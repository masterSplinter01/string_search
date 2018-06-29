

#include "search_algorithm.h"

const size_t p = 53;

//prime const number

substring::substring(const std::string& filename): _filename(filename), _p_pow(1) {
    size_t p = 53;
    std::ifstream temp;
    temp.exceptions(std::ifstream::failbit);
    try{
        temp.open(filename);
        temp.seekg(0, std::ios::end);
        _length = temp.tellg();
        temp.seekg(0, std::ios::beg);
    }
    catch (std::fstream::failure& e){
        std::cerr<<"Opening output file error"<<std::endl;
        std::exit(1);
    }
    _hash =  init_hash(temp, _length);
    for (size_t i = 0; i < _length; ++i){
        _p_pow  *= p;
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


void rabin_karp_search(substring& substr, const std::string &current_search_file, std::ofstream &output)  {
    std::cout<<"thread for "<< current_search_file<< " begin! \n";

    std::ifstream substr_file;
    std::ifstream string_fstream1;
    std::ifstream string_fstream2;

    string_fstream1.exceptions(std::ifstream::failbit);

    try {
        string_fstream1.open(current_search_file);
        string_fstream2.open(current_search_file);
        substr_file.open(substr.get_filename());

    }
    catch (std::ios::failure& e) {
        std::cout << "Permission denied: " << current_search_file<< std::endl;
        std::cout<<"thread for "<<current_search_file<<" finished!\n";
        return;
    }

    char prev_c, next_c;

    string_fstream1.seekg(0, std::ios::end);
    auto string_length = (ull)string_fstream1.tellg();
    string_fstream1.seekg(0, std::ios::beg);

    if (substr.get_length() > string_length){
        std::cout<<"thread for "<<current_search_file<<" finished!\n";
        return;
    }

    auto current_string_chunk_hash = init_hash(string_fstream2, substr.get_length());



    //calculating hashes of string chunks with length = substring's length. if hash of substring == hash of chunks, we check that this substrings are the same


    while(string_fstream2){
        if (substr.get_hash() == current_string_chunk_hash && check_strings(substr_file, string_fstream1)){
            std::unique_lock<std::mutex> lock(mtx);
            output<<current_search_file<<std::endl;
            std::cout<<"thread for "<<current_search_file<<" finished!\n";
            return;
        }

        string_fstream1.get(prev_c);
        string_fstream2.get(next_c);

        current_string_chunk_hash = step_hash(prev_c, next_c, current_string_chunk_hash, substr.get_p_pow());

    }

}

bool check_strings(std::ifstream &substring, std::ifstream &string_chunk) {
    //because of collisions we need to check the strings with the same hashes char by char
    substring.seekg(0);
    char c1, c2;
    while(substring.get(c1) && string_chunk.get(c2)){
        if (c1 != c2){
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

ull step_hash(char prev_c, char next_c, const ull &prev_hash, const ull p_pow) {
    return prev_hash * (ull)p  - (ull)prev_c * p_pow + (ull)next_c;

}


















