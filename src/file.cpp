#include <iostream>

#include "file.hpp"

File::File(std::string file_path) noexcept(false) :
    m_item(file_path), m_current_path(nullptr)
{}

bool File::next(std::ifstream &file_to_search_in) noexcept(false)
{
    while(m_item != end(m_item))
    {
        if(m_item->is_regular_file())
        {
            if(m_current_path == nullptr || *m_current_path != m_item->path())
            {
                file_to_search_in.open(m_item->path());
                m_current_path = &m_item->path();
                return true;
            }
        }

        auto item_copy = m_item;

        try {
            ++item_copy;
            m_item = item_copy;
        } catch(std::filesystem::filesystem_error &e) {
            std::cerr << e.what() << std::endl;
            item_copy = m_item;
            item_copy.disable_recursion_pending();
        } catch(...) {
            std::cerr << "Unknown error" << std::endl;
            throw;
        }
    }

    return false;
}
