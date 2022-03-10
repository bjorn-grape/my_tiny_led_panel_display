#pragma once
#include "Page.h"

class IPPage : public Page{
public:
    IPPage(canvas_ptr);
    virtual bool init();
    virtual void display();
    virtual void update(const std::string& name, const std::string& val);

private:
    std::string ip_address;
    std::string port;
};
