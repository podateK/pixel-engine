#pragma once

#include "engine/Core.h"
#include <SFML/Audio.hpp>
#include <unordered_map>

namespace pe::audio {

class SoundManager {
public:
    SoundManager() = default;

    bool loadSound(const std::string& name, const std::string& path);
    bool loadMusic(const std::string& name, const std::string& path);

    void playSound(const std::string& name, f32 volume = 100.0f, f32 pitch = 1.0f);
    void stopSound(const std::string& name);
    void stopAllSounds();

    void playMusic(const std::string& name, f32 volume = 100.0f, bool loop = true);
    void stopMusic();
    void pauseMusic();
    void resumeMusic();

    void setSoundVolume(const std::string& name, f32 volume);
    void setMusicVolume(f32 volume);
    void setMasterVolume(f32 volume);

    f32 getMasterVolume() const { return m_masterVolume; }
    f32 getMusicVolume() const { return m_musicVolume; }

    bool isMusicPlaying() const;
    bool isSoundPlaying(const std::string& name) const;

    void removeSound(const std::string& name);

private:
    std::unordered_map<std::string, std::unique_ptr<sf::SoundBuffer>> m_buffers;
    std::unordered_map<std::string, std::unique_ptr<sf::Sound>> m_sounds;
    std::unordered_map<std::string, std::unique_ptr<sf::Music>> m_music;

    f32 m_masterVolume = 100.0f;
    f32 m_musicVolume = 80.0f;
    std::string m_currentMusic;
};

} // namespace pe::audio
