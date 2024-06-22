#include "book.hpp"

Book::Book() : BaseQueue()
{}

Book::PagePtr Book::add_page(void) noexcept
{
    Book::PagePtr page(new Page);

    enqueue(page);

    return page;
}

Book::PagePtr Book::get_page(bool& is_growing) noexcept
{
    Book::PagePtr page{nullptr};

    dequeue(page, is_growing);

    return page;
}

void Book::set_book_finished(void) noexcept
{
    set_finished();
}
