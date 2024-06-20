#include <iostream>

#include "file.hpp"

File::File(std::string file) noexcept(false)
{
    std::cout << "Looking at the file: " << file << std::endl; 
}
