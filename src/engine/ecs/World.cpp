#include "engine/ecs/World.h"

namespace pe::ecs {

EntityID World::createEntity() {
    EntityID id;
    if (!m_freeEntities.empty()) {
        id = m_freeEntities.front();
        m_freeEntities.pop();
        m_entities[id].alive = true;
        m_entities[id].generation++;
    } else {
        id = static_cast<EntityID>(m_entities.size());
        if (id >= MAX_ENTITIES) {
            assert(false && "Max entities reached");
            return NULL_ENTITY;
        }
        m_entities.push_back({id, true, 0});
    }
    m_entityCount++;
    return id;
}

void World::destroyEntity(EntityID entity) {
    if (entity >= m_entities.size() || !m_entities[entity].alive) return;

    for (auto& [type, array] : m_componentArrays) {
        array->removeEntity(entity);
    }

    for (auto& [type, system] : m_systems) {
        system->removeEntity(entity);
    }

    m_entities[entity].alive = false;
    m_freeEntities.push(entity);
    m_entityCount--;
}

bool World::isAlive(EntityID entity) const {
    return entity < m_entities.size() && m_entities[entity].alive;
}

void World::initSystems() {
    for (auto& key : m_systemOrder) {
        m_systems[key]->init(*this);
    }
}

void World::updateSystems(f32 dt) {
    for (auto& key : m_systemOrder) {
        m_systems[key]->update(*this, dt);
    }
}

void World::renderSystems(Renderer& renderer) {
    for (auto& key : m_systemOrder) {
        m_systems[key]->render(*this, renderer);
    }
}

void World::clear() {
    for (auto& [type, array] : m_componentArrays) {
        for (EntityID i = 0; i < static_cast<EntityID>(m_entities.size()); i++) {
            if (m_entities[i].alive) {
                array->removeEntity(i);
            }
        }
    }

    for (auto& [type, system] : m_systems) {
        for (EntityID i = 0; i < static_cast<EntityID>(m_entities.size()); i++) {
            if (m_entities[i].alive) {
                system->removeEntity(i);
            }
        }
    }

    m_entities.clear();
    while (!m_freeEntities.empty()) m_freeEntities.pop();
    m_entityCount = 0;
}

} // namespace pe::ecs
