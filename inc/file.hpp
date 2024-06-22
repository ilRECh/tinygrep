#pragma once

#include <string>
#include <filesystem>

/**
 * @brief Contains the current file information
 * 
 */
class File
{
    private:

        File();

        /**
         * @brief Current path
         */
        std::filesystem::path m_current_file;

        /**
         * @brief Recursive iterator through directories
         */
        std::filesystem::recursive_directory_iterator m_iter;

        /**
         * @brief Increases the iterator to the next available regular file
         * 
         * @return true  - there is next file available
         * @return false - reached the end and found no file
         */
        bool goto_next_file(void) noexcept;

        /**
         * @brief The grep utility does not print the filename,
         *        if the filename was passed instead of directory name
         * 
         */
        bool m_is_to_give_filename;

    public:

        /**
         * @brief Construct a new File object
         * 
         * @param file_path the file path to examine
         * 
         * @throw std::filesystem::filesystem_error
         */
        File(std::string file_path) noexcept(false);

        /**
         * @brief Get the next file to search in
         * 
         * @param[out] file_path file path to search in
         * @param[out] is_to_give_filename we should print the filename,
         *                                 only if the directory was specified
         *                                 as the path argument
         * 
         * @return true - there is a file to search in
         *         false - no more files left
         */
        bool next(std::string& file_path, bool& is_to_give_filename) noexcept;
};
