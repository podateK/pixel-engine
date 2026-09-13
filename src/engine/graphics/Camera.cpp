#include "engine/graphics/Camera.h"
#include <cmath>
#include <algorithm>

namespace pe::graphics {

Camera::Camera(const sf::Vector2f& center, const sf::Vector2f& size)
    : m_center(center), m_size(size) {
    updateView();
}

void Camera::update(f32 dt) {
    if (m_following) {
        sf::Vector2f diff = m_followTarget - m_center;
        m_center += diff * m_followSmoothing * dt;
    }

    if (m_followBounds.has_value()) {
        const auto& bounds = m_followBounds.value();
        sf::Vector2f halfSize = m_size * 0.5f;
        m_center.x = std::clamp(m_center.x, bounds.left + halfSize.x, bounds.left + bounds.width - halfSize.x);
        m_center.y = std::clamp(m_center.y, bounds.top + halfSize.y, bounds.top + bounds.height - halfSize.y);
    }

    m_zoom = std::lerp(m_zoom, m_targetZoom, 5.0f * dt);

    applyShake(dt);
    updateView();
}

void Camera::follow(const sf::Vector2f& target, f32 smoothing) {
    m_followTarget = target;
    m_followSmoothing = smoothing;
    m_following = true;
}

void Camera::setPosition(const sf::Vector2f& position) {
    m_center = position;
    m_following = false;
    updateView();
}

void Camera::setSize(const sf::Vector2f& size) {
    m_size = size;
    updateView();
}

void Camera::zoom(f32 factor) {
    m_targetZoom *= factor;
    m_targetZoom = std::clamp(m_targetZoom, 0.1f, 10.0f);
}

void Camera::setZoom(f32 zoom) {
    m_targetZoom = std::clamp(zoom, 0.1f, 10.0f);
}

void Camera::setBounds(const sf::FloatRect& bounds) {
    m_worldBounds = bounds;
    sf::Vector2f halfSize = m_size * 0.5f;
    m_center.x = std::clamp(m_center.x, bounds.left + halfSize.x, bounds.left + bounds.width - halfSize.x);
    m_center.y = std::clamp(m_center.y, bounds.top + halfSize.y, bounds.top + bounds.height - halfSize.y);
}

void Camera::setFollowBounds(const sf::FloatRect& bounds) {
    m_followBounds = bounds;
}

void Camera::shake(f32 intensity, f32 duration) {
    m_shakeIntensity = intensity;
    m_shakeDuration = duration;
    m_shakeTimer = 0.0f;
}

sf::Vector2f Camera::screenToWorld(const sf::Vector2f& screenPos, const sf::RenderWindow& window) const {
    return window.mapPixelToCoords(static_cast<sf::Vector2i>(screenPos), m_view);
}

sf::Vector2f Camera::worldToScreen(const sf::Vector2f& worldPos, const sf::RenderWindow& window) const {
    return window.mapCoordsToPixel(worldPos, m_view);
}

void Camera::updateView() {
    m_view.setCenter(m_center + m_shakeOffset);
    m_view.setSize(m_size / m_zoom);
}

void Camera::applyShake(f32 dt) {
    if (m_shakeTimer < m_shakeDuration) {
        m_shakeTimer += dt;
        f32 progress = m_shakeTimer / m_shakeDuration;
        f32 currentIntensity = m_shakeIntensity * (1.0f - progress);

        static std::mt19937 rng{std::random_device{}()};
        std::uniform_real_distribution<f32> dist(-1.0f, 1.0f);
        m_shakeOffset = {dist(rng) * currentIntensity, dist(rng) * currentIntensity};
    } else {
        m_shakeOffset = {0.0f, 0.0f};
    }
}

} // namespace pe::graphics
