#include "interface.hpp"
#include "store.hpp"

#include <catch2/catch_test_macros.hpp>

using API = phragics::metadata::API<phragics::metadata::Store*>;

struct TestContext {
    TestContext()
    : store()
    , api(&store)
    {}

    phragics::metadata::API<phragics::metadata::Store*> api;
    phragics::metadata::Store store;
};

TEST_CASE("Fundamental types") {
    auto store = phragics::metadata::Store();
    auto api = API(&store);

    SECTION("There is an i32 type") {
        REQUIRE_NOTHROW(api.types().i32());
    }
    SECTION("There is a string type") {
        REQUIRE_NOTHROW(api.types().string());
    }
}

TEST_CASE("A new collection of strings can be created") {
    auto store = phragics::metadata::Store();
    auto elementType = API(&store).types().string();
    auto collection = API(&store).collections().create(elementType);
}

SCENARIO("Elements can be added to a collection") {
    GIVEN("An empty collection of anything") {
        auto ctx = TestContext();
        auto collection = ctx.api.collections().create(ctx.api.types().any());
        WHEN("A string \"test\" is added") {
            auto element = collection.elements().create(std::any(std::string("test")));
            THEN("There is one element in the collection") {
                auto count = collection.elements().count();
                REQUIRE(count == 1);
            } AND_THEN("That element is a string \"test\"") {
                auto any = element.anyValue();
                auto string = std::any_cast<std::string>(any);
                REQUIRE(string == "test");
            }
        }
    }
}
