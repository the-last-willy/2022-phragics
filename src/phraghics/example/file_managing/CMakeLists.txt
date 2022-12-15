add_executable(phragics_example_file_managing)
add_executable(phragics::example:file_managing ALIAS phragics_example_file_managing)

target_sources(phragics_example_file_managing
		PRIVATE
		main.cpp)

target_include_directories(phragics_example_file_managing
		PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(phragics_example_file_managing
		PRIVATE
		phragics::dep::all)
