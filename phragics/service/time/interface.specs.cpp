#include "phragics/common/default.hpp"
#include <phragics/timing/interface.hpp>

#include <catch2/catch_test_macros.hpp>

using API = timing::API<phragics::Default>;

TEST_CASE("The current time can be retrieved") {
    auto now = API().now().get();
    REQUIRE(now > 0);
}
