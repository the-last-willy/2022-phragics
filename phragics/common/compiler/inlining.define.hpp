#include "detect.define.hpp"

#if(PHRAGICS_IS_COMPILER_CLANG() || PHRAGICS_IS_COMPILER_GCC())
    #define ALWAYS_INLINED __attribute__((always_inline)) inline
    #define NEVER_INLINED __attribute__((noinline))
#elif(PHRAGICS_IS_COMPILER_MSVC())
    #define ALWAYS_INLINED __forceinline
    #define NEVER_INLINED __declspec(noinline)
#else
    // #warning "Inlining macros are not currently supported for your compiler. Features are disabled."
    #define ALWAYS_INLINED inline
    #define NEVER_INLINED
#endif

#include "detect.undef.hpp"
