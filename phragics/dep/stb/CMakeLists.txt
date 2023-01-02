find_package(stb COMPONENTS stb)

add_library(phragics_dep_stb)
add_library(phragics::dep::stb ALIAS phragics_dep_stb)

target_sources(phragics_dep_stb
	PRIVATE
		all.cpp)

target_include_directories(phragics_dep_stb
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(phragics_dep_stb
	PUBLIC
		stb::stb)
