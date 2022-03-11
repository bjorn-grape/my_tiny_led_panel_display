#pragma once

#include <string>
#include <sstream>

namespace html_elm_gen {

	auto make_button(const std::string& name,
                     const std::string& url,
                     const std::string& key,
                     const std::string& value,
                     unsigned height=100,
                     unsigned width=100) -> std::string;


}


