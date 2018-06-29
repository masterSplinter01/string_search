
#include "file_manager.h"

std::string make_absolute_path(const fs::path& path, const std::string& filename) {
    try {
        fs::path temp(filename);
        if (temp.is_relative()) {
            temp = path / temp;
        }
        return temp.string();
    }
    catch (fs::filesystem_error& e){
        std::cerr<<"Invalid file"<<std::endl;
        std::exit(1);
    }
}

void view_directory( substring& substr, const fs::path& path, const std::regex& mask, std::ofstream& output_file) {
    boost::asio::thread_pool pool(std::thread::hardware_concurrency());

    for (auto &rsc : fs::recursive_directory_iterator(path, fs::directory_options::skip_permission_denied)) {

        auto current_filename = rsc.path().filename().string();

        if (std::regex_match(current_filename, mask) && fs::is_regular_file(rsc)) {
            auto current_file_path = rsc.path().string();

            boost::asio::post(pool,[&substr, current_file_path, &output_file](){rabin_karp_search(substr, current_file_path, output_file);});

        }
    }

    pool.join();
}
