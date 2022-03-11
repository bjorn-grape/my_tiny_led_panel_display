#include <iostream>
#include <string>
#include <signal.h>
#include <functional>
#include <thread>
#include "MatrixHandler.h"
#include "httplib.h"
#include "request_handler.h"

std::function<void(void)> InterruptHandler;

void signal_handler(int) {
    InterruptHandler();
    std::cout << "Received interrupt\n";
}

void register_signals(MatrixHandler &mh, httplib::Server &server) {
    InterruptHandler = [&mh, &server]() {
        mh.stop();
        server.stop();
    };
    signal(SIGTERM, signal_handler);
    signal(SIGINT, signal_handler);
}

int main(int argc, char **argv) {
    std::cout << "Creating Matrix handler\n";
    auto mh = MatrixHandler();
    if (!mh.init(argc, argv)) {
        std::cout << "Could not create Matrix handler!\n";
        return 1;
    }

    std::thread t([&mh]() { mh.loop(); });
    t.detach();

    httplib::Server svr;

    svr.Get("/", [&](const httplib::Request &req, httplib::Response &res) {
        request_handler::request_page(req, res, mh, svr);
    });

    svr.listen("0.0.0.0", PORT);

    return 0;
}
