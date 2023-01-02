#pragma once

#include "os.hpp"

#include <phragics/common/compiler/inlining.define.hpp>

#if PHRAGICS_IS_UNIX()
#   include <signal.h>
#endif

namespace phragics {

ALWAYS_INLINED
void breakpoint()
#if PHRAGICS_IS_UNIX()
{
    raise(SIGTRAP);
}
#else
#warning "void phragics::breakpoint(): Not currently supported for this compiler."
{}
#endif

}

#include <phragics/common/compiler/inlining.undef.hpp>