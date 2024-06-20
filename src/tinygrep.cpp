#include <iostream>

#include "tinygrep.hpp"

TinyGrep::TinyGrep(
    std::string pattern,
    std::string file
) throw() : 
    m_file(file),
    m_finder(pattern)
{

}

void TinyGrep::run(void) throw()
{
    
}
