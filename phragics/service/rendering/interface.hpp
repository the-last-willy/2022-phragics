#pragma once

namespace rendering {

template<typename Handle>
struct API {
    struct Context { Handle handle; };
    Context context;

    struct OpenGL
};

}

