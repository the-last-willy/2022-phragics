#pragma once

#include <string>
#include <utility>
#include <vector>

struct LoggerAction {

};

namespace LoggerActions {

};

struct LogEntry {
    std::string content;
};

template<typename Context>
struct LoggingApi {
    struct Request { Context context; };
    Request req;

    constexpr LoggingApi(Context ctx) : req({std::move(ctx)}) {}

    struct Logs {
        typedef struct : Request {} Request;
        Request req;

        struct Id {
            typedef struct : Request { int id = 0; } Request;
            Request req;

            // Methods.

            /// Returns the corresponding log.
            auto get() -> std::string;
        };

        constexpr auto id(int i) -> Id {
            return {std::move(req), i};
        }

        // Methods.

        void clear();

        /// Creates a new log entry.
        /// @returns The id of the newly created log entry.
        auto create(std::string log) -> int;
    };

    constexpr auto logs() -> Logs {
        return {std::move(req)};
    }

    struct Settings {
        typedef struct : Request {} Request;
        Request req;
    };

    constexpr auto settings() && -> Settings {
        return {std::move(req)};
    }
};

struct Logger {
    std::vector<std::string> logs;
};

struct Context {
    Logger* logger = nullptr;
};

template<> auto LoggingApi<Context>::Logs::Id::get() -> std::string {
    return req.context.logger->logs[req.id];
}

template<> auto LoggingApi<Context>::Logs::create(std::string str) -> int {
    auto& logs = req.context.logger->logs;
    auto id = size(logs);
    logs.push_back(std::move(str));
    return id;
}
