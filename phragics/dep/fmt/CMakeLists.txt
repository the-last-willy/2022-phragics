find_package(fmt REQUIRED)

add_library(phragics_dep_fmt INTERFACE)
add_library(phragics::dep::fmt ALIAS phragics_dep_fmt)

target_link_libraries(phragics_dep_fmt
	INTERFACE
		fmt::fmt)
