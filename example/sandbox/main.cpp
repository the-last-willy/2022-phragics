#include "piecewise/common.hpp"

#include <filesystem>
#include <map>
#include <optional>
#include <vector>
#include <string>

using namespace pcws;

using FileId = int;

using Path = std::filesystem::path;

struct File {
	FileId id = -1;
	Path path;

	std::optional<std::string> content;

	auto is_loaded() const -> bool {
		return content.has_value();
	}
};

struct FileManager {
	std::vector<std::filesystem::path> include_directories;

	std::map<RebindableR<FileId>, File> id_to_file;
	std::map<RebindableR<Path>, File> path_to_file;
	FileId next_id = 0;

	void load(const std::filesystem::path& p) {
		auto full_path = Path();
		// Searches for a full path that exists.
		{
			for(auto&& dir : include_directories) {
				auto candidate = dir / p;
				if(exists(full_path)) {
					full_path = std::move(candidate);
				}
			}
		}
		// Create the file resource.
		{

		}
		// Load file content.
		if(!full_path.empty()) {

		}
	}

	auto opt_ref(const Path& p) -> File*
};

struct Preprocessor {

};

auto main() -> int {

}
