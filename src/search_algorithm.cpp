#include <iostream>
#include <boost/thread.hpp>
#include "search_algorithm.h"

static const  size_t p = 53; //prime const number

void rabin_karp_search(std::ifstream &substring,  std::ofstream &output, const std::string& filename) {

    std::ifstream string_fstream1;
    std::ifstream string_fstream2;

    string_fstream1.exceptions(std::ifstream::failbit);

    try {
        string_fstream1.open(filename);
        string_fstream2.open(filename);

    }
    catch (std::ios::failure& e) {
        std::cout << "Permission denied: " << filename<< std::endl;
        return;
    }

    char prev_c, next_c;

    substring.seekg(0, std::ios::end);
    auto substring_length = (ull)substring.tellg();
    substring.seekg(0, std::ios::beg);

    string_fstream1.seekg(0, std::ios::end);
    auto string_length = (ull)string_fstream1.tellg();
    string_fstream1.seekg(0, std::ios::beg);

    if (substring_length > string_length){
        return;
    }


    //calculating hash of substring and hash of first substring_length chars of string
    auto substring_hash = init_hash(substring, substring_length);
    auto current_string_chunk_hash = init_hash(string_fstream1, substring_length);


    string_fstream1.seekg(0, std::ios_base::beg);
    string_fstream2.seekg(substring_length, std::ios_base::beg);


    //calculating hashes of string chunks with length = substring's length. if hash of substring == hash of chunks, we check that this substrings are the same



    for (size_t i = 0; i < string_length - substring_length + 1; ++i){
        if (substring_hash == current_string_chunk_hash){
            if (check_strings(substring, string_fstream1, i, i+substring_length)){
                mtx.lock();
                output<<filename<<std::endl;
                mtx.unlock();
                return;
            }
        }
        else{
            string_fstream2.get(next_c);
            string_fstream1.get(prev_c);
            current_string_chunk_hash = step_hash(prev_c, next_c, substring_length, current_string_chunk_hash);
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

ull init_hash(std::ifstream &input, const ull &length) {
    char c;
    ull hash = 0;
    for (size_t i = 0; i < length; ++i){
        input.get(c);
        hash = hash * p + c;
    }
    return  hash;
}

ull step_hash(char prev_c, char next_c, const ull &length, const ull &prev_hash) {
    return (ull)prev_hash * (ull)p  - (ull)prev_c * (ull)pow(p, length) + (ull)next_c;

}






