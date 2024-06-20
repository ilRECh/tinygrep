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
         * @brief Construct a new Tiny Grep object
         * 
         * @param pattern searching basic regex pattern
         * @param file file path to search in
         * 
         * @throw empty exception in case if member initialization failed 
         */
        TinyGrep(std::string pattern, std::string file) noexcept(false);

        /**
         * @brief Run the search
         * 
         * @return 0 if no issues, 1 is something happened
         */
        int run(void) noexcept;
};
