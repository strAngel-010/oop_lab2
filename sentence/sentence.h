#ifndef OOPPROG2_SENTENCE_H
#define OOPPROG2_SENTENCE_H
enum NUMS {
	REALLOC_SIZE = 5
};

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <sstream>
#include "../word/word.h"

namespace Prog2 {
	class Sentence {
	private: 
		Word* arr;
		unsigned int len;
	public:
		/*!
		Default constructor for sentence
		@param arr Word array (Word*)
        @param len Length of array
        */
		explicit Sentence(Word* arr = nullptr, unsigned int len = 0) : arr(arr), len(len) {};

		/*!
		Creates Sentence containing 1 Word
		@param word Reference to Word (Word&)
		@throws std::bad_alloc on failure to allocate memory
        */
		Sentence(const Word& word);

		/*!
		Creates Sentence from array of null-terminated strings
		@param arr Array of null-terminated strings (char*[])
		@param len Length of array
		@throws std::bad_alloc on failure to allocate memory
    	@throws std::terminate if execution of a function invoked as part of the algorithm throws an exception
        */
		explicit Sentence(char* arr[], unsigned int len);

		/*!
		Copy constructor for Sentence
        @param ob Reference to another Sentence (const Sentence&)
        */
		explicit Sentence(const Sentence& ob);

		/*!
		Move constructor for Sentence
        @param ob Another Sentence (rvalue reference Sentence&&)
        */
		explicit Sentence(Sentence&& ob) noexcept;

		/*!
        Destructor for Word
        */
		~Sentence();

		/*!
		Setter for array
        @param arr Word array (Word*)
        @returns Reference to Sentence (Sentence&)
        */
		Sentence &setArr(const Word* arr) noexcept;

		/*!
		Setter for length
        @param len Length of array
        @returns Reference to Sentence (Sentence&)
        */
        Sentence &setLen(unsigned int len) noexcept;

		/*!
		Getter for length
        @returns Length of array
        */
		unsigned int getLen() const { return len; }

		/*!
		Getter for array
        @returns Word array (Word*)
        */
		Word* getArr() const { return arr; }

		/*!
		Finds given word in array
		@param word Null-terminated string (const char*)
		@throws std::out_of_range if len param is greater than real length of array
		@returns Index of Word
		*/
		int findWord(const char* word);

		/*!
		Creates array of null-terminated strings from Word array
		@throws std::out_of_range if len param is greater than real length of array
		@returns Array of null-terminated strings (char**)
		*/
		char** toCharArray();

		/*!
		Creates subset (new Sentence) containing Words with given first letter
		@param c Char for creating subset
		@throws std::bad_alloc on failure to allocate memory
		@throws std::terminate if execution of a function invoked as part of the algorithm throws an exception
		@returns Pointer to new Sentence (Sentence*)
		*/
		Sentence* createSubset(char c);

		/*!
		Sorts Sentence
		@returns Reference to Sentence (Sentence&)
		*/
		Sentence& sort() noexcept;

		/*!
		Prints full information of the Sentence
        @param out Reference to output stream (std::ostream&)
        @returns Reference to Sentence
        */
		Sentence& print(std::ostream& out);

		/*!
		Copy operator for Sentence
        @param lhs Reference to another Sentence (Sentence&)
        @returns Reference to changed Sentence (Sentence&)
        */
		Sentence& operator = (Sentence& ob);

		/*!
		Move operator for Sentence
        @param ob Another Sentence (rvalue reference Sentence&&)
        @returns Reference to changed Sentence (Sentence&)
        */
		Sentence& operator = (Sentence&& ob) noexcept;

		/*!
		+= operator for Sentence
		@param ob Reference to Sentence (const Sentence&)
		@throws std::bad_alloc on failure to allocate memory
    	@throws std::terminate if execution of a function invoked as part of the algorithm throws an exception
		@returns Reference to Sentence (Sentence&)
		*/
		Sentence& operator += (const Sentence& ob);

		/*!
		Gets Word with given index
		@param index Index of Word
		@throws std::runtime_error if index is out of range
		@returns Reference to Word (Word&)
		*/
		Word& operator [] (int index);

		/*!
		Input operator for Sentence
        @param in Reference to input stream (std::istream&)
        @param sentence Reference to Sentence (Sentence&)
        @returns Reference to input stream (std::istream&)
        */
		friend std::istream& operator>> (std::istream& in, Sentence& sentence);

		/*!
		Output operator for Sentence
        @param out Reference to output stream (std::ostream&)
        @param sentence Reference to Sentence (Sentence&)
        @returns Reference to output stream (std::ostream&)
        */
		friend std::ostream& operator<< (std::ostream& out, const Sentence& sentence);
	};
}

#endif
