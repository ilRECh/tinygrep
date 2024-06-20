#include <iostream>

#include "tinygrep.hpp"

#define EXIT_OK 0
#define EXIT_ERR 1
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
        return EXIT_ERR;
    }
    else
    {
        int status = EXIT_OK;

        try
        {
            TinyGrep grep(*(argv + 1), *(argv + 2));
            grep.run();
        }
        catch(...)
        {
            status = EXIT_ERR;
        }

        return status;
    }
}
