add_subdirectory(assimp)
add_subdirectory(catch2)
add_subdirectory(fmt)
add_subdirectory(glad)
add_subdirectory(glfw)
add_subdirectory(glm)
add_subdirectory(imgui)
add_subdirectory(stb)

add_library(phragics_dep_all INTERFACE)
add_library(phragics::dep::all ALIAS phragics_dep_all)

target_link_libraries(phragics_dep_all
	INTERFACE
		phragics::dep::assimp
		phragics::dep::catch2
		phragics::dep::fmt
		phragics::dep::glad
		phragics::dep::glfw
		phragics::dep::glm
		phragics::dep::imgui
		phragics::dep::stb)
