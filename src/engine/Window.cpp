#include "engine/Window.h"

namespace pe {

bool Window::create(const std::string& title, u32 width, u32 height, bool vsync) {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;

    m_window.create(sf::VideoMode(width, height), title, sf::Style::Default, settings);
    m_window.setVerticalSyncEnabled(vsync);

    m_defaultView = m_window.getDefaultView();
    m_defaultView.setCenter(static_cast<f32>(width) / 2.0f, static_cast<f32>(height) / 2.0f);
    m_defaultView.setSize(static_cast<f32>(width), static_cast<f32>(height));
    m_window.setView(m_defaultView);

    return m_window.isOpen();
}

void Window::close() {
    m_window.close();
}

bool Window::isOpen() const {
    return m_window.isOpen();
}

void Window::clear(const sf::Color& color) {
    m_window.clear(color);
}

void Window::display() {
    m_window.display();
}

void Window::setView(const sf::View& view) {
    m_window.setView(view);
}

void Window::resetView() {
    m_window.setView(m_defaultView);
}

sf::Vector2u Window::getSize() const {
    return m_window.getSize();
}

sf::Vector2f Window::mapPixelToCoords(const sf::Vector2i& point) const {
    return m_window.mapPixelToCoords(point);
}

void Window::setVerticalSyncEnabled(bool enabled) {
    m_window.setVerticalSyncEnabled(enabled);
}

void Window::setFramerateLimit(u32 limit) {
    m_window.setFramerateLimit(limit);
}

std::optional<sf::Event> Window::pollEvent() {
    sf::Event event;
    if (m_window.pollEvent(event)) {
        return event;
    }
    return std::nullopt;
}

} // namespace pe
