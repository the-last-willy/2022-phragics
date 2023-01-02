find_package(assimp COMPONENTS assimp)

add_library(phragics_dep_assimp INTERFACE)
add_library(phragics::dep::assimp ALIAS phragics_dep_assimp)

target_link_libraries(phragics_dep_assimp
	INTERFACE
		assimp::assimp
		phragics::common)
