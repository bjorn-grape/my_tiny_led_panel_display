#include "led-matrix.h"
#include "MatrixHandler.h"
#include <thread>

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
    is_init_ = true;
    return true;
}

auto MatrixHandler::draw() -> void {
	int i = 34;
	if (i % 2 == 0)
            canvas_->Fill(255, 255, 0);
        else if (i % 2 == 1)
            canvas_->Fill(255, 255, 255);

        std::this_thread::sleep_for(1000ms);
}

auto MatrixHandler::set_display_type(DisplayType dt) -> void
{
    s_display = dt;
}


auto MatrixHandler::loop() -> void {
    if (!is_init_)
        return;
    while (s_display != DisplayType::STOP)
    {
        draw();
    }
    canvas_->Clear();
}

