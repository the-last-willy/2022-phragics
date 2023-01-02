add_executable(phragics_anew)

target_sources(phragics_anew
	PRIVATE
		main.cpp)

target_include_directories(phragics_anew
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(phragics_anew
	PRIVATE
		phragics::dep::all)
