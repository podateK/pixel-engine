#pragma once

#include "engine/Core.h"
#include "engine/scene/Scene.h"
#include <stack>

namespace pe::scene {

enum class TransitionType {
    None,
    FadeOut,
    FadeIn,
    SlideLeft,
    SlideRight
};

class SceneManager {
public:
    SceneManager() = default;

    void pushScene(std::shared_ptr<Scene> scene);
    void popScene();
    void changeScene(std::shared_ptr<Scene> scene);

    void setTransition(TransitionType type, f32 duration);

    void update(Engine& engine, f32 dt);
    void render(Engine& engine, class Renderer& renderer);

    Scene* getCurrentScene();
    const Scene* getCurrentScene() const;
    u32 getSceneCount() const { return static_cast<u32>(m_scenes.size()); }

    bool isTransitioning() const { return m_transitioning; }

private:
    void beginTransition(TransitionType type, f32 duration);
    void updateTransition(f32 dt);

    std::stack<std::shared_ptr<Scene>> m_scenes;
    std::shared_ptr<Scene> m_pendingScene;

    TransitionType m_transitionType = TransitionType::None;
    f32 m_transitionDuration = 0.0f;
    f32 m_transitionTimer = 0.0f;
    bool m_transitioning = false;
    bool m_transitionHalfway = false;
    f32 m_transitionAlpha = 0.0f;

    TransitionType m_currentTransitionType = TransitionType::None;
    f32 m_currentTransitionDuration = 0.0f;
};

} // namespace pe::scene
