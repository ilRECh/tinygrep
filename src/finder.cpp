#include <iostream>
#include <regex>

#include "finder.hpp"

Finder::Finder(std::string pattern) noexcept(false) :
    m_pattern(pattern)
{}
