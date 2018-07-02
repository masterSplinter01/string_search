#include "rabin_karp_search.h"

const size_t p = 53; //prime const number that we use for calculating hash

substring::substring(const std::string& filename) : _filename(filename), _p_pow(1) {
	std::ifstream temp;
	temp.exceptions(std::ifstream::failbit);
	try {
		temp.open(filename);
		temp.seekg(0, std::ios::end);
		_length = temp.tellg();
		temp.seekg(0, std::ios::beg);
	}
	catch (std::fstream::failure& e) {
		std::cerr << "Opening substring file error: " << filename << std::endl;
		exit(1);
	}

	_hash = init_hash(temp, _length);

	for (size_t i = 0; i < _length; ++i) {
		_p_pow *= p;
	}
}

const std::string substring::get_filename() {
	return _filename;
}

const ull substring::get_hash() {
	return _hash;
}

const ull substring::get_length() {
	return _length;
}

const ull substring::get_p_pow() {
	return _p_pow;
}


void rabin_karp_search(substring& substr, const std::string &search_file, std::ofstream &output) {
	
	std::ifstream substring_file;
	std::ifstream string_fstream1;
	std::ifstream string_fstream2;

	string_fstream1.exceptions(std::ifstream::failbit);

	try {

		string_fstream1.open(search_file);
		string_fstream2.open(search_file);

	}
	catch (std::ios::failure& e) {
		std::unique_lock<std::mutex> lock(iostream_mutex);
		std::cout << "Permission denied: " << search_file << std::endl;
		return;
	}

	try {
		substring_file.open(substr.get_filename());
	}
	catch (std::ios::failure& e) {
		std::unique_lock<std::mutex> lock(iostream_mutex);
		std::cout << "Can't open file with substring: " << substr.get_filename() << std::endl;
		exit(1);
	}

	char prev_c, next_c;

	string_fstream1.seekg(0, std::ios::end);
	auto string_length = (ull)string_fstream1.tellg();
	string_fstream1.seekg(0, std::ios::beg);

	if (substr.get_length() > string_length) {
		return;
	}

	//calculating hash of 1st chunk of string with length = substring_length
	auto string_chunk_hash = init_hash(string_fstream2, substr.get_length());


	/*to get symbols from chunks of string where we search
	we read chars from 2 streams:
	string_fstream1 starts from 0
	string_fstream2 starts from substring_length*/

	while (string_fstream2) {
		if (substr.get_hash() == string_chunk_hash && check_strings(substring_file, string_fstream1)) {
			std::unique_lock<std::mutex> lock(fstream_mutex);
			output << search_file << std::endl;
			return;
		}

		string_fstream1.get(prev_c);
		string_fstream2.get(next_c);

		string_chunk_hash = step_hash(prev_c, next_c, string_chunk_hash, substr.get_p_pow());

	}

}

bool check_strings(std::ifstream &substring, std::ifstream &string_chunk) {
	substring.seekg(0);
	auto pos = string_chunk.tellg();
	char c1, c2;
	while (substring.get(c1) && string_chunk.get(c2)) {
		if (c1 != c2) {
			return false;
		}
	}
	string_chunk.seekg(pos);
	return true;
}

ull init_hash(std::ifstream &input, const ull &length) {
	char c;
	ull hash = 0;
	for (size_t i = 0; i < length; ++i) {
		input.get(c);
		hash = hash * p + c;
	}
	return hash;
}

ull step_hash(char prev_c, char next_c, const ull &prev_hash, const ull p_pow) {
	return prev_hash * (ull)p - (ull)prev_c * p_pow + (ull)next_c;

}