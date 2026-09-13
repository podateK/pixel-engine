#pragma once

#include "engine/Core.h"
#include <SFML/System/Vector2.hpp>

namespace pe::physics {

enum class BodyType {
    Static,
    Dynamic,
    Kinematic
};

struct PhysicsBody {
    BodyType type = BodyType::Dynamic;
    sf::Vector2f velocity{0.0f, 0.0f};
    sf::Vector2f acceleration{0.0f, 0.0f};
    sf::Vector2f force{0.0f, 0.0f};

    f32 mass = 1.0f;
    f32 inverseMass = 1.0f;
    f32 restitution = 0.0f;
    f32 friction = 0.5f;

    bool isSensor = false;
    bool affectedByGravity = true;

    u32 collisionLayer = 1;
    u32 collisionMask = 0xFFFFFFFF;

    void applyForce(const sf::Vector2f& f) { force += f; }
    void applyImpulse(const sf::Vector2f& impulse) { velocity += impulse * inverseMass; }

    void setMass(f32 m) {
        mass = m;
        inverseMass = (m > 0.0f) ? (1.0f / m) : 0.0f;
    }

    sf::Vector2f getKineticEnergy() const {
        f32 speed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
        return {0.5f * mass * speed * speed, 0.0f};
    }
};

} // namespace pe::physics
