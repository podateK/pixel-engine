#pragma once

#include "engine/Core.h"
#include "engine/ecs/World.h"
#include "engine/ecs/Entity.h"
#include "engine/physics/PhysicsBody.h"
#include "engine/physics/Collision.h"
#include <functional>

namespace pe::physics {

class PhysicsWorld {
public:
    PhysicsWorld() = default;

    void setGravity(const sf::Vector2f& gravity) { m_gravity = gravity; }
    sf::Vector2f getGravity() const { return m_gravity; }

    void step(f32 dt);
    void update(pe::ecs::World& world, f32 dt);

    using CollisionCallback = std::function<void(EntityID a, EntityID b, const CollisionManifold&)>;
    void setCollisionCallback(CollisionCallback callback) { m_collisionCallback = std::move(callback); }

    const std::vector<CollisionManifold>& getCollisions() const { return m_collisions; }
    u32 getCollisionCount() const { return static_cast<u32>(m_collisions.size()); }

    void setVelocityIterations(u32 iterations) { m_velocityIterations = iterations; }
    void setPositionIterations(u32 iterations) { m_positionIterations = iterations; }

private:
    void integrate(f32 dt);
    void detectCollisions(pe::ecs::World& world);
    void resolveCollisions();

    sf::Vector2f m_gravity{0.0f, 980.0f};
    std::vector<CollisionManifold> m_collisions;
    CollisionCallback m_collisionCallback;

    u32 m_velocityIterations = 8;
    u32 m_positionIterations = 3;

    struct BodyPair {
        EntityID a;
        EntityID b;
    };
    std::vector<BodyPair> m_bodyPairs;
};

} // namespace pe::physics
