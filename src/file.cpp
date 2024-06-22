#include <iostream>

#include "file.hpp"

File::File(std::string file_path) noexcept(false) :
    m_current_file(file_path), m_iter(), m_is_to_give_filename(true)
{
    namespace fs = std::filesystem;

    if(fs::is_directory(m_current_file))
    {
        m_iter = fs::recursive_directory_iterator(m_current_file);
        m_current_file.clear();

        goto_next_file();
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

bool File::next(std::ifstream &file_to_search_in, std::string& file_path) noexcept(false)
{
    if(m_current_file.empty())
    {
        return false;
    }

    bool success = false;

    while(!success)
    {
        file_to_search_in.open(m_current_file, std::ios_base::in);

        if(file_to_search_in.good())
        {
            if(m_is_to_give_filename)
            {
                file_path = m_current_file.string() + ":";
            }

            success = true;
            goto_next_file();
        }
        else
        {
            std::cerr << "tinygrep: " << m_current_file << ": Permission denied" << std::endl;

            if(!goto_next_file())
            {
                break;
            }
        }
    }

    return success;
}
