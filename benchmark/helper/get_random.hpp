#pragma once

#include <cstddef>
#include <random>
#include <type_traits>

namespace wiz {

    template <typename T, std::enable_if_t<std::is_arithmetic_v<T> && std::is_integral_v<T>>* = nullptr>
    static inline T get_random(T a, T b) noexcept {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<T> dis(a, b);
        return dis(gen);
    }

    template <typename T, std::enable_if_t<std::is_arithmetic_v<T> && std::is_floating_point_v<T>>* = nullptr>
    static inline T get_random(T a, T b) noexcept {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_real_distribution<T> dis(a, b);
        return dis(gen);
    }

} // namespace wiz
