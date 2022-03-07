#include "main.h"
#include "led-matrix.h"
#include "MatrixHandler.h"
#include <iostream>
#include <string>
#include <signal.h>


std::function<void(int)> InterruptHandler;


int main(int argc, char **argv) {
    auto mh = MatrixHandler();
    if(! mh.init(argc, argv)) {
        std::cout << "Could not create Matrix handler!\n";
        return 1;
    }
    InterruptHandler = [&mh](int){
        mh.set_display_type(DisplayType::STOP)
    };
    signal(SIGTERM, InterruptHandler);
    signal(SIGINT, InterruptHandler);
    mh.loop();
    return 0;
}
