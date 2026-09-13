#pragma once

#include "engine/Core.h"
#include "engine/ecs/Entity.h"

namespace pe::ecs {

class World;

class System {
public:
    virtual ~System() = default;

    virtual void init(World& world) { (void)world; }
    virtual void update(World& world, f32 dt) = 0;
    virtual void render(World& world, class Renderer& renderer) { (void)world; (void)renderer; }

    void addEntity(EntityID entity) { m_entities.push_back(entity); }
    void removeEntity(EntityID entity);
    const std::vector<EntityID>& getEntities() const { return m_entities; }

protected:
    std::vector<EntityID> m_entities;
};

} // namespace pe::ecs
