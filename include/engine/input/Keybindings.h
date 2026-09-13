#pragma once

#include "engine/Core.h"
#include "engine/input/InputManager.h"
#include <unordered_map>
#include <fstream>

namespace pe::input {

struct KeybindEntry {
    std::string actionName;
    sf::Keyboard::Key key;
};

class Keybindings {
public:
    Keybindings() = default;

    void setBinding(const std::string& action, sf::Keyboard::Key key);
    sf::Keyboard::Key getBinding(const std::string& action) const;
    bool hasBinding(const std::string& action) const;
    void removeBinding(const std::string& action);

    void applyBindings(InputManager& inputManager) const;
    void loadFromFile(const std::string& path);
    void saveToFile(const std::string& path) const;

    void setDefault(const std::string& action, sf::Keyboard::Key key);
    void resetToDefaults();

    const std::unordered_map<std::string, sf::Keyboard::Key>& getAllBindings() const { return m_bindings; }

private:
    static std::string keyToString(sf::Keyboard::Key key);
    static sf::Keyboard::Key stringToKey(const std::string& str);

    std::unordered_map<std::string, sf::Keyboard::Key> m_bindings;
    std::unordered_map<std::string, sf::Keyboard::Key> m_defaults;
};

} // namespace pe::input
