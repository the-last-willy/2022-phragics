#pragma once

#include <filesystem>
#include <fstream>
#include <sstream>

namespace phragics {

auto content(const std::filesystem::path& p) -> std::string {
    std::ifstream t(p);
    std::stringstream buffer;
    buffer << t.rdbuf();
    return buffer.str();
}

}
