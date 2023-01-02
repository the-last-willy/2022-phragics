#pragma once

#include <filesystem>
#include <fstream>
#include <optional>
#include <vector>

namespace phragics::storage {

class PersistentFile {
public:

};

class TransientFile {
public:

};

class File {
public:
    File();

    auto path() const -> const std::filesystem::path& { return path_; }

    auto isPersistent() const -> bool { return persistent_; }
    auto isTransient() const -> bool { return transient_; }

private:
    std::filesystem::path path_;

    std::optional<PersistentFile> persistent_;
    std::optional<TransientFile> transient_;
};

}