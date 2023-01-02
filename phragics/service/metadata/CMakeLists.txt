add_library(phragics_metadata)
add_library(phragics::metadata ALIAS phragics_metadata)
target_sources(phragics_metadata
    PRIVATE
        metadata.cpp)
target_link_libraries(phragics_metadata
    PUBLIC
        phragics)

add_executable(phragics_metadata_test)
target_sources(phragics_metadata_test
    PRIVATE
        interface.specs.cpp)
target_link_libraries(phragics_metadata_test
    PRIVATE
        phragics::metadata
        Catch2::Catch2WithMain)

catch_discover_tests(phragics_metadata_test)
