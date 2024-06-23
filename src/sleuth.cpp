#include "sleuth.hpp"

#include <iostream>
#include <fstream>

Sleuth::Sleuth(
    std::string& pattern,
    size_t num_threads
) : m_pattern(pattern),
    m_threads(),
    m_book(new Book),
    m_printer(m_book),
    m_is_to_show_filename(true)
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

        std::ifstream file_to_search_in(hook->path, std::ios_base::in);

        if(!file_to_search_in.good())
        {
            hook->page->add_line(std::cerr, "grep: " + hook->path + ": Permission denied");
            hook->page->set_page_finished();
            file_to_search_in.close();
            continue;
        }

        std::string line;
        std::string prefix;

        if(m_is_to_show_filename)
        {
            prefix = hook->path;
            prefix += ":";
        }

        while(getline(file_to_search_in, line))
        {
            if(std::regex_search(line, m_pattern))
            {
                if(m_is_to_show_filename)
                {
                    line = std::string(prefix) + line;
                }

                hook->page->add_line(std::cout, line);
            }
        }

        hook->page->set_page_finished();
        file_to_search_in.close();
    }
}

void Sleuth::set_is_to_show_filename(bool is_to_show) noexcept
{
    m_is_to_show_filename = is_to_show;
}

void Sleuth::add_path(std::string& path) noexcept
{
    enqueue(Sleuth::HookPtr(new Hook {
            .path = path,
            .page = Book::PagePtr(m_book->add_page())
        }
    ));
}

void Sleuth::report_false_hook(std::string& false_hook_directory_name) noexcept
{
    auto page = m_book->add_page();
    page->add_line(std::cerr, "grep: " + false_hook_directory_name + ": Permission denied");
    page->set_page_finished();
}

void Sleuth::set_investigation_finished(void) noexcept
{
    set_finished();
}
