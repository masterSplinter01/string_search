#include <iostream>
#include "search_algorithm.h"

static const  size_t p = 53; //prime const number
static const ull r = ULLONG_MAX;



void rabin_karp_search(std::ifstream &substring, std::ifstream &string_fstream1, std::ifstream &string_fstream2,  std::ofstream &output, const std::string& filename) {
    //file with substring we search, file with current string where we search, output file stram, where we will write
    //position of found substrings in string
    char prev_c, next_c;

    substring.seekg(0, std::ios::end);
    auto substring_length = (ull)substring.tellg();
    substring.seekg(0, std::ios::beg);


    //vector of pows of prime number p
    std::vector<ull> pows_p = {1};
    for (size_t i = 1; i <= substring_length; ++i){
        pows_p.push_back(pows_p.back() * p);
    }

    //calculating hash of substring
    auto substring_hash = init_hash(substring, substring_length, pows_p);
    auto current_string_chunk_hash = init_hash(string_fstream1, substring_length, pows_p);


    string_fstream1.seekg(0, std::ios::end);
    auto string_length = (ull)string_fstream1.tellg();
    string_fstream1.seekg(0, std::ios_base::beg);
    string_fstream2.seekg(substring_length, std::ios_base::beg);


    //calculating hashes of string chunks with length = substring's length. if hash of substring == hash of chunks, we check that this substrings are the same



    for (size_t i = 0; i < string_length - substring_length + 1; ++i){
        if (substring_hash == current_string_chunk_hash){
            if (check_strings(substring, string_fstream1, i, i+substring_length)){
                output<<filename<<std::endl;
                return;
            }
        }
        else{
            string_fstream2.get(next_c);
            string_fstream1.get(prev_c);
            current_string_chunk_hash = step_hash(prev_c, next_c, substring_length, current_string_chunk_hash, pows_p);
        }
    }
}


bool check_strings(std::ifstream &substring, std::ifstream &string_chunk, ull i1, ull i2) {
    //because of collisions we need to check the strings with the same hashes char by char
    substring.seekg(0);
    string_chunk.seekg(i1);
    for (size_t i = 0; i < i2 - i1; ++i){
        if (substring.get() != string_chunk.get()){
            return false;
        }
    }
    return true;
}

ull init_hash(std::ifstream &input, const ull &length, const std::vector<ull> &pows) {
    char c;
    ull hash = 0;
    for (size_t i = 0; i < length; ++i){
        input.get(c);
        hash += pows[i]* (ull)c;
    }
    return  hash;
}

ull step_hash(char prev_c, char next_c, const ull &length, const ull &prev_hash, const std::vector<ull> &pows) {
    return (ull)prev_hash * (ull)p  - (ull)prev_c * pows[length] + (ull)next_c;

}






