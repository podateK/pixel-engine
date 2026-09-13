#pragma once

#include "engine/Core.h"
#include "engine/resources/AssetManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace pe::resources {

class ResourceManager {
public:
    ResourceManager() = default;

    sf::Texture* loadTexture(const std::string& id, const std::string& path);
    sf::Font* loadFont(const std::string& id, const std::string& path);
    sf::SoundBuffer* loadSoundBuffer(const std::string& id, const std::string& path);
    sf::Music* loadMusic(const std::string& id, const std::string& path);

    sf::Texture* getTexture(const std::string& id);
    sf::Font* getFont(const std::string& id);
    sf::SoundBuffer* getSoundBuffer(const std::string& id);
    sf::Music* getMusic(const std::string& id);

    bool hasTexture(const std::string& id) const;
    bool hasFont(const std::string& id) const;
    bool hasSoundBuffer(const std::string& id) const;

    void removeTexture(const std::string& id);
    void removeFont(const std::string& id);
    void removeSoundBuffer(const std::string& id);

    void clearAll();

    u32 getTextureCount() const { return m_textures.count(); }
    u32 getFontCount() const { return m_fonts.count(); }

private:
    ResourceCache<sf::Texture> m_textures;
    ResourceCache<sf::Font> m_fonts;
    ResourceCache<sf::SoundBuffer> m_soundBuffers;
    std::unordered_map<std::string, std::unique_ptr<sf::Music>> m_musicFiles;
};

} // namespace pe::resources
