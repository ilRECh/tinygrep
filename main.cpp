#include <iostream>

#include "tinygrep.hpp"

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
    if(argc != 3)
    {
        usage();
        return 1;
    }
    else
    {
        int status = 0;

        try
        {
            TinyGrep grep(*(argv + 1), *(argv + 2));
            grep.run();
        }
        catch(...)
        {
            status = 1;
        }

        return status;
    }
}
