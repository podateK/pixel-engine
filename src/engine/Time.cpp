#include "engine/Time.h"

namespace pe {

void Time::update() {
    auto currentTime = Clock::now();
    auto duration = std::chrono::duration<f32>(currentTime - m_lastTime);
    m_deltaTime = duration.count();
    m_lastTime = currentTime;

    if (m_deltaTime > 0.25f) {
        m_deltaTime = 0.25f;
    }

    m_elapsedTime += m_deltaTime;

    m_frameCount++;
    m_fpsAccumulator += m_deltaTime;
    if (m_fpsAccumulator >= 1.0f) {
        m_fps = m_frameCount;
        m_frameCount = 0;
        m_fpsAccumulator -= 1.0f;
    }
}

} // namespace pe
