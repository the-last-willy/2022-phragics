#include "interface.hpp"

#include "store.hpp"

#include <any>
#include <string>

namespace phragics::metadata {

template<> auto API<Store*>::Collections::Collection::Elements::Element::anyValue() const -> std::any {
    auto& store = *context.handle;
    auto& collection = store.collections[context.collectionId.value];
    return collection.elements[context.elementId.value];
}

template<> auto API<Store*>::Collections::Collection::Elements::count() const -> std::size_t {
    auto& store = *context.handle;
    auto collectionIt = store.collections.find(context.collectionId.value);
    if(collectionIt == end(store.collections)) {
        return 0;
    } else {
        return collectionIt->second.elements.size();
    }
}

template<> auto API<Store*>::Collections::Collection::Elements::create(std::any any) const -> Element {
    auto& store = *context.handle;
    auto& collection = store.collections[context.collectionId.value];
    auto elementId = collection.nextId++;
    collection.elements[elementId] = std::move(any);
    return {context, ElementId{elementId}};
}

template<> auto API<Store*>::Collections::create(TypeId) const -> Collection {
    auto& store = *context.handle;
    auto id = store.nextId++;
    store.collections.insert(std::pair<int, metadata::Collection>(id, metadata::Collection()));
    return {context, id};
}

template<> auto API<Store*>::Types::any() const -> TypeId {
    return TypeId{std::type_index(typeid(std::any))};
}

template<> auto API<Store*>::Types::i32() const -> TypeId {
    return TypeId{std::type_index(typeid(int))};
}

template<> auto API<Store*>::Types::string() const -> TypeId {
    return TypeId{std::type_index(typeid(std::string))};
}

}