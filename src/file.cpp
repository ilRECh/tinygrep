#include <iostream>

#include "file.hpp"

bool File::open_path(std::string file_path) noexcept
{
    try {
        m_file.open(file_path);
    } catch(...) {
        std::cerr << "Something wrong with the file" << std::endl;
    }

    return false;
}
