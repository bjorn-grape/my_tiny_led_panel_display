#include "TimePage.h"
#include <ctime>
#include "graphics.h"

TimePage::TimePage(canvas_ptr canvas) : Page(canvas) {}

bool TimePage::init() {

    return true;
}

void TimePage::display(bool is_same_page) {
    int letter_spacing = 0;
    std::string fontpath = "myfont.bdf";
    rgb_matrix::Font font;
    if (!font.LoadFont(fontpath.c_str())) {
        canvas_->Fill(40, 100, 255);
        return;
    }

    canvas_->Fill(0, 0, 0);
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
    rgb_matrix::Color color(255, 255, 255);

    rgb_matrix::DrawText(frame_canvas_, font,
                         30, 30,
                         color, nullptr,
                         buf, letter_spacing);
}

void TimePage::update(const std::string &name, const std::string &val) {

}
