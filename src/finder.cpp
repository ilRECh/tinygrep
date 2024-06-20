#include <iostream>
#include <regex>

#include "finder.hpp"

bool Finder::set_pattern(std::string pattern) noexcept
{
    try {
        m_pattern = pattern;
    } catch(...) {
        std::cerr << "Incorrect pattern" << std::endl;
        return true;
    }

    return false;
}
