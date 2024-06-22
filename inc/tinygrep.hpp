#pragma once

#include <string>
#include <regex>
#include <memory>

#include "file.hpp"
#include "printer.hpp"

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
         * @brief The basic regex pattern to search for
         */
        std::regex m_pattern;

        /**
         * @brief A Book with all the results to print, page by page
         * 
         */
        std::shared_ptr<Book> m_book;

        /**
         * @brief A thread, which prints the book
         */
        Printer m_printer;

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
