find_package(glad COMPONENTS glad)

add_library(phragics_dep_glad INTERFACE)
add_library(phragics::dep::glad ALIAS phragics_dep_glad)

target_link_libraries(phragics_dep_glad
	INTERFACE
		glad::glad)
