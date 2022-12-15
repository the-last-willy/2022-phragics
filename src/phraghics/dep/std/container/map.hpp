#pragma once

#include <map>

namespace phragics::std_ {

template<typename... Tr, typename K>
auto findPtr(std::map<Tr...>& m, const K& key) -> typename std::map<Tr...>::mapped_type* {
	auto it = m.find(key);
	if(it == end(m)) {
		return nullptr;
	} else {
		return &it->second;
	}
}

}
