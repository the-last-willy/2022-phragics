#pragma once

#include <any>
#include <map>

namespace phragics::metadata {

struct Collection {
    int nextId = 1;
    int typeId = 0;
    std::map<int, std::any> elements;
};

struct Store {
    int nextId = 1;
    std::map<int, Collection> collections;
};

}