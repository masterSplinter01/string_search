#include <boost/program_options.hpp>
#include <experimental/filesystem>
#include <regex>
#include <boost/asio.hpp>
#include <boost/asio/thread_pool.hpp>
#include <cstdlib>

#include "rabin_karp_search.h"

namespace po = boost::program_options;
namespace fs = std::experimental::filesystem;

std::mutex fstream_mutex;
std::mutex iostream_mutex;

void search_substring(const std::string &substring_filename, const fs::path &path, const std::regex &mask,
	std::string &output_filename) {

	substring substring(substring_filename);
	std::ofstream output_file;
	output_file.exceptions(std::ifstream::failbit);

	try {
		output_file.open(output_filename);
	}
	catch (std::ios::failure& e) {
		std::cout << "Output file error" << std::endl;
		exit(1);
	}

	boost::asio::thread_pool pool(std::thread::hardware_concurrency());

	for (auto &rsc : fs::recursive_directory_iterator(path)) {

		auto filename = rsc.path().filename().string();
		if (std::regex_match(filename, mask) && fs::is_regular_file(rsc)) {
			auto file_path = rsc.path().string();
			boost::asio::post(pool, [&substring, file_path, &output_file]() {rabin_karp_search(substring, file_path, output_file); });

		}
	}

	pool.join();
}

int main(int ac, char* av[]) {
	po::options_description desc("Allowed options");
	desc.add_options()
		("path,p", po::value<std::string>(), "directory")
		("mask,m", po::value<std::string>(), "filename's masks")
		("input,i", po::value<std::string>()->required(), "filename with string we search") //input option is required
		("output,o", po::value<std::string>(), "result file directory")
		("help,h", "produce help message")
		;
	po::variables_map vm;

	try {
		po::store(po::parse_command_line(ac, av, desc), vm);
		po::notify(vm);
	}
	catch (boost::program_options::error& e) {
		std::cout << "invalid option: " << e.what() << std::endl;
		exit(1);
	}

	fs::path path;
	std::regex mask;
	std::string search_string_filename;
	std::string output_filename;

	//checking input arguments

	if (vm.count("path")) {
		path = vm["path"].as<std::string>();
	}
	else {
		path = fs::path();
	}

	if (vm.count("mask")) {
		try {

			mask = vm["mask"].as<std::string>();

		}
		catch (std::regex_error& e) {
			std::cout << "Invalid mask" << std::endl;
		}
	}
	else {
		mask = "^(.*)";
	}

	if (vm.count("input")) {
		fs::path temp(vm["input"].as<std::string>());
		search_string_filename = fs::absolute(temp, path).string();
	}

	if (vm.count("output")) {
		fs::path temp(vm["output"].as<std::string>());
		output_filename = fs::absolute(temp, path).string();
	}
	else {
		std::cout << "File with results not specified, default output file: " << path.string() << " result.txt" << std::endl;
		fs::path temp("result.txt");
		output_filename = fs::absolute(temp, path).string();
	}

	if (vm.count("help")) {
		std::cout << desc << "\n";
		return 0;
	}

	search_substring(search_string_filename, path, mask, output_filename);

	return 0;

}