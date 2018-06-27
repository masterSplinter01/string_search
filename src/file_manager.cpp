
#include "file_manager.h"

file_manager::file_manager(const std::string& dir_path, const std::string& file_mask, const std::string& input, const std::string& output):
        _path(dir_path), _search_substring_file(input), _output_file(output), _mask(file_mask)
{/*EMPTY*/}


const fs::path file_manager::get_path() {
    return _path;
}

const std::regex file_manager::get_mask() {
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
    //determine whether the path is relative or absolute
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

void file_manager::view_directory() {
    //iterate directories and files in current_directory

    boost::asio::thread_pool pool(std::thread::hardware_concurrency());

    for (auto &rsc : fs::recursive_directory_iterator(_path, fs::directory_options::skip_permission_denied)) {

        auto current_filename = rsc.path().filename().string();

        if (std::regex_match(current_filename, _mask) && fs::is_regular_file(rsc)) {
            auto absolute_file_path = rsc.path().string();
            boost::asio::post(pool,[this, absolute_file_path](){rabin_karp_search(_search_substring_file, _output_file, absolute_file_path);});

        }
    }

    pool.join();


}

