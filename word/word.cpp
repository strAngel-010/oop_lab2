#include "word.h"
#include <iostream>

namespace Prog2 {
    Word::Word(const char* word){
        int len = 0;
        try { len = std::strlen(word); }
        catch(...) { throw; }
        
        if (!checkWord(word, len))
            throw std::invalid_argument("Space symbol found");
        try { 
            this->word = new char[len+1];
            std::copy(word, word+len+1, this->word);
        }
        catch (...) { throw; }
        this->len = len;
    }

    Word::Word(char arr[], unsigned int len){
        try {
            if (!checkWord(arr, len))
                throw std::invalid_argument("Error: Space symbol found");
            
            arr = (char*)str_realloc(arr, len, len+1);
            if (!arr)
                throw std::runtime_error("Realloc error");
            arr[len] = '\0';
        } catch(...) { throw; }
            
        word = arr;
        this->len = len;
    }

    Word::Word(const Word& ob) : word(nullptr), len(ob.len) {
        if (len) {
            word = new char[ob.len + 1];
            std::copy(ob.word, ob.word + ob.len + 1, word);
        }
    }

    Word::Word(Word&& ob) noexcept : word(ob.word), len(ob.len) {
        ob.len = 0;
        ob.word = nullptr;
    }

    Word::~Word(){
        if (word) { delete[] word; }
        word = nullptr;
        len = 0;
    }

    Word &Word::setWord(const char* word){
        int len = 0;
        try { len = std::strlen(word); }
        catch(...) { throw; }

        if (!checkWord(word, len))
            throw std::invalid_argument("Space symbol found");
        try {
            if (this->word) { delete[] this->word; }
            this->word = new char[len + 1];
            std::copy(word, word + len + 1, this->word);
        }
        catch (...) { throw; }
        return *this;
    }

    Word &Word::setLen(unsigned int len) noexcept{ 
        this->len = len; 
        return *this;
    }

    bool Word::substr(const char* substr){
        return ((std::string)word).find(substr) != std::string::npos;
    }

    Word &Word::toLower() noexcept {
        for (int i = 0; i < (int)len; i++)
            word[i] = std::tolower(word[i]);
        return *this;
    }

    Word& Word::print(std::ostream& out) noexcept {
        out << "Word: " << word << "; Length: " << len;
        return *this;
    }

    bool checkWord(const char* arr, unsigned int len) noexcept{
        for (int i = 0; i < (int)len; i++){
            if (arr[i] == ' ')
                return false;
        }
        return true;
    }

    const char* str_realloc(const char* arr, int prev_size, int size) {
        try {
            char* tmp = new char[size];
            std::copy(arr, arr + prev_size, tmp);
            delete[] arr;
            arr = tmp;
            return arr;
        }
        catch (...){
            throw;
        }
    }

    const Word* word_realloc(const Word* arr, int prev_size, int size) {
        try {
            Word* tmp = new Word[size];
            std::copy(arr, arr + prev_size, tmp);
            delete[] arr;
            arr = tmp;
            return arr;
        }
        catch (...) { throw; }
    }

    Word& Word::operator = (const Word& ob) {
        if (this != &ob) {
            delete[] word;
            word = nullptr;
            if ((len = ob.len) != 0) {
                word = new char[len+1];
                std::copy(ob.word, ob.word + ob.len + 1, word);
            }
        }
        return *this;
    }

    Word& Word::operator = (Word&& ob) noexcept {
        std::swap(len, ob.len);
        std::swap(word, ob.word);
        return *this;
    }

    std::ostream& operator<< (std::ostream& out, const Word& word) {
        out << word.word;
        return out;
    }

    std::istream& operator>> (std::istream& in, Word& word) {
        std::string str;
        in >> str;
        if (in.eof()) { return in; }
        if (in.bad())
            throw std::runtime_error("Input broken");
        if (in.good()) {
            const char* c_str = str.c_str();
            try {
                word.setWord(c_str);
                word.setLen(std::strlen(c_str));
            }
            catch (...) { throw; }
        }
        in.clear();
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return in;
    }

    int comp(const void* w1, const void* w2){
        if (*(Word*)w1 < *(Word*)w2){ return -1; }
        if (*(Word*)w1 > *(Word*)w2){ return 1; }
        return 0;
    }
}