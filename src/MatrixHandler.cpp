#include "led-matrix.h"
#include "MatrixHandler.h"
#include <thread>
#include "pages/Page.h"
#include "pages/IPPage.h"
#include "pages/TimePage.h"
#include "pages/BusPage.h"

using namespace std::chrono_literals;


MatrixHandler::MatrixHandler() {
}

MatrixHandler::~MatrixHandler() {
    canvas_->Clear();
}

auto MatrixHandler::init(int argc, char **argv) -> bool {
    rgb_matrix::RGBMatrix::Options defaults;
    auto *tmp_ptr = rgb_matrix::RGBMatrix::CreateFromFlags(
            &argc, &argv, &defaults);
    if (!tmp_ptr)
        return false;
    canvas_ = std::shared_ptr<rgb_matrix::RGBMatrix>(tmp_ptr);
    pmap_["ip"] = std::make_shared<IPPage>(canvas_);
    pmap_["time"] = std::make_shared<TimePage>(canvas_);
    pmap_["bus"] = std::make_shared<BusPage>(canvas_);
    for (auto &elm : pmap_)
    elm.second->init();
    is_init_ = true;
    return true;
}

auto MatrixHandler::draw() -> void {
    if (!pmap_.count(page_name_)) {
        canvas_->Fill(255, 255, 255);
        return;
    }
    bool is_same_page = page_name_ ==  last_rendered_page_name;
    pmap_[page_name_]->display(is_same_page);
    last_rendered_page_name = page_name_;
}

auto MatrixHandler::set_display_type(DisplayType dt) -> void {
    s_display = dt;
}

auto MatrixHandler::stop() -> void {
    set_display_type(DisplayType::STOP);
}

auto MatrixHandler::set_page_name(const std::string &name) -> bool {
    if (!pmap_.count(name))
        return false;
    page_name_ = name;
    return true;
}

auto MatrixHandler::set_modifier(const std::string &name) -> bool {
    if (!pmap_.count("bus"))
        return false;
    pmap_["bus"]->update("modifier", name);
    return true;
}

auto MatrixHandler::loop() -> void {
    if (!is_init_)
        return;
    while (s_display != DisplayType::STOP) {
        draw();
        std::this_thread::sleep_for(sleep_ms * 1ms);
    }
    canvas_->Clear();
}

