#pragma once

#include "engine/Core.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <memory>

namespace pe::resources {

template<typename T>
class ResourceCache {
public:
    T* load(const std::string& id, const std::string& path) {
        auto it = m_resources.find(id);
        if (it != m_resources.end()) {
            return it->second.get();
        }

        auto resource = std::make_unique<T>();
        if constexpr (std::is_same_v<T, sf::Music>) {
            if (!resource->openFromFile(path)) return nullptr;
        } else {
            if (!resource->loadFromFile(path)) return nullptr;
        }

        T* ptr = resource.get();
        m_resources[id] = std::move(resource);
        return ptr;
    }

    T* get(const std::string& id) {
        auto it = m_resources.find(id);
        return (it != m_resources.end()) ? it->second.get() : nullptr;
    }

    const T* get(const std::string& id) const {
        auto it = m_resources.find(id);
        return (it != m_resources.end()) ? it->second.get() : nullptr;
    }

    bool has(const std::string& id) const {
        return m_resources.find(id) != m_resources.end();
    }

    void remove(const std::string& id) {
        m_resources.erase(id);
    }

    void clear() {
        m_resources.clear();
    }

    u32 count() const { return static_cast<u32>(m_resources.size()); }

    std::vector<std::string> getIds() const {
        std::vector<std::string> ids;
        ids.reserve(m_resources.size());
        for (const auto& [id, _] : m_resources) {
            ids.push_back(id);
        }
        return ids;
    }

private:
    std::unordered_map<std::string, std::unique_ptr<T>> m_resources;
};

} // namespace pe::resources
