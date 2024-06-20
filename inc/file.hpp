#pragma once

#include <string>

class File
{
    private:

        File();

    public:

        /**
         * @brief Construct a new File object
         * 
         * @param file file path to examine
         */
        File(std::string file) throw();
};
