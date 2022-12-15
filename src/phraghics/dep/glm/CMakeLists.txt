find_package(glm REQUIRED COMPONENTS glm)

add_library(phragics_dep_glm INTERFACE)
add_library(phragics::dep::glm ALIAS phragics_dep_glm)

target_link_libraries(phragics_dep_glm
	INTERFACE
		glm::glm
		phragics::common)
