#pragma once

#include "engine/Core.h"
#include <SFML/Graphics.hpp>
#include <vector>

namespace pe::graphics {

struct Frame {
    sf::IntRect rect;
    f32 duration;
};

class Animation {
public:
    Animation() = default;

    void addFrame(const sf::IntRect& rect, f32 duration);
    void setLooping(bool loop) { m_looping = loop; }
    bool isLooping() const { return m_looping; }

    void play();
    void pause();
    void stop();
    void reset();

    void update(f32 dt);

    bool isFinished() const { return m_finished; }
    bool isPlaying() const { return m_playing; }

    sf::IntRect getCurrentFrame() const;
    u32 getCurrentFrameIndex() const { return m_currentFrame; }
    u32 getFrameCount() const { return static_cast<u32>(m_frames.size()); }

    void setPlaybackSpeed(f32 speed) { m_playbackSpeed = speed; }
    f32 getPlaybackSpeed() const { return m_playbackSpeed; }

    const std::vector<Frame>& getFrames() const { return m_frames; }

private:
    std::vector<Frame> m_frames;
    u32 m_currentFrame = 0;
    f32 m_frameTimer = 0.0f;
    f32 m_playbackSpeed = 1.0f;
    bool m_looping = true;
    bool m_playing = false;
    bool m_finished = false;
};

class AnimationController {
public:
    void addAnimation(const std::string& name, Animation animation);
    void play(const std::string& name);
    void stop(const std::string& name);
    void stopAll();

    void update(f32 dt);

    Animation* getAnimation(const std::string& name);
    const std::string& getCurrentAnimation() const { return m_currentAnimation; }

private:
    std::unordered_map<std::string, Animation> m_animations;
    std::string m_currentAnimation;
};

} // namespace pe::graphics
