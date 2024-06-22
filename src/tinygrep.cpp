#include <iostream>

#include "tinygrep.hpp"

TinyGrep::TinyGrep(
    std::string pattern,
    std::string file_path
) noexcept(false) : 
    m_file(file_path),
    m_pattern(pattern),
    m_printer()
{}

void TinyGrep::run(void) noexcept
{
    std::ifstream file_to_search_in;
    std::string file_path;
    std::string line;

    // while(m_file.next(file_to_search_in, file_path))
    // {
    //     while(getline(file_to_search_in, line))
    //     {
    //         if(std::regex_search(line, m_pattern))
    //         {
    //             m_printer.m_page.add_line(std::cout, line);
    //         }
    //     }

    //     file_to_search_in.close();
    // }

    // m_printer.m_page.set_page_finished();
}

int TinyGrep::start(
    std::string pattern,
    std::string file_path
) {
    try
    {
        TinyGrep grep(pattern, file_path);
        grep.run();
    }
    catch(std::exception &e)
    {
        std::cerr << "tinygrep: " << e.what() << std::endl;
        return EXIT_FAILURE + 1;
    }
    catch(...)
    {
        std::cerr << "tinygrep: Unknown error" << std::endl;
        return EXIT_FAILURE + 1;
    }

    return EXIT_SUCCESS;
}
