add_subdirectory(app)
add_subdirectory(common)
add_subdirectory(core)
add_subdirectory(dep)
add_subdirectory(example)
add_subdirectory(test)

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
