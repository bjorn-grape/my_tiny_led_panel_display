#pragma once

#include <ctime>
#include <string>
#include <queue>

struct TimeInfo {
    std::time_t time_gone;

};

class BusData {
public:
    BusData ( std::string name,
            std::string dst,
            std::string src_name_code,
            std::string dst_name_code,
            unsigned buffer_size);

    void update();
private:
    std::string name_;
    std::string dst_name_short_;
    std::string src_name_code_;
    std::string dst_name_code_;
    std::queue <TimeInfo> time_infos_;
    unsigned buffer_size_ = 3;
};
