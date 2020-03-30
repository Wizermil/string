#pragma once

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#include <benchmark/benchmark.h>
#pragma clang diagnostic pop

#include <utility>

namespace wiz {

    template <typename T>
    void operation_clear_long_test(benchmark::State& state) noexcept {
        for (auto _ : state) {
            state.PauseTiming();
            T a {"totototototototototototototototo", 32};
            state.ResumeTiming();
            a.clear();
            benchmark::DoNotOptimize(a);
        }
        state.counters["itr"] = benchmark::Counter(state.iterations(), benchmark::Counter::kIsRate);
    }

    template <typename T>
    void operation_clear_short_test(benchmark::State& state) noexcept {
        for (auto _ : state) {
            state.PauseTiming();
            T a {"toto", 4};
            state.ResumeTiming();
            a.clear();
            benchmark::DoNotOptimize(a);
        }
        state.counters["itr"] = benchmark::Counter(state.iterations(), benchmark::Counter::kIsRate);
    }

} // namespace wiz
