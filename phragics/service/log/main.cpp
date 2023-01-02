#include "logging.hpp"

#include <iostream>

int main() {
    auto logger = Logger();
    auto ctx = Context();
    ctx.logger = &logger;

    auto id = LoggingApi(ctx).logs().create("ok");
    auto str = LoggingApi(ctx).logs().id(id).get();
    std::cout << str << std::endl;
}
