add_library(phragics_timing)
add_library(phragics::timing ALIAS phragics_timing)
target_sources(phragics_timing
    PRIVATE
        timing.cpp)
target_link_libraries(phragics_timing
    PUBLIC
        phragics)

add_executable(phragics_timing_test)
target_sources(phragics_timing_test
    PRIVATE
        interface.specs.cpp)
target_link_libraries(phragics_timing_test
    PRIVATE
        phragics::timing
        Catch2::Catch2WithMain)

catch_discover_tests(phragics_timing_test)
