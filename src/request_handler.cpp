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

        if (req.has_param("name")) {
            std::string page_name = "None";
            page_name = req.get_param_value("name");
            mh.set_page_name(page_name);
        }

        if (req.has_param("modifier")) {
            std::string modifier = "";
            modifier = req.get_param_value("modifier");
            mh.set_modifier(modifier);
        }
        std::cout << "GET: /page/?name=" << page_name << "\n";
        if (page_name == "stop") {
            std::cout << "Stopping the server...";
            mh.stop();
            server.stop();
        }

        std::stringstream ss;
//        auto btn1 = html_elm_gen::make_button(ss.str(), "/page/", "name", "none", 20);
        ss << html_elm_gen::make_button("STOP", "/", "name", "stop", 20, 33);
        ss << html_elm_gen::make_button("IP", "/", "name", "ip", 20, 34);
        ss << html_elm_gen::make_button("TIME", "/", "name", "time", 20, 33);
        ss << html_elm_gen::make_button("<", "/", "modifier", "prev", 20, 25);
        ss << html_elm_gen::make_button("BUS", "/", "name", "bus", 20, 50);
        ss << html_elm_gen::make_button(">", "/", "modifier", "next", 20, 25);
        res.set_content(ss.str(), "text/html");
    }

}
