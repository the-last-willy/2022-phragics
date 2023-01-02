#define PHRAGICS_IS_COMPILER_CLANG() (defined(__clang__) && defined(__GNUC__))
#define PHRAGICS_IS_COMPILER_GCC() (!defined(__clang__) && defined(__GNUC__))
#define PHRAGICS_IS_COMPILER_MSVC() (defined(_MSC_VER))

#if(!(PHRAGICS_IS_COMPILER_CLANG() || PHRAGICS_IS_COMPILER_GCC() || PHRAGICS_IS_COMPILER_MSVC()))
    #warning "Unsupported compiler. Some features might be disabled."
#endif

