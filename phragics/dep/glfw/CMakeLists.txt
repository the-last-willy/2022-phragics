find_package(glfw3 REQUIRED)

add_library(phragics_dep_glfw INTERFACE)
add_library(phragics::dep::glfw ALIAS phragics_dep_glfw)

target_link_libraries(phragics_dep_glfw
	INTERFACE
		glfw
		phragics
		phragics::dep::glad)
