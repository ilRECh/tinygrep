#include "printer.hpp"

Printer::Printer(std::shared_ptr<Book> book) :
    m_book(book),
    m_printer_thread(&Printer::print_book, this)
{}

Printer::~Printer()
{
    try {
        m_printer_thread.join();
    } catch(...) {
        std::cerr << "Couldn't join the printer thread" << std::endl;
    }
}

void Printer::print_book(void) noexcept
{
    bool is_book_growing = true;

    while(is_book_growing)
    {
        auto page = m_book->get_page(is_book_growing);

        if(page != nullptr)
        {
            bool is_page_growing = true;

            while(is_page_growing)
            {
                auto lines = page->get_lines(is_page_growing);

                for(auto &line : lines)
                {
                    line->stream << line->sentense << '\n';
                }
            }
        }
    }
}
