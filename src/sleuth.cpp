#include "sleuth.hpp"

#include <iostream>
#include <fstream>

Sleuth::Sleuth(
    std::string pattern,
    size_t num_threads) :
    m_pattern(pattern),
    m_threads(),
    m_book(new Book),
    m_printer(m_book)
{
    for(size_t i = 0; i < num_threads; ++i)
    {
        m_threads.push_back(std::thread(&Sleuth::search, this));
    }
}

Sleuth::~Sleuth()
{
    for(auto& thread : m_threads)
    {
        thread.join();
    }

    m_book->set_book_finished();
}

void Sleuth::search(void) noexcept
{
    bool is_growing = true;

    while(is_growing)
    {
        HookPtr hook{nullptr};

        dequeue(hook, is_growing);

        if(hook == nullptr && !is_growing)
        {
            break;
        }

        auto page = m_book->add_page();

        std::ifstream file_to_search_in(hook->path, std::ios_base::in);

        if(!file_to_search_in.good())
        {
            page->add_line(std::cerr, "tinygrep: " + hook->path + ": Permission denied");
            continue;
        }

        std::string line;
        std::string prefix;

        if(hook->is_to_show_path)
        {
            prefix = hook->path;
            prefix += ":";
        }

        while(getline(file_to_search_in, line))
        {
            if(std::regex_search(line, m_pattern))
            {
                if(hook->is_to_show_path)
                {
                    line = std::string(prefix) + line;
                }

                page->add_line(std::cout, line);
            }
        }

        page->set_page_finished();
        file_to_search_in.close();
    }
}

void Sleuth::add_path(HookPtr path) noexcept
{
    enqueue(path);
}

void Sleuth::set_investigation_finished(void) noexcept
{
    set_finished();
}

