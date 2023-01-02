#include "filesystem.hpp"

#include <fstream>

namespace phragics_std {

auto file_to_string(const std::filesystem::path& fullpath) -> std::string {
    std::ifstream file(fullpath);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

}