find_package(Catch2 REQUIRED)

################################################################################

add_executable(test_unit)

target_sources(test_unit
	PRIVATE
	../test/piecewise/common/numeric/rounding.cpp)

target_include_directories(test_unit
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/..)

target_link_libraries(test_unit
	PRIVATE
	Catch2::Catch2WithMain
	piecewise)

################################################################################

include(CTest)
include(Catch)

catch_discover_tests(test_unit)
