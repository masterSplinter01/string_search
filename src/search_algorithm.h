#pragma once
#include <fstream>
#include <vector>
#include <climits>
#include <cmath>
#include <cassert>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>

extern boost::mutex mtx;



typedef unsigned long long int ull;



ull init_hash(std::ifstream &input, const ull& length);
ull step_hash(char prev_c, char next_c, const ull& length, const ull &prev_hash );

void rabin_karp_search( std::ifstream& substring, std::ofstream& output, const std::string& filename);

bool check_strings(std::ifstream &substring, std::ifstream &string_chunk, ull i1, ull i2);
