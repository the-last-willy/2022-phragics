add_executable(phragics_sandbox)

target_sources(phragics_sandbox
	PRIVATE
		main.cpp)

target_include_directories(phragics_sandbox
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(phragics_sandbox
	PRIVATE
		phragics::dep::all)
