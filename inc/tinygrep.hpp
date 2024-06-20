#pragma once

#include <string>

#include "file.hpp"
#include "finder.hpp"

class TinyGrep
{
    private:

        TinyGrep();

        /**
         * @brief The current file to search in
         */
        File m_file;

        /**
         * @brief The finder, which searches for patterns 
         */
        Finder m_finder;

    public:
        /**
         * @brief Construct a new TinyGrep object
         * 
         * @param pattern the basic regex pattern to match with
         * @param file_path the file path to search in
         */
        TinyGrep(std::string pattern, std::string file_path) noexcept;

        /**
         * @brief Run the search
         * 
         * @return 0 if no issues, 1 is something happened
         */
        int run(void) noexcept;
};
