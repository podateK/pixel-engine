#pragma once

#include "engine/Core.h"

namespace pe::ecs {

class IComponentArray {
public:
    virtual ~IComponentArray() = default;
    virtual void removeEntity(EntityID entity) = 0;
};

template<typename T>
class ComponentArray : public IComponentArray {
public:
    void insert(EntityID entity, const T& component) {
        assert(m_entityToIndex.find(entity) == m_entityToIndex.end() && "Component already exists on entity");
        u32 index = m_size;
        m_entityToIndex[entity] = index;
        m_indexToEntity[index] = entity;
        m_data[index] = component;
        m_size++;
    }

    void removeEntity(EntityID entity) override {
        auto it = m_entityToIndex.find(entity);
        if (it == m_entityToIndex.end()) return;

        u32 removedIndex = it->second;
        u32 lastIndex = m_size - 1;

        m_data[removedIndex] = m_data[lastIndex];

        EntityID lastEntity = m_indexToEntity[lastIndex];
        m_entityToIndex[lastEntity] = removedIndex;
        m_indexToEntity[removedIndex] = lastEntity;

        m_entityToIndex.erase(it);
        m_indexToEntity.erase(lastIndex);
        m_size--;
    }

    T& get(EntityID entity) {
        assert(m_entityToIndex.find(entity) != m_entityToIndex.end() && "Entity does not have this component");
        return m_data[m_entityToIndex[entity]];
    }

    const T& get(EntityID entity) const {
        assert(m_entityToIndex.find(entity) != m_entityToIndex.end() && "Entity does not have this component");
        return m_data[m_entityToIndex[entity]];
    }

    bool has(EntityID entity) const {
        return m_entityToIndex.find(entity) != m_entityToIndex.end();
    }

    u32 size() const { return m_size; }

    std::span<EntityID> getEntities() {
        m_entityBuffer.clear();
        for (u32 i = 0; i < m_size; i++) {
            m_entityBuffer.push_back(m_indexToEntity[i]);
        }
        return m_entityBuffer;
    }

private:
    std::array<T, MAX_ENTITIES> m_data{};
    std::unordered_map<EntityID, u32> m_entityToIndex;
    std::unordered_map<u32, EntityID> m_indexToEntity;
    u32 m_size = 0;
    mutable std::vector<EntityID> m_entityBuffer;
};

} // namespace pe::ecs
