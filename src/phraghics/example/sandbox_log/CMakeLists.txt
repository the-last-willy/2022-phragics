add_executable(phragics_example_sandbox_log)

target_sources(phragics_example_sandbox_log
	PRIVATE
		main.cpp)

target_link_libraries(phragics_example_sandbox_log
	PRIVATE
		phragics::dep::all)
