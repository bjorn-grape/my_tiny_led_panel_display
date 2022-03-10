#pragma once
#include "Page.h"

class TimePage : public Page {
    TimePage();
    virtual bool init() ;
    virtual void display() ;
    virtual void update(const std::string& name, const std::string& val) ;

};
