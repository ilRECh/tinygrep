#include "page.hpp"

Page::Page() : BaseQueue(true)
{}

void Page::add_line(std::ostream& output_stream, const std::string& line) noexcept
{
    enqueue(Line {.sentense = line, .stream = output_stream} );
}

std::list<Line> Page::get_lines(bool& is_growing) noexcept
{
    std::list<Line> lines;

    dequeue(lines, is_growing);

    return lines;
}

void Page::set_page_finished(void) noexcept
{
    set_finished();
}
