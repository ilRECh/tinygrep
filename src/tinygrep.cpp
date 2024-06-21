#include <iostream>

#include "tinygrep.hpp"

TinyGrep::TinyGrep(
    std::string pattern,
    std::string file_path
) noexcept(false) : 
    m_file(file_path), m_finder(pattern)
{}

void TinyGrep::run(void) noexcept
{
    std::ifstream file_to_search_in;
    std::string line;

    while(m_file.next(file_to_search_in))
    {
        const std::string& current_path = m_file.get_path();

        while(getline(file_to_search_in, line))
        {
            if(m_finder.has_pattern(line))
            {
                std::cout << current_path << ":" << line << '\n';
            }
        }

        file_to_search_in.close();
    }
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
