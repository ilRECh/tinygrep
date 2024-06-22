#pragma once

#include <string>
#include <memory>

#include "file.hpp"
#include "sleuth.hpp"

/**
 * @brief Main class which provides grep functionality
 */
class TinyGrep
{
    public:

        /**
         * @brief The main executing function
         * 
         * @param pattern 
         * @param file_path
         * 
         * @return int 
         */
        static int start(std::string pattern, std::string file_path);

    private:

        TinyGrep();

        /**
         * @brief The current file to search in
         */
        File m_file;

        /**
         * @brief A sleuth, who searches for clues
         */
        Sleuth m_sleuth;

    public:
        /**
         * @brief Construct a new TinyGrep object
         * 
         * @param pattern the basic regex pattern to match with
         * @param file_path the file path to search in
         */
        TinyGrep(std::string pattern, std::string file_path) noexcept(false);

        /**
         * @brief Run the search
         */
        void run(void) noexcept;
};
