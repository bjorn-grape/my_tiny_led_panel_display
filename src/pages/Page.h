#pragma once

typedef std::shared_ptr<rgb_matrix::RGBMatrix> canvas_ptr;

class Page {
public:
    Page(canvas_ptr canvas);
    virtual bool init() = 0;
    virtual void display() = 0;
    virtual void update(const std::string& name, const std::string& val) = 0;

protected:
    canvas_ptr canvas_;
};
