#include "filesystem.hpp"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace phragics_std {

auto file_to_string(const std::filesystem::path& fullpath) -> std::string {
    std::ifstream file(fullpath);
	if(!file.is_open())
	{
		throw std::runtime_error("Failed to open file.");
	}
	else
	{
		std::stringstream buffer;
		buffer << file.rdbuf();
		return buffer.str();
	}
}

}