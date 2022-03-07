#pragma once
#include <memory>

enum DisplayType{
    STOP = 0,
    DEFAULT = 1,
};

class MatrixHandler {

public:
    MatrixHandler();
    ~MatrixHandler();
    auto init(int argc, char **argv) -> bool;
    auto loop() -> void;
    auto draw() -> void;
    auto set_display_type(DisplayType dt) -> void;

private:
    std::shared_ptr<RGBMatrix> canvas_;
    SelectedDisplay s_display = DisplayType::DEFAULT;
    bool is_init_ = false;
};

