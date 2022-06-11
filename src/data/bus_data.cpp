#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
#include "bus_data.h"
#include "graphics.h"
BusData::BusData(std::string name,
                 std::string dst,
                 std::string src_name_code,
                 std::string dst_name_code,
                 unsigned buffer_size = 3)
        : name_(name),
          dst_name_short_(dst),
          src_name_code_(dst),
          dst_name_code_(dst),
          buffer_size_(buffer_size) {
}

void BusData::update() {
    std::time_t current_time = std::time(nullptr);
    auto second_since_epoch = std::asctime(std::localtime(&current_time));
    std::stringstream ss();
    constexpr auto url = "http://transport.opendata.ch/v1/connections";

    std::string src = "?from=Zurich,Kappeli&";
    std::string dst = "?from=Zurich,Kappeli&";

}