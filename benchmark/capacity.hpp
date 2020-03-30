#pragma once

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#include <benchmark/benchmark.h>
#pragma clang diagnostic pop

namespace wiz {

    template <typename T>
    void capacity_reserve_long_test(benchmark::State& state) noexcept {
        for (auto _ : state) {
            state.PauseTiming();
            T data {"totototototototototototototototo", 32};
            state.ResumeTiming();
            data.reserve(65);
        }
        state.counters["itr"] = benchmark::Counter(state.iterations(), benchmark::Counter::kIsRate);
    }

    template <typename T>
    void capacity_reserve_short_test(benchmark::State& state) noexcept {
        for (auto _ : state) {
            state.PauseTiming();
            T data {"toto", 4};
            state.ResumeTiming();
            data.reserve(5);
        }
        state.counters["itr"] = benchmark::Counter(state.iterations(), benchmark::Counter::kIsRate);
    }

    template <typename T>
    void capacity_shrink_long_test(benchmark::State& state) noexcept {
        for (auto _ : state) {
            state.PauseTiming();
            T data {"toto", 4};
            data.reserve(65);
            state.ResumeTiming();
            data.shrink_to_fit();
        }
        state.counters["itr"] = benchmark::Counter(state.iterations(), benchmark::Counter::kIsRate);
    }

    template <typename T>
    void capacity_shrink_short_test(benchmark::State& state) noexcept {
        for (auto _ : state) {
            state.PauseTiming();
            T data {"toto", 4};
            state.ResumeTiming();
            data.shrink_to_fit();
        }
        state.counters["itr"] = benchmark::Counter(state.iterations(), benchmark::Counter::kIsRate);
    }

} // namespace wiz
