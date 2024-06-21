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
        Finder(std::string pattern) noexcept(false) : m_pattern(pattern)
        {}

        /**
         * @brief Matches the pattern against a string to see
         *        if there is a occurence
         * 
         * @param line the string to match against
         * @return true there is a pattern in the string
         * @return false no pattern in the string
         */
        inline bool has_pattern(std::string &line) noexcept
        {
            return std::regex_search(line, m_pattern);
        }
};
