#pragma once

#include <any>
#include <typeindex>
#include <utility>

namespace phragics::metadata {

struct CollectionId {
    int value = 0;
};

struct ElementId {
    int value = 0;
};

struct TypeId {
    std::type_index value;
};

template<typename Handle>
struct API {
    struct Context { Handle handle; };
    Context context;

    constexpr API(Handle handle) : context{std::move(handle)} {}

    struct Collections {
        Context context;

        struct Collection {
            typedef struct : Context { CollectionId collectionId; } Context;
            Context context;

            struct Elements {
                Context context;

                struct Element {
                    typedef struct : Context { ElementId elementId; } Context;
                    Context context;

                    auto anyValue() const -> std::any;
                };
                constexpr auto id(ElementId id) -> Element { return {context, id}; }

                auto count() const -> std::size_t;
                auto create(std::any) const -> Element;
            };
            constexpr auto elements() -> Elements { return {context}; }
        };
        constexpr auto id(CollectionId i) -> Collection { return {context, i}; }

        auto create(TypeId) const -> Collection;
    };
    constexpr auto collections() -> Collections { return {context}; }

    struct Types {
        Context context;

        struct Id {
            typedef struct : Context { TypeId typeId; } Context;
            Context context;
        };
        auto id(TypeId id) -> Id { return {context, id}; }

        auto any() const -> TypeId;
        auto i32() const -> TypeId;
        auto i64() const -> TypeId;
        auto string() const -> TypeId;
    };
    constexpr auto types() & -> Types { return {context}; }
    constexpr auto types() && -> Types { return {std::move(context)}; }
};

}