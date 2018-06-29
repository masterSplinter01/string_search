#include <iostream>
#include <fstream>
#include <boost/program_options.hpp>
#include <mutex>
#include <experimental/filesystem>
#include <regex>

#include "file_manager.h"

namespace po = boost::program_options;
namespace fs = std::experimental::filesystem;

std::mutex mtx;

int main(int ac, char* av[]){
    po::options_description desc("Allowed options");
    desc.add_options()
            ("path,p", po::value<std::string>(), "directory")
            ("mask,m", po::value<std::string>(), "filename's masks")
            ("input,i", po::value<std::string>()->required(), "filename with string we search") //input option is required
            ("output,o", po::value<std::string>(), "result file directory")
            ("help,h", "produce help message")
            ;
    po::variables_map vm;
    po::store(po::parse_command_line(ac, av, desc), vm);
    po::notify(vm);

    fs::path path;
    std::regex mask;
    std::string search_string_filename;
    std::ofstream output_file;

    if (vm.count("path")){
        path = vm["path"].as<std::string>();
    }
    else{
        path = fs::current_path();
    }

    if (vm.count("mask")){
        mask = vm["mask"].as<std::string>();
    } else{
        mask = "^(.*)";
    }

    if (vm.count("input")) {
        search_string_filename = make_absolute_path(path, vm["input"].as<std::string>());
    }

    if (vm.count("output")) {
        output_file.open(make_absolute_path(path, vm["output"].as<std::string>()));
    }
    else {
        std::cout<<"File with results not specified, default output file: " << path.string() << "result.txt" << std::endl;
        output_file.open(make_absolute_path(path, "result.txt"));
    }

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 0;
    }

    substring current_substr(search_string_filename);

   view_directory(current_substr, path, mask, output_file);


    return 0;



}