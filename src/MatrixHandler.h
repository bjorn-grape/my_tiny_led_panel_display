#pragma once
#include <led-matrix.h>
#include <memory>
#include <unordered_map>
#include "Page.h"

enum DisplayType{
    STOP = 0,
    DEFAULT = 1,
};

typedef std::unordered_map<std::string, std::shared_ptr<Page>> pagemap;

class MatrixHandler {

public:
    MatrixHandler();
    ~MatrixHandler();
    auto init(int argc, char **argv) -> bool;
    auto loop() -> void;
    auto draw() -> void;
    auto stop() -> void;
    auto set_page_name(const std::string& name) -> bool;

private:
    auto set_display_type(DisplayType dt) -> void;
    std::shared_ptr<rgb_matrix::RGBMatrix> canvas_;
    DisplayType s_display = DisplayType::DEFAULT;
    bool is_init_ = false;
    pagemap pmap_;
    std::string page_name_;
};

