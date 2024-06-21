#include <iostream>

#include "file.hpp"

File::File(std::string file_path) noexcept(false) :
    m_item(file_path), m_current_path()
{}

bool File::next(std::ifstream &file_to_search_in) noexcept(false)
{
    while(m_item != end(m_item))
    {
        if(m_item->is_regular_file())
        {
            auto next_path = m_item->path().string();

            if(m_current_path != next_path)
            {
                file_to_search_in.open(m_item->path(), std::ios_base::in);

                if(file_to_search_in.good())
                {
                    m_current_path = next_path;
                    return true;
                }
                else
                {
                    std::cerr << "tinygrep: " << m_item->path() << ": Permission denied" << std::endl;
                }
            }
        }

        auto item_copy = m_item;
        bool success = false;

        while(!success)
        {
            try {
                ++item_copy;
                m_item = item_copy;
                success = true;
            } catch(std::filesystem::filesystem_error &e) {
                std::cerr << "tinygrep: " << m_item->path() << ": " << e.what() << std::endl;
                item_copy = m_item;
                item_copy.disable_recursion_pending();
            } catch(...) {
                std::cerr << "Unknown error" << std::endl;
                throw;
            }
        }
    }

    return false;
}

const std::string& File::get_path(void) const noexcept
{
    return m_current_path;
}
