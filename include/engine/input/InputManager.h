#pragma once

#include "engine/Core.h"
#include <SFML/Window.hpp>
#include <unordered_map>
#include <unordered_set>

namespace pe::input {

enum class InputAction {
    None,
    MoveUp,
    MoveDown,
    MoveLeft,
    MoveRight,
    Action,
    Jump,
    Pause,
    Menu
};

class InputManager {
public:
    InputManager() = default;

    void update(const sf::Event& event);
    void update();

    bool isKeyPressed(sf::Keyboard::Key key) const;
    bool isKeyJustPressed(sf::Keyboard::Key key) const;
    bool isKeyJustReleased(sf::Keyboard::Key key) const;

    bool isActionPressed(InputAction action) const;
    bool isActionJustPressed(InputAction action) const;
    bool isActionJustReleased(InputAction action) const;

    bool isMouseButtonPressed(sf::Mouse::Button button) const;
    bool isMouseButtonJustPressed(sf::Mouse::Button button) const;
    bool isMouseButtonJustReleased(sf::Mouse::Button button) const;

    sf::Vector2i getMousePosition() const;
    sf::Vector2f getMousePosition(const sf::RenderWindow& window) const;

    void bindKey(InputAction action, sf::Keyboard::Key key);
    void unbindKey(InputAction action);
    sf::Keyboard::Key getBinding(InputAction action) const;

    void setDeadzone(f32 deadzone) { m_deadzone = deadzone; }

private:
    std::unordered_set<sf::Keyboard::Key> m_keysPressed;
    std::unordered_set<sf::Keyboard::Key> m_keysJustPressed;
    std::unordered_set<sf::Keyboard::Key> m_keysJustReleased;
    std::unordered_set<sf::Keyboard::Key> m_prevKeysPressed;

    std::unordered_set<sf::Mouse::Button> m_mousePressed;
    std::unordered_set<sf::Mouse::Button> m_mouseJustPressed;
    std::unordered_set<sf::Mouse::Button> m_mouseJustReleased;
    std::unordered_set<sf::Mouse::Button> m_prevMousePressed;

    std::unordered_map<InputAction, sf::Keyboard::Key> m_bindings;
    f32 m_deadzone = 0.2f;
};

} // namespace pe::input
