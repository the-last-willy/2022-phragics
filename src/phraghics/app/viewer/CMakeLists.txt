add_executable(phragics_app_viewer)
add_executable(phragics::app:viewer ALIAS phragics_app_viewer)

target_sources(phragics_app_viewer
	PRIVATE
		main.cpp)

target_include_directories(phragics_app_viewer
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(phragics_app_viewer
	PRIVATE
		phragics::dep::all)
