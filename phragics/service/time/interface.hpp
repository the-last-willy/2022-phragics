#pragma once

#include <ctime>
#include <utility>

namespace timing {

template<typename Handle>
struct API {
    struct Context { Handle handle; };
    Context context;

    constexpr API(Handle handle = {}) : context({std::move(handle)}) {}

    struct Now {
        typedef struct : Context {} Context;
        Context context;

        auto get() -> std::time_t;
    };

    constexpr auto now() && -> Now {
        return {std::move(context)};
    }

    struct Timers {
        typedef struct : Context {} Context;
        Context context;
    };
};

}