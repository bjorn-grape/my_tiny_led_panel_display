#pragma once
#include <string>
#include <vector>

struct BusData {
    std::string name,
    unsigned hour,
    unsigned min,
};

class BusPage : public Page{
public:
    BusPage(canvas_ptr);
    virtual bool init() ;
    virtual void display(bool is_same_page);
    virtual void update(const std::string& name, const std::string& val) ;

private:
    bool need_refresh = false;
    int index = 0;
    unsigned entry_per_page = 2;
    std::vector<BusData> data;
};
