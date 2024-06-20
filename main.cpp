#include <iostream>

#include "tinygrep.hpp"

#define EXACT_NUMBER_OF_ARGS 3

/**
 * @brief Print the program's usage to the standard output
 * 
 */
static void usage(void)
{
    std::cout << "Usage: tinygrep <pattern> <directory_or_file>" << std::endl;
}

int main(int argc, char **argv)
{
    if(argc != EXACT_NUMBER_OF_ARGS)
    {
        usage();
        return EXIT_FAILURE;
    }

    return TinyGrep::start(*(argv + 1), *(argv + 2));
}
