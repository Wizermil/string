#pragma once

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#include <benchmark/benchmark.h>
#pragma clang diagnostic pop

#include <utility>

namespace wiz {

    template <typename T>
    void constructor_default_test(benchmark::State& state) noexcept {
        for (auto _ : state) {
            T const data;
            benchmark::DoNotOptimize(data);
        }
        state.counters["itr"] = benchmark::Counter(state.iterations(), benchmark::Counter::kIsRate);
    }

    template <typename T>
    void constructor_cstring_long_test(benchmark::State& state) noexcept {
        for (auto _ : state) {
            T const data {"totototototototototototototototo", 32};
            benchmark::DoNotOptimize(data);
        }
        state.counters["itr"] = benchmark::Counter(state.iterations(), benchmark::Counter::kIsRate);
    }

    template <typename T>
    void constructor_cstring_short_test(benchmark::State& state) noexcept {
        for (auto _ : state) {
            T const data {"toto", 4};
            benchmark::DoNotOptimize(data);
        }
        state.counters["itr"] = benchmark::Counter(state.iterations(), benchmark::Counter::kIsRate);
    }

    template <typename T>
    void constructor_copy_long_test(benchmark::State& state) noexcept {
        for (auto _ : state) {
            state.PauseTiming();
            T const b {"totototototototototototototototo", 32};
            state.ResumeTiming();
            T a {b};
            benchmark::DoNotOptimize(a);
        }
        state.counters["itr"] = benchmark::Counter(state.iterations(), benchmark::Counter::kIsRate);
    }

    template <typename T>
    void constructor_copy_short_test(benchmark::State& state) noexcept {
        for (auto _ : state) {
            state.PauseTiming();
            T const b {"toto", 4};
            state.ResumeTiming();
            T a {b};
            benchmark::DoNotOptimize(a);
        }
        state.counters["itr"] = benchmark::Counter(state.iterations(), benchmark::Counter::kIsRate);
    }

    template <typename T>
    void constructor_copyassign_long_test(benchmark::State& state) noexcept {
        for (auto _ : state) {
            state.PauseTiming();
            T a {"totototototototototototototototo", 32};
            T const b {"totototototototototototototototo", 32};
            state.ResumeTiming();
            a = b;
            benchmark::DoNotOptimize(a);
        }
        state.counters["itr"] = benchmark::Counter(state.iterations(), benchmark::Counter::kIsRate);
    }

    template <typename T>
    void constructor_copyassign_long_worst_test(benchmark::State& state) noexcept {
        for (auto _ : state) {
            state.PauseTiming();
            T a {"totototototototototototototototo", 32};
            T const b {"totototototototototototototototototototototototototototototototo", 64};
            state.ResumeTiming();
            a = b;
            benchmark::DoNotOptimize(a);
        }
        state.counters["itr"] = benchmark::Counter(state.iterations(), benchmark::Counter::kIsRate);
    }

    template <typename T>
    void constructor_copyassign_short_test(benchmark::State& state) noexcept {
        for (auto _ : state) {
            state.PauseTiming();
            T a {"toto", 4};
            T const b {"toto", 4};
            state.ResumeTiming();
            a = b;
            benchmark::DoNotOptimize(a);
        }
        state.counters["itr"] = benchmark::Counter(state.iterations(), benchmark::Counter::kIsRate);
    }

    template <typename T>
    void constructor_move_long_test(benchmark::State& state) noexcept {
        for (auto _ : state) {
            state.PauseTiming();
            T b {"totototototototototototototototo", 32};
            state.ResumeTiming();
            T a {std::move(b)};
            benchmark::DoNotOptimize(a);
        }
        state.counters["itr"] = benchmark::Counter(state.iterations(), benchmark::Counter::kIsRate);
    }

    template <typename T>
    void constructor_move_short_test(benchmark::State& state) noexcept {
        for (auto _ : state) {
            state.PauseTiming();
            T b {"toto", 4};
            state.ResumeTiming();
            T a {std::move(b)};
            benchmark::DoNotOptimize(a);
        }
        state.counters["itr"] = benchmark::Counter(state.iterations(), benchmark::Counter::kIsRate);
    }

    template <typename T>
    void constructor_moveassign_long_test(benchmark::State& state) noexcept {
        for (auto _ : state) {
            state.PauseTiming();
            T a {"totototototototototototototototo", 32};
            T b {"totototototototototototototototo", 32};
            state.ResumeTiming();
            a = std::move(b);
            benchmark::DoNotOptimize(a);
        }
        state.counters["itr"] = benchmark::Counter(state.iterations(), benchmark::Counter::kIsRate);
    }

    template <typename T>
    void constructor_moveassign_short_test(benchmark::State& state) noexcept {
        for (auto _ : state) {
            state.PauseTiming();
            T a {"toto", 4};
            T b {"toto", 4};
            state.ResumeTiming();
            a = std::move(b);
            benchmark::DoNotOptimize(a);
        }
        state.counters["itr"] = benchmark::Counter(state.iterations(), benchmark::Counter::kIsRate);
    }

    template <typename T>
    void constructor_fwdit_long_test(benchmark::State& state) noexcept {
        char const data[] {'l', 'o', 'n', 'g', 'l', 'o', 'n', 'g', 'l', 'o', 'n', 'g', 'l', 'o', 'n', 'g', 'l', 'o', 'n', 'g', 'l', 'o', 'n', 'g', 'l', 'o', 'n', 'g', 'l' , 'o', 'n', 'g'};
        for (auto _ : state) {
            T a {&data[0], &data[0] + 32};
            benchmark::DoNotOptimize(a);
        }
        state.counters["itr"] = benchmark::Counter(state.iterations(), benchmark::Counter::kIsRate);
    }

    template <typename T>
    void constructor_fwdit_short_test(benchmark::State& state) noexcept {
        char const data[] {'t', 'o', 't', 'o'};
        for (auto _ : state) {
            T a {&data[0], &data[0] + 4};
            benchmark::DoNotOptimize(a);
        }
        state.counters["itr"] = benchmark::Counter(state.iterations(), benchmark::Counter::kIsRate);
        state.counters["itr"] = benchmark::Counter(state.iterations(), benchmark::Counter::kIsRate);
    }

} // namespace wiz
