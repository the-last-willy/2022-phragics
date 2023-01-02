find_package(glfw3 REQUIRED)
find_package(imgui REQUIRED COMPONENTS imgui)

add_library(phragics_dep_imgui)
add_library(phragics::dep::imgui ALIAS phragics_dep_imgui)

target_sources(phragics_dep_imgui
	PRIVATE
		${CMAKE_BINARY_DIR}/imgui_impl_glfw.h
		${CMAKE_BINARY_DIR}/imgui_impl_glfw.cpp
		${CMAKE_BINARY_DIR}/imgui_impl_opengl3.cpp
		${CMAKE_BINARY_DIR}/imgui_impl_opengl3.h)

target_include_directories(phragics_dep_imgui
	PUBLIC
		${CMAKE_BINARY_DIR})

target_link_libraries(phragics_dep_imgui
	PUBLIC
		glfw
		imgui::imgui
		phragics)
