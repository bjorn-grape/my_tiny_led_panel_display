#include <iostream>
#include <sstream>
#include "../main.h"
#include "IPPage.h"
#include "graphics.h"

IPPage::IPPage(canvas_ptr canvas) : Page(canvas) {
   }

bool IPPage::init() {
    std::string command("hostname -I");

    std::array<char, 128> buffer;
    std::string result;

    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe)
    {
        std::cerr << "Couldn't start command." << std::endl;
        return false;
    }
    while (fgets(buffer.data(), 128, pipe) != NULL) {
        std::cout << "Reading..." << std::endl;
        result += buffer.data();
    }
    auto returnCode = pclose(pipe);
    auto ip_line = std::string(result);
    std::string delimiter = " ";
    std::string token = ip_line.substr(0, ip_line.find(delimiter));
    std::stringstream ss;
    ss << token << ":" << PORT;

    this->ip_address = ss.str();

    return true;
}

void IPPage::display(bool is_same_page) {
    //if (is_same_page)
    //        return;
    frame_canvas_->Fill(0, 100, 0);
    rgb_matrix::Color color(255, 255, 255);
    int  letter_spacing = 0;
    std::string fontpath ="myfont.bdf"; 
    rgb_matrix::Font font;
    if (!font.LoadFont(fontpath.c_str()))
    {
    	canvas_->Fill(40,100,255);
	    return;
    }
    int length = rgb_matrix::DrawText(frame_canvas_, font,
                                  30, 30,
                                  color, nullptr,
                                  ip_address.c_str(), letter_spacing);

    canvas_->SwapOnVSync(frame_canvas_);
}

void IPPage::update(const std::string& name, const std::string& val){

}
