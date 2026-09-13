#pragma once

#include "Core.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace pe {

class Window {
public:
    Window() = default;
    ~Window() = default;

    bool create(const std::string& title, u32 width, u32 height, bool vsync = true);
    void close();
    bool isOpen() const;

    void clear(const sf::Color& color = sf::Color::Black);
    void display();

    void setView(const sf::View& view);
    void resetView();

    sf::Vector2u getSize() const;
    sf::Vector2f mapPixelToCoords(const sf::Vector2i& point) const;

    void setVerticalSyncEnabled(bool enabled);
    void setFramerateLimit(u32 limit);

    sf::RenderWindow& getHandle() { return m_window; }
    const sf::RenderWindow& getHandle() const { return m_window; }

    std::optional<sf::Event> pollEvent();

private:
    sf::RenderWindow m_window;
    sf::View m_defaultView;
};

} // namespace pe
