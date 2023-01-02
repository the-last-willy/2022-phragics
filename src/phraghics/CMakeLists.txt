add_subdirectory(dep)

add_library(phragics_common INTERFACE)
add_library(phragics::common ALIAS phragics_common)

target_include_directories(phragics_common
	INTERFACE
		..)

if(MSVC)
	target_compile_options(phragics_common
		INTERFACE
			/std:c++20)
endif()
