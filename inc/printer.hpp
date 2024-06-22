#pragma once

#include <thread>
#include <memory>

#include "book.hpp"

class Printer
{
    private:

        /**
         * @brief Shared book with pages to print
         */
        std::shared_ptr<Book> m_book;

        /**
         * @brief Printer thread
         */
        std::thread m_printer_thread;

        /**
         * @brief Print the book, page by page
         */
        void print_book(void) noexcept;

    public:

        /**
         * @brief Construct a new Printer object
         */
        Printer();

        /**
         * @brief Destroy the Printer object
         */
        ~Printer();
};
