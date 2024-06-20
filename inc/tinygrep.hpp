#pragma once

#include <string>

#include "file.hpp"
#include "finder.hpp"

class TinyGrep
{
    private:

        TinyGrep();

        File m_file;
        Finder m_finder;

    public:
        /**
         * @brief Construct a new Tiny Grep object
         * 
         * @param pattern searching basic regex pattern
         * @param file file path to search in
         */
        TinyGrep(std::string pattern, std::string file) throw();

        /**
         * @brief Run the search
         * 
         */
        void run(void) throw();
};
