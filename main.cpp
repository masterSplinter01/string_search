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
            ("input,i", po::value<std::string>(), "filename with string we search")
            ("output,o", po::value<std::string>(), "result file directory")
            ("help,h", "produce help message")
            ;
    po::variables_map vm;
    po::store(po::parse_command_line(ac, av, desc), vm);
    po::notify(vm);

    file_manager fm;

    if (vm.count("path") == 1){
        fm.set_path(vm["path"].as<std::string>());
        //std::cout<<vm["path"].as<std::string>()<<"\n";
    }

    if (vm.count("mask") == 1){
        //std::cout<<vm["mask"].as<std::string>()<<"\n";
        fm.set_mask(vm["mask"].as<std::string>());

    }

    if (vm.count("input") == 1){
        fm.set_search_substring_file(vm["input"].as<std::string>());
    }

    if (vm.count("output") == 1){
        fm.set_output_file(vm["output"].as<std::string>());
    }

    if (vm.count("help")) {
       std::cout << desc << "\n";
        return 0;
    }



    view_directory(fm, fm.get_path());






    return 0;
}