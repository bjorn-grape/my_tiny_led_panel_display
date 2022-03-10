#include "IPPage.h"

IPPage::IPPage(canvas_ptr canvas) : Page(canvas) {
    length = rgb_matrix::DrawText(offscreen_canvas, font,
                                  x, y + font.baseline(),
                                  color, nullptr,
                                  line.c_str(), letter_spacing);
}

bool IPPage::init() {
    std::string command("hostname -I");

    std::array<char, 128> buffer;
    std::string result;

    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe)
    {
        std::cerr << "Couldn't start command." << std::endl;
        return 0;
    }
    while (fgets(buffer.data(), 128, pipe) != NULL) {
        std::cout << "Reading..." << std::endl;
        result += buffer.data();
    }
    auto returnCode = pclose(pipe);
    auto ip_line = std::string(result);
    std::string delimiter = " ";
    std::string token = ip_line.substr(0, ip_line.find(delimiter));
    this->ip_address = token;
}

void IPPage::display() {
    canvas_->Fill(255, 0, 0);
}

void IPPage::update(const std::string& name, const std::string& val){

}
