add_executable(phragics_example_imgui_demo)
add_executable(phragics::example::imgui_demo ALIAS phragics_example_imgui_demo)

target_sources(phragics_example_imgui_demo
	PRIVATE
		main.cpp)

target_include_directories(phragics_example_imgui_demo
	PRIVATE
		.)

target_link_libraries(phragics_example_imgui_demo
	PRIVATE
		phragics::dep::glfw
		phragics::dep::imgui)
