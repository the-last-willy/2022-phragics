cmake_minimum_required(VERSION 3.15)

project(PiecewiseEngine VERSION 0.0.0)

if(MSVC)
	add_compile_options(/W4 /std:c++20)
else()
endif()

add_subdirectory(example)
add_subdirectory(src)
add_subdirectory(test)

find_package(Catch2)

add_executable(catch2_test test/main.cpp)

# Use the global target
target_link_libraries(catch2_test Catch2::Catch2WithMain)
