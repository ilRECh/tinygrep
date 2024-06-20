#pragma once

#include <string>
#include <regex>

class Finder
{
    private:

        Finder();
    
        /**
         * @brief The basic regex pattern
         */
        std::regex m_pattern;
    
    public:

        /**
         * @brief Construct a new Finder object
         * 
         * @param pattern basic regex pattern to examine
         * 
         * @throw std::regex_error
         */
        Finder(std::string pattern) noexcept(false);
};
