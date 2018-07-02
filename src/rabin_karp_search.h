#pragma once
#include <mutex>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>

extern std::mutex fstream_mutex;
extern std::mutex iostream_mutex;

typedef unsigned long long int ull;

class substring {
public:
	substring() = default;
	explicit substring(const std::string& filename);
	const std::string get_filename();
	const ull get_hash();
	const ull get_length();
	const ull get_p_pow();

private:
	std::string _filename;
	ull _hash;
	ull _length;
	ull _p_pow;
};

void rabin_karp_search(substring& substr, const std::string& search_file, std::ofstream& output);
ull init_hash(std::ifstream &input, const ull& length);
ull step_hash(char prev_c, char next_c, const ull &prev_hash, const ull p_pow);
bool check_strings(std::ifstream &substring, std::ifstream &string_chunk);


