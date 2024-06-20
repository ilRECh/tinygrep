#include <iostream>

#include "tinygrep.hpp"

TinyGrep::TinyGrep(
    std::string pattern,
    std::string file
) noexcept(false) : 
    m_file(file),
    m_finder(pattern)
{}

int TinyGrep::run(void) noexcept
{
    
}
