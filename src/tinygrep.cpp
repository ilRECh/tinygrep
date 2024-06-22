#include <iostream>

#include "tinygrep.hpp"

TinyGrep::TinyGrep(
    std::string pattern,
    std::string file_path
) noexcept(false) : 
    m_file(file_path),
    m_sleuth(pattern)
{}

void TinyGrep::run(void) noexcept
{
    bool is_to_give_filename = false;
    std::string file_path;

    while(m_file.next(file_path, is_to_give_filename))
    {
        m_sleuth.add_path(
            Sleuth::HookPtr(
                new Hook {
                    .is_to_show_path = is_to_give_filename,
                    .path = file_path
                }
            )
        );
    }

    m_sleuth.set_investigation_finished();
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
