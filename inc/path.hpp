#pragma once

#include <string>
#include <functional>

extern "C"
{
    #include <sys/stat.h>
    #include <dirent.h>
    #include <errno.h>
}

/**
 * @brief Contains the current Path information
 * 
 */
class Path
{
    public:

        typedef std::function<void(const char *)> callback_func_t;

    private:

        Path();

        /**
         * @brief The grep utility does not print the filename,
         *        if the filename was passed instead of directory name
         * 
         */
        bool m_is_to_give_filename;

        /**
         * @brief Starting path
         */
        std::string m_starting_path;

        /**
         * @brief A Callback to call on each regular file found
         */
        callback_func_t m_handle_regular_file;

        /**
         * @brief A Callback to call on each permission denied err
         */
        callback_func_t m_handle_permission_denied;

        /**
         * @brief Iterate through subdirectories
         */
        void iterate_through_directories(const char * directory_path) noexcept;

    public:

        /**
         * @brief Construct a new Path object
         * 
         * @param file_path the Path path to examine
         * 
         * @throw std::filesystem::filesystem_error
         */
        Path(std::string file_path) noexcept;

        /**
         * @brief Iterate through directories recursively
         */
        void iterate(
            callback_func_t handle_regular_file,
            callback_func_t handle_permission_denied
        ) noexcept;

        /**
         * @brief Determines whether the initial path is file or directory
         * 
         * @details if it's a file, then there is no need to show the filename
         * 
         * @return true 
         * @return false 
         */
        bool get_is_starting_path_regfile(void) noexcept;
};
