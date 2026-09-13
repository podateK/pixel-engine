#pragma once

#include "Core.h"

namespace pe {

class Time {
public:
    Time() = default;

    void update();

    f32 getDeltaTime() const { return m_deltaTime; }
    f32 getElapsedTime() const { return m_elapsedTime; }
    u32 getFps() const { return m_fps; }

    void setTimeScale(f32 scale) { m_timeScale = scale; }
    f32 getTimeScale() const { return m_timeScale; }

    f32 getScaledDeltaTime() const { return m_deltaTime * m_timeScale; }

private:
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = Clock::time_point;

    TimePoint m_lastTime = Clock::now();
    f32 m_deltaTime = 0.0f;
    f32 m_elapsedTime = 0.0f;
    f32 m_timeScale = 1.0f;
    u32 m_fps = 0;

    u32 m_frameCount = 0;
    f32 m_fpsAccumulator = 0.0f;
};

} // namespace pe
