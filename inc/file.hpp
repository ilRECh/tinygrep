#pragma once

#include <string>
#include <fstream>

class File
{
    private:

        /**
         * @brief A file with contents
         */
        std::ifstream m_file;

    public:

        /**
         * @brief Construct a new File object
         * 
         * @param file_path the file path to examine
         * 
         * @return false - no issues
         *         true - something wrong with the file path
         */
        bool open_path(std::string file_path) noexcept;
};
