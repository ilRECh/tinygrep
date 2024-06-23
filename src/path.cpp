#include <iostream>

#include "path.hpp"
#include <filesystem>

namespace fs = std::filesystem;

Path::Path(std::string file_path) noexcept :
    m_starting_path(file_path)
{}

void Path::iterate_through_directories(const char * directory_path) noexcept
{
    try
    {
        for(auto const& dirent : fs::directory_iterator(directory_path))
        {
            auto const &dirpath = dirent.path();

            if(dirent.is_directory())
            {
                iterate_through_directories(dirpath.c_str());
            }
            else
            {
                m_handle_regular_file(dirpath.c_str());
            }
        }
    }
    catch(...)
    {
        m_handle_permission_denied(directory_path);
        return;
    }
}

void Path::iterate(
    callback_func_t handle_regular_file,
    callback_func_t handle_permission_denied
) noexcept {
    if(get_is_starting_path_regfile())
    {
        handle_regular_file(m_starting_path.c_str());
    }
    else
    {
        m_handle_regular_file = handle_regular_file;
        m_handle_permission_denied = handle_permission_denied;

        iterate_through_directories(m_starting_path.c_str());
    }
}

bool Path::get_is_starting_path_regfile(void) noexcept
{
    if(!std::filesystem::is_directory(m_starting_path))
    {
        return true;
    }

    return false;
}
