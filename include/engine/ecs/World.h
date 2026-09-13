#pragma once

#include "engine/Core.h"
#include "engine/ecs/Entity.h"
#include "engine/ecs/Component.h"
#include "engine/ecs/System.h"
#include "engine/ecs/ComponentArray.h"

namespace pe::ecs {

class World {
public:
    World() = default;

    EntityID createEntity();
    void destroyEntity(EntityID entity);
    bool isAlive(EntityID entity) const;

    template<typename T>
    void addComponent(EntityID entity, const T& component) {
        getOrCreateArray<T>()->insert(entity, component);
    }

    template<typename T>
    void removeComponent(EntityID entity) {
        auto it = m_componentArrays.find(typeid(T));
        if (it != m_componentArrays.end()) {
            it->second->removeEntity(entity);
        }
    }

    template<typename T>
    T& getComponent(EntityID entity) {
        return getOrCreateArray<T>()->get(entity);
    }

    template<typename T>
    const T& getComponent(EntityID entity) const {
        return getOrCreateArray<T>()->get(entity);
    }

    template<typename T>
    bool hasComponent(EntityID entity) const {
        auto it = m_componentArrays.find(typeid(T));
        if (it == m_componentArrays.end()) return false;
        return static_cast<ComponentArray<T>*>(it->second.get())->has(entity);
    }

    template<typename T, typename... Args>
    T& addSystem(Args&&... args) {
        auto system = std::make_unique<T>(std::forward<Args>(args)...);
        T& ref = *system;
        std::type_index key(typeid(T));
        m_systems[key] = std::move(system);
        m_systemOrder.push_back(key);
        return ref;
    }

    template<typename T>
    T& getSystem() {
        auto it = m_systems.find(typeid(T));
        assert(it != m_systems.end() && "System not found");
        return static_cast<T&>(*it->second);
    }

    template<typename T>
    bool hasSystem() const {
        return m_systems.find(typeid(T)) != m_systems.end();
    }

    void initSystems();
    void updateSystems(f32 dt);
    void renderSystems(class Renderer& renderer);

    void clear();

    u32 getEntityCount() const { return m_entityCount; }

private:
    template<typename T>
    ComponentArray<T>* getOrCreateArray() {
        std::type_index key(typeid(T));
        auto it = m_componentArrays.find(key);
        if (it == m_componentArrays.end()) {
            auto array = std::make_unique<ComponentArray<T>>();
            ComponentArray<T>* ptr = array.get();
            m_componentArrays[key] = std::move(array);
            return ptr;
        }
        return static_cast<ComponentArray<T>*>(it->second.get());
    }

    template<typename T>
    const ComponentArray<T>* getArray() const {
        auto it = m_componentArrays.find(typeid(T));
        if (it == m_componentArrays.end()) return nullptr;
        return static_cast<const ComponentArray<T>*>(it->second.get());
    }

    std::vector<EntityData> m_entities;
    std::queue<EntityID> m_freeEntities;
    u32 m_entityCount = 0;
    u32 m_aliveCount = 0;

    std::unordered_map<std::type_index, std::unique_ptr<IComponentArray>> m_componentArrays;
    std::unordered_map<std::type_index, std::unique_ptr<System>> m_systems;
    std::vector<std::type_index> m_systemOrder;
};

} // namespace pe::ecs
