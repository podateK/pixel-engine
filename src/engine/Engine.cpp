#include "engine/Engine.h"

namespace pe {

Engine::Engine(const Config& config) : m_config(config) {
    m_window.create(config.title, config.windowWidth, config.windowHeight, config.vsync);
    m_renderer.init(m_window.getHandle());
    m_input = input::InputManager();
}

Engine::~Engine() {
    stop();
}

void Engine::run() {
    m_running = true;

    m_scenes.update(*this, 0.0f);

    while (m_running && m_window.isOpen()) {
        m_time.update();
        f32 dt = m_time.getDeltaTime();

        processEvents();
        update(dt);
        render();
    }
}

void Engine::stop() {
    m_running = false;
    m_world.clear();
}

void Engine::processEvents() {
    while (auto event = m_window.pollEvent()) {
        m_input.update(*event.value());

        if (event.value()->type == sf::Event::Closed) {
            m_running = false;
            m_window.close();
        }
    }

    m_input.update();
}

void Engine::update(f32 dt) {
    m_scenes.update(*this, dt);
    m_physics.update(m_world, dt);

    if (m_updateCallback) {
        m_updateCallback(dt);
    }
}

void Engine::render() {
    m_renderer.clear(m_config.clearColor);

    sf::View cameraView = m_camera.getView();
    m_renderer.setView(cameraView);

    if (m_renderCallback) {
        m_renderCallback(m_renderer);
    }

    m_scenes.render(*this, m_renderer);
    m_renderer.flush();

    m_renderer.setView(m_window.getHandle().getDefaultView());
    m_window.display();
}

} // namespace pe
