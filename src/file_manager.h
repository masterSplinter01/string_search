#pragma once
#include <iostream>
#include <experimental/filesystem>
#include <regex>
#include "search_algorithm.h"
#include <stdexcept>
#include <cassert>

namespace fs = std::experimental::filesystem;

class file_manager {

public:
    file_manager();
    file_manager(std::string dir_path, std::string file_mask, std::string input, std::string output);
    fs::path get_path();
    std::regex get_mask();
    std::ifstream& get_search_substring_file();
    std::ofstream& get_output_file();

    void set_path(const std::string& path);
    void set_mask(const std::string& mask);
    void set_search_substring_file(const std::string &substring);
    void set_output_file(const std::string& output);

private:
    fs::path _path;
    std::regex _mask;
    std::ifstream _search_substring_file;
    std::ofstream _output_file;

};

void view_directory(file_manager& fm, const fs::path& current_directory);

