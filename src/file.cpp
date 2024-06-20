#include <iostream>

#include "file.hpp"

File::File(std::string file) throw()
{
    std::cout << "Looking at: " << file << std::endl; 
}
