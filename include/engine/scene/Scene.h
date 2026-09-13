#pragma once

#include "engine/Core.h"

namespace pe::scene {

class Engine;
class SceneManager;

class Scene {
public:
    virtual ~Scene() = default;

    virtual void onEnter(Engine& engine) = 0;
    virtual void onExit(Engine& engine) = 0;
    virtual void update(Engine& engine, f32 dt) = 0;
    virtual void render(Engine& engine, class Renderer& renderer) = 0;

    virtual void onPause(Engine& engine) { (void)engine; }
    virtual void onResume(Engine& engine) { (void)engine; }

    bool isActive() const { return m_active; }
    const std::string& getName() const { return m_name; }

protected:
    void setName(const std::string& name) { m_name = name; }

private:
    std::string m_name;
    bool m_active = false;
    friend class SceneManager;
};

} // namespace pe::scene
