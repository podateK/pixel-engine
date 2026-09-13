#pragma once

#include "engine/Core.h"

namespace pe::ecs {

constexpr u32 MAX_ENTITIES = 10000;
constexpr u32 MAX_COMPONENTS = 64;

using Entity = EntityID;

struct EntityData {
    Entity id = NULL_ENTITY;
    bool alive = false;
    u32 generation = 0;
};

} // namespace pe::ecs
