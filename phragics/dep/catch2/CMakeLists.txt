find_package(Catch2)

add_library(phragics_dep_catch2 INTERFACE)
add_library(phragics::dep::catch2 ALIAS phragics_dep_catch2)

target_link_libraries(phragics_dep_catch2
	INTERFACE
		Catch2::Catch2WithMain)
