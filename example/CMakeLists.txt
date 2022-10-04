add_executable(example_sandbox)

target_sources(example_sandbox
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/sandbox/main.cpp)

target_include_directories(example_sandbox
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/sandbox)

target_link_libraries(example_sandbox
	PRIVATE
	piecewise)
