#include "page.hpp"

Page::Page() : BaseQueue()
{}

void Page::add_line(
    std::ostream& output_stream,
    const std::string& line) noexcept
{
    enqueue(Page::LinePtr(new Line {.sentense = line, .stream = output_stream}));
}

std::list<Page::LinePtr> Page::get_lines(bool& is_growing) noexcept
{
    std::list<Page::LinePtr> lines;

    dequeue(lines, is_growing);

    return lines;
}

void Page::set_page_finished(void) noexcept
{
    set_finished();
}
