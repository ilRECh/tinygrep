#pragma once

#include <string>
#include <regex>

class Finder
{
    private:
    
        /**
         * @brief The basic regex pattern
         */
        std::regex m_pattern;
    
    public:

        /**
         * @brief Set the pattern
         * 
         * @param pattern basic regex pattern to examine
         * 
         * @return false - no issues
         *         true - pattern examination failed
         */
        bool set_pattern(std::string pattern) noexcept;
};
