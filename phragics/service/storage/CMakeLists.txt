add_library(phragics_storage)
add_library(phragics::storage ALIAS phragics_storage)
target_sources(phragics_storage
    PRIVATE
        storage.cpp)
target_link_libraries(phragics_storage
    PUBLIC
        phragics)

add_executable(phragics_storage_test)
target_sources(phragics_storage_test
    PRIVATE
        interface.specs.cpp)
target_link_libraries(phragics_storage_test
    PRIVATE
        phragics::storage
        Catch2::Catch2WithMain)

catch_discover_tests(phragics_storage_test)
