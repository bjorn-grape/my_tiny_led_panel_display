#pragma once
#include "httplib.h"
#include "MatrixHandler.h"
namespace request_handler {
    auto request_page(const httplib::Request &req, httplib::Response &res,
                      MatrixHandler &mh, httplib::Server &server) -> void;


}
