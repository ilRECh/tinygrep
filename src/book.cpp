#include "book.hpp"

Book::Book() : BaseQueue(false)
{}

std::shared_ptr<Page> Book::add_page(void) noexcept
{
    std::shared_ptr<Page> page(new Page);

    enqueue(page);

    return page;
}

std::shared_ptr<Page> Book::get_page(bool& is_growing) noexcept
{
    std::list<std::shared_ptr<Page>> page_list;

    dequeue(page_list, is_growing);

    if(page_list.empty())
    {
        return nullptr;
    }

    return *page_list.begin();
}

void Book::set_book_finished(void) noexcept
{
    set_finished();
}
