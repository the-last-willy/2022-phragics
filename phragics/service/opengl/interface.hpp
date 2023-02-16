#pragma once

namespace opengl {

template<typename Handle>
struct API {
    struct Context { Handle handle; };
    Context context;

    struct Buffers {
        Context context;

        struct Buffer {
            typedef struct C : Context { int bufferId; } Context;
        };

        auto create() const -> unsigned;
    };

    struct Programs {

    };

    struct Shaders {
		typedef struct C : Context { unsigned shaderId; } Context

		auto create() const ->
    };
};

}