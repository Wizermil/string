#pragma once

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#include <benchmark/benchmark.h>
#pragma clang diagnostic pop

#include <utility>

namespace wiz {

    template <typename T>
    void function_equal_string_long_test(benchmark::State& state) noexcept {
        for (auto _ : state) {
            state.PauseTiming();
            T a {"totototototototototototototototo", 32};
            T b {"totototototototototototototototo", 32};
            state.ResumeTiming();
            benchmark::DoNotOptimize(a == b);
        }
        state.counters["itr"] = benchmark::Counter(state.iterations(), benchmark::Counter::kIsRate);
    }

    template <typename T>
    void function_equal_string_short_test(benchmark::State& state) noexcept {
        for (auto _ : state) {
            state.PauseTiming();
            T a {"toto", 4};
            T b {"toto", 4};
            state.ResumeTiming();
            benchmark::DoNotOptimize(a == b);
        }
        state.counters["itr"] = benchmark::Counter(state.iterations(), benchmark::Counter::kIsRate);
    }

    template <typename T>
    void function_equal_cstring_long_test(benchmark::State& state) noexcept {
        for (auto _ : state) {
            state.PauseTiming();
            T a {"totototototototototototototototo", 32};
            state.ResumeTiming();
            benchmark::DoNotOptimize(a == "totototototototototototototototo");
        }
        state.counters["itr"] = benchmark::Counter(state.iterations(), benchmark::Counter::kIsRate);
    }

    template <typename T>
    void function_equal_cstring_short_test(benchmark::State& state) noexcept {
        for (auto _ : state) {
            state.PauseTiming();
            T a {"toto", 4};
            state.ResumeTiming();
            benchmark::DoNotOptimize(a == "toto");
        }
        state.counters["itr"] = benchmark::Counter(state.iterations(), benchmark::Counter::kIsRate);
    }

} // namespace wiz
