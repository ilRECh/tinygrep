#pragma once

#include <memory>

#include "base_queue.hpp"
#include "page.hpp"

template class BaseQueue<Page>;

class Book : private BaseQueue<Page>
{
    public:

        /**
         * @brief Shared pointer typedef
         * 
         */
        typedef BaseQueue::BaseQueueElem PagePtr;

        /**
         * @brief Construct a new Book object
         */
        Book();

        /**
         * @brief Create a new page, add it to the Book,
         *        and share it with the requester
         */
        std::shared_ptr<Page> add_page(void) noexcept;

        /**
         * @brief Get the next available page
         * 
         * @param is_growing whether the Book is still growing
         * @return std::shared_ptr<Page> the page to print
         */
        std::shared_ptr<Page> get_page(bool& is_growing) noexcept;

        /**
         * @brief Mark the Book as finished
         */
        void set_book_finished(void) noexcept;
};
