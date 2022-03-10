#include "TimePage.h"

TimePage::TimePage(canvas_ptr canvas) : Page(canvas) {}

bool TimePage::init() {

}

void TimePage::display() {
    canvas_->Fill(0, 255, 0);
}

void TimePage::update(const std::string &name, const std::string &val) {

}