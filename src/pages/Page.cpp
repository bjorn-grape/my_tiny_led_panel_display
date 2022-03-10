#include "Page.h"

Page::Page(canvas_ptr canvas) : canvas_(canvas) {
	frame_canvas_ = canvas_->CreateFrameCanvas();
}
