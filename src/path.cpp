#include <iostream>

#include "path.hpp"

static const std::string CURRENT_DIRECTORY = ".";
static const std::string PARENT_DIRECTORY = "..";

Path::Path(std::string file_path) noexcept : 
    m_starting_path(file_path)
{}

void Path::iterate_through_directories(const char * directory_path) noexcept
{
    DIR * directory = opendir(directory_path);

    if(directory == NULL)
    {
        m_handle_permission_denied(directory_path);
        return;
    }

    struct dirent * dirent = readdir(directory);

    while(dirent != NULL)
    {
        std::string full_path = std::string(directory_path);
        if(*full_path.rbegin() != '/')
        {
            full_path += '/';
        }
        full_path += std::string(dirent->d_name);

        if(
            dirent->d_type == DT_DIR &&
            dirent->d_name != CURRENT_DIRECTORY &&
            dirent->d_name != PARENT_DIRECTORY
        ) {
            iterate_through_directories(full_path.c_str());
        }
        else if(dirent->d_type == DT_REG)
        {
            m_handle_regular_file(full_path.c_str());
        }

        dirent = readdir(directory);
    }

    closedir(directory);
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
    struct stat sb;

    if(stat(m_starting_path.c_str(), &sb) == 0 && S_ISREG(sb.st_mode))
    {
        // it is a regular file
        return true;
    }

    return false;
}
