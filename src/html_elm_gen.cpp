#include "html_elm_gen.h"


namespace html_elm_gen {



    auto make_button(const std::string& name,
                     const std::string& url,
                     const std::string& key,
                     const std::string& value,
                     unsigned height,
                     unsigned width) -> std::string
    {
        std::stringstream ss;
        ss << "<a href=\""
        << url << "?"
        << key << "="
        << value
        << "\" >"
        << "<input type=\"submit\" style=\"height:" << height
        << "%;width:" << width << "%;\" value=\"" << name << "\">"
        << "</input>"
        << "</a>";
        return ss.str();
    }


};
