#pragma once

#include <vector>
#include <string>
#include <regex>

#include "base_queue.hpp"
#include "book.hpp"
#include "printer.hpp"

struct Hook
{
    bool is_to_show_path;
    std::string path;
};

template class BaseQueue<Hook>;

/**
 * @brief Thread pool of searchers
 */
class Sleuth : private BaseQueue<Hook>
{
    private:

        /**
         * @brief The basic regex pattern to search for
         */
        std::regex m_pattern;

        /**
         * @brief Vector to store worker threads
         */
        std::vector<std::thread> m_threads;

        /**
         * @brief A Book with all the results to print, page by page
         */
        std::shared_ptr<Book> m_book;

        /**
         * @brief A thread, which prints the book
         */
        Printer m_printer;

        /**
         * @brief Searches the path for clues
         */
        void search(void) noexcept;

    public:

        typedef BaseQueue::BaseQueueElem HookPtr;

        /**
         * @brief Construct a new Sleuth object with given number of threads
         *
         * @param pattern the pattern to search for
         * @param num_threads number of threads
         */
        Sleuth(
            std::string pattern,
            size_t num_threads = std::thread::hardware_concurrency()
        );

        /**
         * @brief Destroy the Sleuth object and stop the thread pool
         * 
         */
        ~Sleuth();

        /**
         * @brief Add the path to search for the clues in 
         * 
         * @param path 
         */
        void add_path(HookPtr path) noexcept;

        /**
         * @brief When there is no more hooks to investigate for clues ->
         *        finish investigation
         */
        void set_investigation_finished(void) noexcept;
};
