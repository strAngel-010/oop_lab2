#include "sentence.h"

namespace Prog2 {
	Sentence::Sentence(const Word& word){
		try {
			Word* words = new Word[1];
			words[0] = word;
			arr = words;
			len = 1;
		}
		catch (...) { throw; }
	}

	Sentence::Sentence(char* arr[], unsigned int len) {
		unsigned int errors = 0;
		unsigned int last_ind = 0;
		Word* words = new Word[len];
		for (int i = 0; i < (int)len; ++i) {
			try {
				words[last_ind] = Word(arr[i]);
				++last_ind;
			} catch (const std::exception& e) {
				errors += 1;
				std::cerr << e.what() << std::endl;
				continue;
			}
		}
		if (errors) {
			try { words = (Word*)word_realloc(words, len - errors, len - errors); }
			catch (...) { throw; }
		}
		this->arr = words;
		this->len = len - errors;
	}

	Sentence::Sentence(const Sentence& ob) : arr(nullptr), len(ob.len) {
		if (len) {
			arr = new Word[ob.len];
			std::copy(ob.arr, ob.arr + ob.len, arr);
		}
	}

	Sentence::Sentence(Sentence&& ob) noexcept : arr(ob.arr), len(ob.len) {
		ob.len = 0;
		ob.arr = nullptr;
	}

	Sentence::~Sentence() {
		if (arr) {
			delete[] arr;
		}
		arr = nullptr;
		len = 0;
	}

	Sentence &Sentence::setArr(const Word* arr) noexcept {
        if (this->arr) { delete[] this->arr; }
		this->arr = (Word*)arr;
		return *this;
    }

	Sentence &Sentence::setLen(unsigned int len) noexcept{
        this->len = len;
		return *this;
    }

	int Sentence::findWord(const char* word) {
		try {
			Word w(word);
			for (int i = 0; i < (int)len; i++){
				if (w == arr[i])
					return i;
			}
		}
		catch (...) { throw; }
		return -1;
	}

	char** Sentence::toCharArray(){
		try {
			char** res = new char*[len];
			for (int i = 0; i < (int)len; i++)
				res[i] = (char*)arr[i].getWord();
			return res;
		} catch (...) { throw; }
	}

	Sentence* Sentence::createSubset(char c) {
		Sentence* subset;
		try { subset = new Sentence(); }
		catch (...) { throw; }
		const char* cur_word = nullptr;
		for (int i = 0; i < (int)len; ++i) {
			cur_word = arr[i].getWord();
			if ((cur_word[0] == c) || (std::tolower(cur_word[0]) == c)) {
				try { *subset += arr[i]; }
				catch (...) {
					delete subset;
					throw;
				}
			}
		}
		return subset;
	}

	Sentence& Sentence::sort() noexcept {
		qsort(arr, len, sizeof(Word), comp);
		return *this;
	}

	Sentence& Sentence::print(std::ostream& out) {
		out << "Sentence: " << std::endl;
		for (int i = 0; i < (int)len; i++) {
			arr[i].print(out);
			out << std::endl;
		}
		out << "Total: " << len << " words" << std::endl;
		return *this;
	}

	Sentence& Sentence::operator = (Sentence& ob) {
		for (int i = 0; i < (int)len; ++i)
			delete &arr[i];
		if (arr)
			delete[] arr;
		arr = nullptr;
		if ((len = ob.len) != 0) {
			arr = new Word[len];
			std::copy(ob.arr, ob.arr + ob.len, arr);
		}
		return *this;
	}

	Sentence& Sentence::operator = (Sentence&& ob) noexcept {
        std::swap(len, ob.len);
        std::swap(arr, ob.arr);
        return *this;
    }

	Sentence& Sentence::operator += (const Sentence& ob) {
		if (ob.len) {
			try {
				arr = (Word*)word_realloc(arr, len, len + ob.len);
				std::copy(ob.arr, ob.arr + ob.len, arr + len);
				len += ob.len;
				ob.~Sentence();
			}
			catch (...) { throw; }
		}
		return *this;
	}

	Word& Sentence::operator [] (int index){
		if (index >= len)
			throw std::runtime_error("Index out of range");
		return arr[index];
	}

	std::istream& operator>> (std::istream& in, Sentence& sentence) {
		sentence.~Sentence();
		std::string str = "";
		unsigned int size = 0;
		while (true) {
			in >> str;
			if (in.eof()) { return in; }
			if (in.bad())
				throw std::runtime_error("Input broken");
			if (in.good()) {
				if (str == "N") { break; }
				if (sentence.len == size) {
					size += REALLOC_SIZE;
					try { sentence.arr = (Word*)word_realloc(sentence.arr, sentence.len, size);  }
					catch (...) { throw; }
				}
				try { 
					Word* w = new Word(str.c_str());
					sentence.arr[sentence.len] = std::move(*w);
					++sentence.len;
					delete w;
				}
				catch (...) { throw; }
			}
			in.clear();
        	in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		if (size) {
			try { sentence.arr = (Word*)word_realloc(sentence.arr, sentence.len, sentence.len); }
			catch (...) { throw; }
		}
		return in;
	}

	std::ostream& operator<< (std::ostream& out, const Sentence& sentence) {
		out << "Sentence: ";
		for (int i = 0; i < (int)sentence.len; i++) { out << sentence.arr[i] << " "; }
		out << std::endl;
		return out;
	}
}