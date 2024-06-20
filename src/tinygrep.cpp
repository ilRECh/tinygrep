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

    while(m_file.next(file_to_search_in) && file_to_search_in.good())
    {
        while(getline(file_to_search_in, line))
        {
            std::cout << line << std::endl;
            break;
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
    catch(std::filesystem::filesystem_error &e)
    {
        std::cerr << "tinygrep: " << e.what() << std::endl;
        return EXIT_FAILURE + 1;
    }
    catch(std::exception &e)
    {
        std::cerr << "tinygrep: " << e.what() << std::endl;
        return EXIT_FAILURE + 1;
    }
    catch(...)
    {
        std::cerr << "Unknown error" << std::endl;
        return EXIT_FAILURE + 1;
    }

    return EXIT_SUCCESS;
}
