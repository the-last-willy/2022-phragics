#include "piecewise/common/numeric/rounding.hpp"

#include <catch2/catch_test_macros.hpp>

#include <array>
#include <tuple>
#include <string>

template<typename T>
struct Test {};

template<typename R, typename... Args>
struct Test<R(Args...)> {
	using Function = R(*)(Args...);
	using Input = std::tuple<Args...>;

	Input input;
	R expectation;

	Test(Input&& i, R&& r)
	: input(std::forward<Input>(i))
	, expectation(std::forward<R>(r))
	{}
};

template<typename R, typename... Args>
Test(std::tuple<Args...>, R) -> Test<R(Args...)>;

TEST_CASE("piecewise/common/numeric/rounding: Ceiled") {
	auto tests = std::array{
		Test(std::tuple(0, 1), 0),
		Test(std::tuple(3, 2), 4),
		Test(std::tuple(4, 3), 6),
		Test(std::tuple(5, 4), 8)
	};
	auto fn = [](auto& a, auto& b) { return pcws::ceiled(a, b); };
	for(int i = 0; i < size(tests); ++i) {
		SECTION("#" + std::to_string(i)) {
			auto t = &tests[i];
			auto input = &t->input;
			auto r = std::apply(fn, *input);
			REQUIRE(r == t->expectation);
		}
	}
}

TEST_CASE("piecewise/common/numeric/rounding: Ceiled quotient") {
	auto tests = std::array{
		Test(std::tuple(0, 1), 0),
		Test(std::tuple(5, 2), 3),
		Test(std::tuple(10, 3), 4),
		Test(std::tuple(19, 4), 5)
	};
	auto fn = [](auto& a, auto& b) { return pcws::ceiled_quotient(a, b); };
	for(int i = 0; i < size(tests); ++i) {
		SECTION("#" + std::to_string(i)) {
			auto t = &tests[i];
			auto r = std::apply(fn, t->input);
			REQUIRE(r == t->expectation);
		}
	}
}
