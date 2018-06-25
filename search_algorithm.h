#pragma once
#include <fstream>
#include <vector>
#include <climits>

typedef unsigned long long int ull;
typedef long long int ll;

ull hash(std::ifstream& string, const ull &i1, const ull &i2, const ull &prev_hash,  const std::vector<ull> &pows);
void rabin_karp_search(std::ifstream& substring, std::ifstream& string, std::ofstream& output);
bool check_strings(std::ifstream &substring, std::ifstream &string_chunk, ull i1, ull i2);
