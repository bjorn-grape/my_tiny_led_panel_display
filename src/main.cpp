#include <iostream>
#include <string>
#include <signal.h>
#include <functional>
#include <thread>
#include "MatrixHandler.h"
#include "httplib.h"


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

    std::thread t([&mh](){mh.loop(); });
    t.detach();

    httplib::Server svr;

    svr.Get("/", [](const httplib::Request &, httplib::Response &res) {
        res.set_content("Hello World!", "text/plain");
    });
    svr.Get("/page/", [&](const httplib::Request& req, httplib::Response& res) {
	std::string page_name = "None";
	if (req.has_param("name"))
	{
		page_name = req.get_param_value("name"); 
	}	
	std::cout << "GET: /page/?name=" << page_name << "\n"; 
	if(page_name == "stop"){
		std::cout << "Stopping the server...";
		mh.set_display_type(DisplayType::STOP);
		svr.stop();
	}
	std::stringstream ss;
	ss << "You selected: " << page_name;

        res.set_content(ss.str(), "text/plain");
    });

    svr.listen("0.0.0.0", 8080);

    return 0;
}
