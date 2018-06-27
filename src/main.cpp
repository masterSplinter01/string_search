#include <iostream>
#include <fstream>
#include <boost/program_options.hpp>
#include <boost/thread/mutex.hpp>

#include "file_manager.h"

namespace po = boost::program_options;

boost::mutex mtx;

int main(int ac, char* av[]) {

    /*desc keeps all program arguments, their types and descriptions*/
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

    file_manager fm;

    /*setting fm fields */
    // if user doesnt set path, we use current directory
    if (vm.count("path")) {
        fm.set_path(vm["path"].as<std::string>());
    }
    else{
        fm.set_path(fs::current_path());
    }

    //if user doesnt set mask, we use regex mask for any filename
    if (vm.count("mask")){
        fm.set_mask(vm["mask"].as<std::string>());
    } else{
        fm.set_mask("^(.*)");
    }

    //input option is requred, if user doesnt set input, program throws exception
    if (vm.count("input")) {
        fm.set_search_substring_file(vm["input"].as<std::string>());
    }

    //if user doesnt set output file, we create file in current path with default name result.txt
    if (vm.count("output")){
        fm.set_output_file(vm["output"].as<std::string>());
    }
    else {
        std::cout<<"File with results not specified, default output file: " << fm.get_path().string() << "result.txt" << std::endl;
        fm.set_output_file("result.txt");
    }

    if (vm.count("help")) {
       std::cout << desc << "\n";
        return 0;
    }


    fm.view_directory();

    return 0;
}