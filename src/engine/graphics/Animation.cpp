#include "engine/graphics/Animation.h"

namespace pe::graphics {

void Animation::addFrame(const sf::IntRect& rect, f32 duration) {
    m_frames.push_back({rect, duration});
}

void Animation::play() {
    m_playing = true;
    m_finished = false;
    m_currentFrame = 0;
    m_frameTimer = 0.0f;
}

void Animation::pause() {
    m_playing = false;
}

void Animation::stop() {
    m_playing = false;
    m_finished = false;
    m_currentFrame = 0;
    m_frameTimer = 0.0f;
}

void Animation::reset() {
    m_currentFrame = 0;
    m_frameTimer = 0.0f;
    m_finished = false;
}

void Animation::update(f32 dt) {
    if (!m_playing || m_finished || m_frames.empty()) return;

    m_frameTimer += dt * m_playbackSpeed;

    while (m_frameTimer >= m_frames[m_currentFrame].duration) {
        m_frameTimer -= m_frames[m_currentFrame].duration;
        m_currentFrame++;

        if (m_currentFrame >= m_frames.size()) {
            if (m_looping) {
                m_currentFrame = 0;
            } else {
                m_currentFrame = static_cast<u32>(m_frames.size()) - 1;
                m_finished = true;
                m_playing = false;
                return;
            }
        }
    }
}

sf::IntRect Animation::getCurrentFrame() const {
    if (m_frames.empty()) return {};
    return m_frames[m_currentFrame].rect;
}

void AnimationController::addAnimation(const std::string& name, Animation animation) {
    m_animations[name] = std::move(animation);
}

void AnimationController::play(const std::string& name) {
    if (m_currentAnimation == name && m_animations[name].isPlaying()) return;

    if (!m_currentAnimation.empty()) {
        auto it = m_animations.find(m_currentAnimation);
        if (it != m_animations.end()) {
            it->second.stop();
        }
    }

    m_currentAnimation = name;
    auto it = m_animations.find(name);
    if (it != m_animations.end()) {
        it->second.play();
    }
}

void AnimationController::stop(const std::string& name) {
    auto it = m_animations.find(name);
    if (it != m_animations.end()) {
        it->second.stop();
    }
    if (m_currentAnimation == name) {
        m_currentAnimation.clear();
    }
}

void AnimationController::stopAll() {
    for (auto& [name, anim] : m_animations) {
        anim.stop();
    }
    m_currentAnimation.clear();
}

void AnimationController::update(f32 dt) {
    auto it = m_animations.find(m_currentAnimation);
    if (it != m_animations.end()) {
        it->second.update(dt);
    }
}

Animation* AnimationController::getAnimation(const std::string& name) {
    auto it = m_animations.find(name);
    return (it != m_animations.end()) ? &it->second : nullptr;
}

} // namespace pe::graphics
