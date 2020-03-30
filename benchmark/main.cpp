#include <functional>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#include <benchmark/benchmark.h>
#include <elixir/String.hpp>
#pragma clang diagnostic pop

#include <string>
#include <string/string.hpp>

#include "capacity.hpp"
#include "constructor.hpp"
#include "function.hpp"
#include "operation.hpp"

namespace wiz {

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wglobal-constructors"

// string

//    // constructor
//    BENCHMARK_TEMPLATE(constructor_default_test, wiz::string);
//    BENCHMARK_TEMPLATE(constructor_default_test, std::string);
//    BENCHMARK_TEMPLATE(constructor_default_test, elixir::String);
//
//    BENCHMARK_TEMPLATE(constructor_cstring_short_test, wiz::string);
//    BENCHMARK_TEMPLATE(constructor_cstring_short_test, std::string);
//    BENCHMARK_TEMPLATE(constructor_cstring_short_test, elixir::String);
//
//    BENCHMARK_TEMPLATE(constructor_fwdit_long_test, wiz::string);
//    BENCHMARK_TEMPLATE(constructor_fwdit_long_test, std::string);
//    BENCHMARK_TEMPLATE(constructor_fwdit_long_test, elixir::String);
//
//    BENCHMARK_TEMPLATE(constructor_fwdit_short_test, wiz::string);
//    BENCHMARK_TEMPLATE(constructor_fwdit_short_test, std::string);
//    BENCHMARK_TEMPLATE(constructor_fwdit_short_test, elixir::String);
//
//    BENCHMARK_TEMPLATE(constructor_cstring_long_test, wiz::string);
//    BENCHMARK_TEMPLATE(constructor_cstring_long_test, std::string);
//    BENCHMARK_TEMPLATE(constructor_cstring_long_test, elixir::String);
//
//    BENCHMARK_TEMPLATE(constructor_copy_long_test, wiz::string);
//    BENCHMARK_TEMPLATE(constructor_copy_long_test, std::string);
//    BENCHMARK_TEMPLATE(constructor_copy_long_test, elixir::String);
//
//    BENCHMARK_TEMPLATE(constructor_copy_short_test, wiz::string);
//    BENCHMARK_TEMPLATE(constructor_copy_short_test, std::string);
//    BENCHMARK_TEMPLATE(constructor_copy_short_test, elixir::String);
//
//    BENCHMARK_TEMPLATE(constructor_copyassign_long_test, wiz::string);
//    BENCHMARK_TEMPLATE(constructor_copyassign_long_test, std::string);
//    BENCHMARK_TEMPLATE(constructor_copyassign_long_test, elixir::String);
//
    BENCHMARK_TEMPLATE(constructor_copyassign_long_worst_test, wiz::string);
//    BENCHMARK_TEMPLATE(constructor_copyassign_long_worst_test, std::string);
//    BENCHMARK_TEMPLATE(constructor_copyassign_long_worst_test, elixir::String);
//
//    BENCHMARK_TEMPLATE(constructor_copyassign_short_test, wiz::string);
//    BENCHMARK_TEMPLATE(constructor_copyassign_short_test, std::string);
//    BENCHMARK_TEMPLATE(constructor_copyassign_short_test, elixir::String);
//
//    BENCHMARK_TEMPLATE(constructor_move_long_test, wiz::string);
//    BENCHMARK_TEMPLATE(constructor_move_long_test, std::string);
//    BENCHMARK_TEMPLATE(constructor_move_long_test, elixir::String);
//
//    BENCHMARK_TEMPLATE(constructor_move_short_test, wiz::string);
//    BENCHMARK_TEMPLATE(constructor_move_short_test, std::string);
//    BENCHMARK_TEMPLATE(constructor_move_short_test, elixir::String);
//
//    BENCHMARK_TEMPLATE(constructor_moveassign_long_test, wiz::string);
//    BENCHMARK_TEMPLATE(constructor_moveassign_long_test, std::string);
//    BENCHMARK_TEMPLATE(constructor_moveassign_long_test, elixir::String);
//
//    BENCHMARK_TEMPLATE(constructor_moveassign_short_test, wiz::string);
//    BENCHMARK_TEMPLATE(constructor_moveassign_short_test, std::string);
//    BENCHMARK_TEMPLATE(constructor_moveassign_short_test, elixir::String);
//
//    // capacity
//    BENCHMARK_TEMPLATE(capacity_reserve_short_test, wiz::string);
//    BENCHMARK_TEMPLATE(capacity_reserve_short_test, std::string);
//    BENCHMARK_TEMPLATE(capacity_reserve_long_test, wiz::string);
//    BENCHMARK_TEMPLATE(capacity_reserve_long_test, std::string);
//
//    BENCHMARK_TEMPLATE(capacity_shrink_short_test, wiz::string);
//    BENCHMARK_TEMPLATE(capacity_shrink_short_test, std::string);
//    BENCHMARK_TEMPLATE(capacity_shrink_long_test, wiz::string);
//    BENCHMARK_TEMPLATE(capacity_shrink_long_test, std::string);
//
//
//    // operation
//
//    BENCHMARK_TEMPLATE(operation_clear_long_test, wiz::string);
//    BENCHMARK_TEMPLATE(operation_clear_long_test, std::string);
//
//    BENCHMARK_TEMPLATE(operation_clear_short_test, wiz::string);
//    BENCHMARK_TEMPLATE(operation_clear_short_test, std::string);
//
//    // function
//
//    BENCHMARK_TEMPLATE(function_equal_string_long_test, wiz::string);
//    BENCHMARK_TEMPLATE(function_equal_string_long_test, std::string);
//    BENCHMARK_TEMPLATE(function_equal_string_long_test, elixir::String);
//
//    BENCHMARK_TEMPLATE(function_equal_string_short_test, wiz::string);
//    BENCHMARK_TEMPLATE(function_equal_string_short_test, std::string);
//    BENCHMARK_TEMPLATE(function_equal_string_short_test, elixir::String);
//
//    BENCHMARK_TEMPLATE(function_equal_cstring_long_test, wiz::string);
//    BENCHMARK_TEMPLATE(function_equal_cstring_long_test, std::string);
//    BENCHMARK_TEMPLATE(function_equal_cstring_long_test, elixir::String);
//
//    BENCHMARK_TEMPLATE(function_equal_cstring_short_test, wiz::string);
//    BENCHMARK_TEMPLATE(function_equal_cstring_short_test, std::string);
//    BENCHMARK_TEMPLATE(function_equal_cstring_short_test, elixir::String);



#pragma clang diagnostic pop

} // namespace wiz

BENCHMARK_MAIN();
