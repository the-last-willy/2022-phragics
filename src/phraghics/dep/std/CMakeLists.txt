add_library(phragics_dep_std)
add_library(phragics::dep::std ALIAS phragics_dep_std)

target_sources(phragics_dep_std INTERFACE)
