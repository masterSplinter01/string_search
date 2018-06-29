#pragma  once
#include <boost/asio/thread_pool.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <experimental/filesystem>
#include <regex>

#include "search_algorithm.h"

namespace fs = std::experimental::filesystem;

void view_directory(substring& substr, const fs::path& path, const std::regex& mask,   std::ofstream &output_file);

std::string make_absolute_path(const fs::path& path, const std::string& filename);
