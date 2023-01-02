#pragma once

#include <filesystem>
#include <span>
#include <string>

namespace phragics::storage {

struct FileId {

};

template<typename Implementation>
struct API {
    struct Context { typename Implementation::Handle handle; };
    Context context;

    struct File {
        typedef struct : Context { FileId fileId; } Context;
        Context context;

        void close() const;
        void open() const;

        auto isPersistent() const -> bool;
        auto isTransient() const -> bool;

        void save() const;

        auto contentStr() const -> std::string {}
        auto path() const -> std::filesystem::path;
    };
    auto file(FileId id) -> File { return {context, id}; }

    struct Path {
        Context context;

        auto all() const -> std::span<std::filesystem::path>;
        auto add(std::filesystem::path) const -> bool;
        auto remove(std::filesystem::path) const -> bool;
    };

    auto create(std::filesystem::path) const -> FileId;
};

}