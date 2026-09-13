#pragma once

#include "Core.h"
#include "Window.h"
#include "Time.h"
#include "ecs/World.h"
#include "graphics/Renderer.h"
#include "graphics/Camera.h"
#include "physics/PhysicsWorld.h"
#include "audio/SoundManager.h"
#include "input/InputManager.h"
#include "scene/SceneManager.h"
#include "resources/AssetManager.h"

namespace pe {

class Engine {
public:
    struct Config {
        std::string title = "PixelEngine";
        u32 windowWidth = 1280;
        u32 windowHeight = 720;
        bool vsync = true;
        u32 targetFps = 0;
        sf::Color clearColor = sf::Color::Black;
    };

    explicit Engine(const Config& config = {});
    ~Engine();

    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;
    Engine(Engine&&) = delete;
    Engine& operator=(Engine&&) = delete;

    void run();
    void stop();

    Window& getWindow() { return m_window; }
    const Window& getWindow() const { return m_window; }

    Time& getTime() { return m_time; }
    const Time& getTime() const { return m_time; }

    World& getWorld() { return m_world; }
    const World& getWorld() const { return m_world; }

    Renderer& getRenderer() { return m_renderer; }
    const Renderer& getRenderer() const { return m_renderer; }

    Camera& getCamera() { return m_camera; }
    const Camera& getCamera() const { return m_camera; }

    PhysicsWorld& getPhysics() { return m_physics; }
    const PhysicsWorld& getPhysics() const { return m_physics; }

    SoundManager& getAudio() { return m_audio; }
    const SoundManager& getAudio() const { return m_audio; }

    InputManager& getInput() { return m_input; }
    const InputManager& getInput() const { return m_input; }

    SceneManager& getScenes() { return m_scenes; }
    const SceneManager& getScenes() const { return m_scenes; }

    AssetManager& getAssets() { return m_assets; }
    const AssetManager& getAssets() const { return m_assets; }

    bool isRunning() const { return m_running; }

    using UpdateCallback = std::function<void(f32 dt)>;
    using RenderCallback = std::function<void(Renderer&)>;

    void setUpdateCallback(UpdateCallback callback) { m_updateCallback = std::move(callback); }
    void setRenderCallback(RenderCallback callback) { m_renderCallback = std::move(callback); }

private:
    void processEvents();
    void update(f32 dt);
    void render();

    bool m_running = false;
    Config m_config;

    Window m_window;
    Time m_time;
    World m_world;
    Renderer m_renderer;
    Camera m_camera;
    PhysicsWorld m_physics;
    SoundManager m_audio;
    InputManager m_input;
    SceneManager m_scenes;
    AssetManager m_assets;

    UpdateCallback m_updateCallback;
    RenderCallback m_renderCallback;
};

} // namespace pe
