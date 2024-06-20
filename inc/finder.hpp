#pragma once

#include <string>

class Finder
{
    private:
    
        Finder();
    
    public:

        /**
         * @brief Construct a new Finder object
         * 
         * @param pattern basic regex pattern to examine
         */
        Finder(std::string pattern) throw();
};
