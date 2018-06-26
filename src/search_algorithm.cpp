#include <iostream>
#include "search_algorithm.h"

static const  size_t p = 53; //prime const number
static const ull r = ULLONG_MAX;


void rabin_karp_search(std::ifstream &substring, std::ifstream &string, std::ofstream &output) {
    //file with substring we search, file with current string where we search, output file stram, where we will write
    //position of found substrings in string

    substring.seekg(0, std::ios::end);
    auto substring_length = (ull)substring.tellg();


    //vector of pows of prime number p

    std::vector<ull> pows_p = {1};
    for (size_t i = 1; i < substring_length; ++i){
        pows_p.push_back(pows_p.back() * p);
    }

    //calculating hash of substring
   ull substring_hash = hash(substring, 0, substring_length, 0, pows_p);


    string.seekg(0, std::ios::end);
    long long int string_length = string.tellg();
    ull prev_hash = 0;

    //calculating hashes of string chunks with length = substring's length
            // if hash of substring == hash of chunks, we check that this substrings are the same

    for (size_t i = 0; i < string_length - substring_length + 1; ++i){
        auto current_string_chunk_hash = hash(string, i, i+ substring_length, prev_hash, pows_p);
        if (substring_hash == current_string_chunk_hash){
            if (check_strings(substring, string, i, i+substring_length)){
                output<<i<<" ";
            }
        }


    }
    output<<"\n";

}

ull hash(std::ifstream &input, const ull &i1, const ull &i2, const ull &prev_hash,  const std::vector<ull> &pows) {
    //polynomial hash function for string
    // arguments: file with string, indexes of begin and end of string's chunk, hash of previous chunk, vector of pows
    // of prime number p
    //hash ( s[i+1, i + m ] ) = hash(s[i, i + m - 1]) - s[i] * p^(m-1) + s[i+m-1] * p

    char c;
    ull hash = 0;
    auto range = i2 - i1;

    if (prev_hash == 0) {
        input.seekg(i1);

        for (size_t i = 0; i < range; ++i) {
            input.get(c);
            hash += (pows[i] * (int)c) % r;
        }
    }
    else{
        char prev_c;
        char next_c;

        input.seekg(i1-1);
        input.get(prev_c);

        input.seekg(i2);
        input.get(next_c);

        hash = ((prev_hash - prev_c * pows[range - 1]) * p + next_c) % r;
    }
    return hash;;
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




