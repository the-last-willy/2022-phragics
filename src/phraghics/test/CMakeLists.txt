add_executable(phragics_test_unit)
add_executable(phragics::test::unit ALIAS phragics_test_unit)

target_sources(phragics_test_unit
	PRIVATE
		unit/communicating.cpp)

target_link_libraries(phragics_test_unit
	PRIVATE
		phragics::common
		phragics::dep::catch2)
