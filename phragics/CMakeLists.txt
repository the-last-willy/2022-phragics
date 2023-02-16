find_package(Catch2)

enable_testing()
include(Catch)

add_library(phragics INTERFACE)
target_include_directories(phragics
    INTERFACE
        ..)

add_subdirectory(app/dag)
add_subdirectory(app/viewer)
add_subdirectory(dep)
add_subdirectory(service/log)
add_subdirectory(service/metadata)
add_subdirectory(service/storage)
add_subdirectory(service/time)
