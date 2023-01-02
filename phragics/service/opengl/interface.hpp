#pragma once

namespace opengl {

template<typename Handle>
struct API {
    struct Context { Handle handle; };
    Context context;

    struct Buffers {
        Context context;

        struct Buffer {
            typedef struct : Context { int bufferId; } Context;
        };

        auto create() const -> unsigned;
    };

    struct Programs {

    };

    struct Shaders {

    };
};

}