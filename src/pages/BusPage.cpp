#include "BusPage.h"
BusPage::BusPage(canvas_ptr canvas) : Page(canvas) {}

bool BusPage::init() {
    data.emplace_back({"3", 4, 45});
    data.emplace_back({"3", 6, 15});
    data.emplace_back({"3", 7, 23});
    data.emplace_back({"3", 8, 25});
    data.emplace_back({"2", 1, 25});
    data.emplace_back({"2", 4, 25});
    data.emplace_back({"2", 6, 25});
    return true;
}

auto format_data(const BusData& bdt) -> std::string {

}

void BusPage::display(bool is_same_page) {
    if (is_same_page && !need_refresh)
        return;
    need_refresh = false;
    frame_canvas_->Fill(100, 0, 100);
    rgb_matrix::Color color(255, 255, 0);
    int  letter_spacing = 0;
    std::string fontpath ="myfont.bdf";
    rgb_matrix::Font font;
    if (!font.LoadFont(fontpath.c_str()))
    {
        canvas_->Fill(40,100,255);
        return;
    }
    for (unsigned i = 0; i < entry_per_page, i++)
    {
        auto f_data = format_data(data[index + i]);
        rgb_matrix::DrawText(frame_canvas_, font,
                             30, (i + 1) * 30,
                             color, nullptr,
                             f_data.c_str(), letter_spacing);
    }

    canvas_->SwapOnVSync(frame_canvas_);
}

void BusPage::update(const std::string &name, const std::string &val) {
    if (val == "next")
        index += entry_per_page;
    else if (val == "prev")
        index -= entry_per_page;
    if (index < 0) {
        unsigned last_page_nb = data.size() / entry_per_page;
        index = entry_per_page * last_page_nb;
    } else if (index >= data.size())
    {
        index = 0;
    }

    need_refresh = true;

}
