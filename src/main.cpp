#include <iostream>
#include <string>
#include <signal.h>
#include <functional>
#include "MatrixHandler.h"


std::function<void(void)> InterruptHandler;

void signal_handler(int){
  InterruptHandler();
  std::cout << "Received interrupt\n";
}

void register_signals(MatrixHandler& mh, httplib::Server& server){
    InterruptHandler = [&mh, &server](){
        mh.set_display_type(DisplayType::STOP);
        server.stop();
    };
    signal(SIGTERM, signal_handler);
    signal(SIGINT, signal_handler);
}

int main(int argc, char **argv) {
    std::cout << "Creating Matrix handler\n";
    auto mh = MatrixHandler();
    if(! mh.init(argc, argv)) {
        std::cout << "Could not create Matrix handler!\n";
        return 1;
    }

    std::thread t([&mh](){mh.loop()});
    t.detach();

    httplib::Server svr;

    svr.Get("/", [](const httplib::Request &, httplib::Response &res) {
        res.set_content("Hello World!", "text/plain");
    });
    svr.Get(R"(/page/(\d+))", [&](const Request& req, Response& res) {
        auto val = req.matches[0];
        auto numbers = req.matches[1];
        auto str_res  = val + "->" + numbers;
        res.set_content(str_res, "text/plain");
    });

    svr.listen("0.0.0.0", 8080);

    return 0;
}
