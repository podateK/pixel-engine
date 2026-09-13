#pragma once

#include "engine/Core.h"
#include <SFML/Graphics.hpp>
#include <unordered_map>

namespace pe::graphics {

class ShaderManager {
public:
    bool load(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);
    bool loadFromMemory(const std::string& name, const std::string& vertex, const std::string& fragment);
    void remove(const std::string& name);

    sf::Shader* get(const std::string& name);
    const sf::Shader* get(const std::string& name) const;
    bool has(const std::string& name) const;

    void bind(const std::string& name);
    void unbind();

private:
    std::unordered_map<std::string, std::unique_ptr<sf::Shader>> m_shaders;
    std::string m_boundShader;
};

} // namespace pe::graphics
