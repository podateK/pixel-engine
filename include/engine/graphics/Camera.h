#pragma once

#include "engine/Core.h"
#include <SFML/Graphics.hpp>

namespace pe::graphics {

class Camera {
public:
    Camera() = default;
    explicit Camera(const sf::Vector2f& center, const sf::Vector2f& size);

    void update(f32 dt);

    void follow(const sf::Vector2f& target, f32 smoothing = 5.0f);
    void followEntity(class World& world, EntityID entity, f32 smoothing = 5.0f);

    void setPosition(const sf::Vector2f& position);
    sf::Vector2f getPosition() const { return m_center; }

    void setSize(const sf::Vector2f& size);
    sf::Vector2f getSize() const { return m_size; }

    void zoom(f32 factor);
    void setZoom(f32 zoom);
    f32 getZoom() const { return m_zoom; }

    void setBounds(const sf::FloatRect& bounds);
    void setFollowBounds(const sf::FloatRect& bounds);

    void shake(f32 intensity, f32 duration);

    const sf::View& getView() const { return m_view; }

    sf::Vector2f screenToWorld(const sf::Vector2f& screenPos, const sf::RenderWindow& window) const;
    sf::Vector2f worldToScreen(const sf::Vector2f& worldPos, const sf::RenderWindow& window) const;

private:
    void updateView();
    void applyShake(f32 dt);

    sf::View m_view;
    sf::Vector2f m_center{0.0f, 0.0f};
    sf::Vector2f m_size{1280.0f, 720.0f};
    f32 m_zoom = 1.0f;
    f32 m_targetZoom = 1.0f;

    sf::Vector2f m_followTarget{0.0f, 0.0f};
    f32 m_followSmoothing = 5.0f;
    bool m_following = false;

    std::optional<sf::FloatRect> m_worldBounds;
    std::optional<sf::FloatRect> m_followBounds;

    f32 m_shakeIntensity = 0.0f;
    f32 m_shakeDuration = 0.0f;
    f32 m_shakeTimer = 0.0f;
    sf::Vector2f m_shakeOffset{0.0f, 0.0f};
};

} // namespace pe::graphics
