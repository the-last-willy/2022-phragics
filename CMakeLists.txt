cmake_minimum_required(VERSION 3.15)
project(phraghics)

if(MSVC)
	add_compile_options(/std:c++latest)
endif()

add_subdirectory(phragics)

# Your local config here.
