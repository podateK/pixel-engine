#pragma once

#include "engine/Core.h"
#include <SFML/Graphics.hpp>

namespace pe::graphics {

struct TransformComponent {
    sf::Vector2f position{0.0f, 0.0f};
    sf::Vector2f scale{1.0f, 1.0f};
    f32 rotation = 0.0f;
};

struct SpriteComponent {
    sf::Sprite sprite;
    sf::IntRect textureRect;
    sf::Color color = sf::Color::White;
    u32 layer = 0;
    bool visible = true;
};

} // namespace pe::graphics
