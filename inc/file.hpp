#pragma once

#include <string>
#include <fstream>
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
         * @brief The iterator to the element currently in use
         */
        std::filesystem::recursive_directory_iterator m_item;

        /**
         * @brief The current path in progress
         */
        const std::filesystem::path * m_current_path;

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
         * @param[out] file_to_search std::ifstream next file to search in
         * 
         * @return true - there is a file to search in
         *         false - no more files left
         */
        bool next(std::ifstream &file_to_search) noexcept(false);
};
