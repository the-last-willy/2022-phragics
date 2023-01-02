#pragma once

#include <filesystem>
#include <string>

namespace phragics_std {

auto file_to_string(const std::filesystem::path& fullpath) -> std::string;

}
