#pragma once
#include <iostream>
#include <experimental/filesystem>
#include <regex>
#include "search_algorithm.h"
#include <stdexcept>
#include <boost/thread/thread_pool.hpp>
#include <boost/asio/thread_pool.hpp>
#include <thread>
#include <boost/asio.hpp>

namespace fs = std::experimental::filesystem;

class file_manager {

public:
    file_manager() = default;
    file_manager(const std::string& dir_path, const std::string& file_mask, const std::string& input, const std::string& output);
    const fs::path get_path();
    const std::regex get_mask();
     std::ifstream& get_search_substring_file();
     std::ofstream& get_output_file();

    void set_path(const std::string& path);
    void set_mask(const std::string& mask);
    void set_search_substring_file(const std::string &substring);
    void set_output_file(const std::string& output);
    void view_directory();

private:
    fs::path _path;
    std::regex _mask;
    std::ifstream _search_substring_file;
    std::ofstream _output_file;

};



