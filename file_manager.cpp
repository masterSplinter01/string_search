#include "file_manager.h"

file_manager::file_manager(std::string dir_path, std::string file_mask, std::string input, std::string output):
        _path(dir_path) {
    std::regex temp_reg(file_mask);
    _mask = temp_reg;

    _search_substring_file.open(input);
    _output_file.open(output);
}

file_manager::file_manager(): _path(), _mask(), _search_substring_file(), _output_file()
{/* EMPTY */}

fs::path file_manager::get_path() {
    return _path;
}

std::regex file_manager::get_mask() {
    return _mask;
}

void file_manager::set_path(const std::string& path) {
    this->_path = path;
}

void file_manager::set_mask( const std::string& mask) {
    this->_mask = mask;
}

void file_manager::set_search_substring_file(const std::string &substring) {
    fs::path temp(substring);

    try {
        if (temp.is_relative()) {
            temp = this->_path / temp;
        }
        if (_search_substring_file.is_open()) {
            _search_substring_file.close();
        }

        _search_substring_file.open(temp.string());
    }
    catch (std::fstream::failure& e){
        std::cerr<<"Opening substring file error"<<std::endl;
        std::exit(1);
    }

}

void file_manager::set_output_file(const std::string& output) {
    fs::path temp(output);
    try {
        if (temp.is_relative()) {
            temp = this->_path / temp;

        }

        if (_output_file.is_open()) {
            _output_file.close();
        }

        _output_file.open(temp.string());
    }
    catch (std::fstream::failure& e){
        std::cerr<<"Opening output file error"<<std::endl;
        
        std::exit(1);
    }
}

std::ifstream &file_manager::get_search_substring_file() {
    return _search_substring_file;
}

std::ofstream &file_manager::get_output_file() {
    return _output_file;
}

void view_directory(file_manager &fm, const fs::path& current_directory) {
        std::ifstream str;
    try {
        for (auto &rsc : fs::directory_iterator(current_directory)) {
            auto current_filename = rsc.path().filename().string();


            if (std::regex_match(current_filename, fm.get_mask()) && fs::is_regular_file(rsc)) {

                try {
                    str.open(rsc.path().string());
                    fm.get_output_file() << rsc.path().string() << " ";
                }
                catch (std::fstream::failure &e) {
                    std::cout << e.what() << std::endl;
                }
                catch (...) {
                    std::cout << "Something went wrong..." << std::endl;
                }
                rabin_karp_search(fm.get_search_substring_file(), str, fm.get_output_file());
                str.close();
            } else if(fs::is_directory(rsc)) {
                view_directory(fm, rsc);
            }

        }
    }
    catch(fs::filesystem_error& e){
        std::cout<<e.what()<<std::endl;
        return;
    }



}
