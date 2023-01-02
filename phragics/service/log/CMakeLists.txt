add_library(phragics_log INTERFACE)
add_library(phragics::log ALIAS phragics_log)
target_include_directories(phragics_log
    INTERFACE
        ../../../..)

add_executable(phragics_log_sandbox)
add_executable(phragics::log::sandbox ALIAS phragics_log_sandbox)
target_sources(phragics_log_sandbox
    PRIVATE
        main.cpp)
target_link_libraries(phragics_log_sandbox
    PRIVATE
        phragics::log)