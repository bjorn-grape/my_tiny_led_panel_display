#include "MatrixHandler.h"
#include <thread>

MatrixHandler::MatrixHandler() {

}

MatrixHandler::~MatrixHandler() {
    canvas->Clear();
}

auto MatrixHandler::init(int argc, char **argv) -> bool {
    rgb_matrix::RGBMatrix::Options defaults;
    auto *tmp_ptr = rgb_matrix::RGBMatrix::CreateFromFlags(
            &argc, &argv, &defaults);
    if (!tmp_ptr)
        return false;
    canvas_ = std::shared_ptr(tmp_ptr);
    return true;
}

auto MatrixHandler::draw() -> {
    for (unsigned i = 0; i < 1000; ++i) {
        if (i % 2 == 0)
            canvas->Fill(255, 255, 0);
        else if (i % 2 == 1)
            canvas->Fill(255, 255, 255);

        std::this_thread::sleep_for(1000ms);
    }
}

auto MatrixHandler::set_display_type(DisplayType dt) -> void
{
    s_display = dt;
}


auto MatrixHandler::loop() -> {
    if (!is_init_)
        return;
    while (s_display != DisplayType::STOP)
    {
        draw();
    }
}

