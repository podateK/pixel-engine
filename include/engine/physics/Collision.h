#pragma once

#include "engine/Core.h"
#include <SFML/System/Vector2.hpp>

namespace pe::physics {

struct AABB {
    sf::Vector2f position;
    sf::Vector2f size;

    sf::Vector2f getMin() const { return position; }
    sf::Vector2f getMax() const { return position + size; }
    sf::Vector2f getCenter() const { return position + size * 0.5f; }
    sf::Vector2f getHalfSize() const { return size * 0.5f; }

    bool contains(const sf::Vector2f& point) const {
        return point.x >= position.x && point.x <= position.x + size.x &&
               point.y >= position.y && point.y <= position.y + size.y;
    }

    bool intersects(const AABB& other) const {
        return position.x < other.position.x + other.size.x &&
               position.x + size.x > other.position.x &&
               position.y < other.position.y + other.size.y &&
               position.y + size.y > other.position.y;
    }

    bool intersects(const AABB& other, sf::Vector2f& overlap) const {
        f32 overlapX = std::min(getMax().x, other.getMax().x) - std::max(getMin().x, other.getMin().x);
        f32 overlapY = std::min(getMax().y, other.getMax().y) - std::max(getMin().y, other.getMin().y);

        if (overlapX <= 0.0f || overlapY <= 0.0f) return false;

        overlap = {overlapX, overlapY};
        return true;
    }
};

struct CollisionManifold {
    EntityID entityA = NULL_ENTITY;
    EntityID entityB = NULL_ENTITY;
    sf::Vector2f normal{0.0f, 0.0f};
    f32 depth = 0.0f;
    sf::Vector2f contactPoint{0.0f, 0.0f};
};

bool testAABB(const AABB& a, const AABB& b);
bool resolveAABB(AABB& a, AABB& b, const sf::Vector2f& velA, const sf::Vector2f& velB, CollisionManifold& manifold);
sf::Vector2f calculateOverlap(const AABB& a, const AABB& b);

} // namespace pe::physics
