#pragma once

#include <string>
#include <list>
#include <iostream>
#include <functional>
#include <utility>

#include "base_queue.hpp"

struct Line
{
    std::string sentense;
    std::ostream& stream;
};

template class BaseQueue<Line>;

/**
 * @brief A page for printing
 */
class Page : private BaseQueue<Line>
{
    public:

        /**
         * @brief Construct a new Page object
         */
        Page();

        /**
         * @brief Add a line to the page to print it, when the time comes
         * 
         * @param output_stream 
         * @param line 
         */
        void add_line(std::ostream& output_stream, const std::string& line) noexcept;

        /**
         * @brief Get the lines in the page
         * 
         * @param is_growing whether the page is growing
         * @return std::list<Line> current lines to print
         */
        std::list<Line> get_lines(bool& is_growing) noexcept;

        /**
         * @brief Mark the page as finished
         */
        void set_page_finished(void) noexcept;
};
