#include <iostream>
#include <string>
#include <signal.h>
#include <functional>
#include "MatrixHandler.h"


std::function<void(void)> InterruptHandler;

void signal_handler(int){
  InterruptHandler();
  std::cout << "Received interrupt\n";
}

int main(int argc, char **argv) {
    std::cout << "Creating Matrix handler\n";
    auto mh = MatrixHandler();
    if(! mh.init(argc, argv)) {
        std::cout << "Could not create Matrix handler!\n";
        return 1;
    }
    InterruptHandler = [&mh](){
        mh.set_display_type(DisplayType::STOP);
    };
    signal(SIGTERM, signal_handler);
    signal(SIGINT, signal_handler);
    mh.loop();
    return 0;
}
