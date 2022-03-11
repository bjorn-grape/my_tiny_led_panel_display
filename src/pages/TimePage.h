#pragma once
#include "Page.h"

class TimePage : public Page {
public:
    TimePage(canvas_ptr);
    virtual bool init() ;
    virtual void display(bool is_same_page);
    virtual void update(const std::string& name, const std::string& val) ;

};
