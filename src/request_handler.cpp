#include "request_handler.h"
#include <functional>
#include <thread>
#include "html_elm_gen.h"
#include "MatrixHandler.h"
#include "httplib.h"
#include "html_elm_gen.h"

namespace request_handler {
    auto request_page(const httplib::Request &req, httplib::Response &res,
                      MatrixHandler &mh, httplib::Server &server) -> void {
        std::string page_name = "None";
        if (req.has_param("name")) {
            page_name = req.get_param_value("name");
        }
        std::cout << "GET: /page/?name=" << page_name << "\n";
        if (page_name == "stop") {
            std::cout << "Stopping the server...";
            mh.stop();
            server.stop();
        }
        mh.set_page_name(page_name);
        std::stringstream ss;
//        auto btn1 = html_elm_gen::make_button(ss.str(), "/page/", "name", "none", 20);
        ss << html_elm_gen::make_button("STOP", "/page/", "name", "stop", 10);
        ss << html_elm_gen::make_button("IP", "/page/", "name", "ip", 20);
        ss << html_elm_gen::make_button("TIME", "/page/", "name", "time", 20);
        res.set_content(ss.str(), "text/html");
    }

}
