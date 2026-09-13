#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <array>
#include <queue>
#include <optional>
#include <functional>
#include <algorithm>
#include <numeric>
#include <random>
#include <chrono>
#include <cassert>
#include <typeindex>
#include <type_traits>
#include <concepts>
#include <span>

namespace pe {

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using f32 = float;
using f64 = double;

using EntityID = u32;
using ComponentTypeID = u32;

constexpr EntityID NULL_ENTITY = 0;

template<typename T>
concept Numeric = std::is_arithmetic_v<T>;

template<typename T>
concept ComponentType = std::is_default_constructible_v<T>;

} // namespace pe
