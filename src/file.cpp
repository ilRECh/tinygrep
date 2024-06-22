#include <iostream>

#include "file.hpp"

File::File(std::string file_path) noexcept(false) :
    m_current_file(file_path), m_iter(), m_is_to_give_filename(true)
{
    namespace fs = std::filesystem;

    if(fs::is_directory(m_current_file))
    {
        m_iter = fs::recursive_directory_iterator(m_current_file);
        m_current_file = *m_iter;

        while(!fs::is_regular_file(m_current_file))
        {
            goto_next_file();
        }
    }
    else
    {
        // assuming the path was a file
        m_is_to_give_filename = false;
    }
}

bool File::goto_next_file(void) noexcept
{
    m_current_file.clear();

    while(m_iter != end(m_iter))
    {
        auto item_copy = m_iter;
        bool success = false;

        while(!success)
        {
            try {
                ++item_copy;
                m_iter = item_copy;
                success = true;
            } catch(std::filesystem::filesystem_error &e) {
                std::cerr << "tinygrep: " << m_iter->path() << ": " << e.what() << std::endl;
                item_copy = m_iter;
                item_copy.disable_recursion_pending();
            } catch(...) {
                std::cerr << "Unknown error" << std::endl;
            }
        }

        if(m_iter != end(m_iter) && m_iter->is_regular_file())
        {
            m_current_file = m_iter->path();
            return true;
        }
    }

    return false;
}

bool File::next(
    std::string& file_path,
    bool& is_to_give_filename
) noexcept {
    if(m_current_file.empty())
    {
        return false;
    }

    is_to_give_filename = m_is_to_give_filename;
    file_path = m_current_file.string();
    goto_next_file();

    return true;
}
