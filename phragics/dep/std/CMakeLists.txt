add_library(phragics_dep_std)
add_library(phragics::dep::std ALIAS phragics_dep_std)
target_sources(phragics_dep_std
    PRIVATE
        filesystem/filesystem.cpp)
target_include_directories(phragics_dep_std
    PRIVATE
        .)
