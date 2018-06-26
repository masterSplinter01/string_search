#include <iostream>
#include <fstream>
#include <boost/program_options.hpp>



#include "file_manager.h"

namespace po = boost::program_options;

int main(int ac, char* av[]) {

    po::options_description desc("Allowed options");
    desc.add_options()
            ("path,p", po::value<std::string>(), "directory")
            ("mask,m", po::value<std::string>(), "filename's masks")
            ("input,i", po::value<std::string>()->required(), "filename with string we search")
            ("output,o", po::value<std::string>(), "result file directory")
            ("help,h", "produce help message")
            ;
    po::variables_map vm;
    po::store(po::parse_command_line(ac, av, desc), vm);
    po::notify(vm);

    file_manager fm;


    if (vm.count("path")) {
        fm.set_path(vm["path"].as<std::string>());
    }
    else{
        fm.set_path(fs::current_path());
    }


    if (vm.count("mask")){
        fm.set_mask(vm["mask"].as<std::string>());
    } else{
        fm.set_mask("^(.*)");
    }


    if (vm.count("input")) {
        fm.set_search_substring_file(vm["input"].as<std::string>());
    }


    if (vm.count("output")){
        fm.set_output_file(vm["output"].as<std::string>());
    }
    else {
        std::cout<<"File with results not specified, default output file: " << fm.get_path() << "/result.txt" << std::endl;
        fm.set_output_file("result.txt");
    }

    if (vm.count("help")) {
       std::cout << desc << "\n";
        return 0;
    }

    view_directory(fm, fm.get_path());

    return 0;
}