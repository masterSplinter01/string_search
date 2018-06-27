#pragma once
#include <fstream>
#include <vector>
#include <climits>
#include <cmath>
#include <cassert>


typedef unsigned long long int ull;
//typedef long long int ll;


ull init_hash(std::ifstream &input, const ull& length, const std::vector<ull> &pows);
ull step_hash(char prev_c, char next_c, const ull& length, const ull &prev_hash, const std::vector<ull> &pows);

void rabin_karp_search( std::ifstream& substring, std::ifstream& string_fstream1, std::ifstream& string_fstream2,  std::ofstream& output, const std::string& filename);

bool check_strings(std::ifstream &substring, std::ifstream &string_chunk, ull i1, ull i2);
