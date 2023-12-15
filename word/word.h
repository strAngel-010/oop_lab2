#ifndef OOPPROG2_WORD_H
#define OOPPROG2_WORD_H

#include <string>
#include <cstring>
#include <limits>
#include <sstream>

namespace Prog2 {
    class Word {
    private:
        char* word;
        unsigned int len;
    public:
        /*!
        Creates Word without parameters
        */
        explicit Word() {
            word = nullptr;
            len = 0;
        };

        /*!
        Creates Word from null-terminated string
        @param data Null-terminated string (const char*)
        @throws std::invalid_argument If string contains space symbol
        @throws std::terminate if execution of a function invoked as part of the algorithm throws an exception
        @throws std::bad_alloc if the algorithm fails to allocate memory
        */
        explicit Word(const char* data);

        /*!
        Creates Word from char array (not null-terminated)
        @param arr Not null-terminated char array
        @param len Length of array
        @throws std::invalid_argument if string contains space symbol
        @throws std::runtime_error if fails to realloc char array
        */
        explicit Word(char arr[], unsigned int len);

        /*!
        Copy constructor for Word
        @param word Reference to another word (const Word&)
        */
        explicit Word(const Word& word);

        /*!
        Move constructor for Word
        @param ob Another word (rvalue reference Word&&)
        */
        explicit Word(Word&& ob) noexcept;

        /*!
        Destructor for Word
        */
        ~Word();

        /*!
        Setter for word
        @param word Null-terminated string (const char*)
        @returns Reference to Word
        @throws std::invalid_argument if string contains space symbol
        @throws std::runtime_error if fails to realloc char array
        */
        Word &setWord(const char* word);

        /*!
        Setter for length
        @param len Length of array
        @returns Reference to Word
        */
        Word &setLen(unsigned int len) noexcept;

        /*!
        Getter for word
        @returns Null-terminated string (const char*)
        */
        const char* getWord() const { return word; }

        /*!
        Getter for length
        @returns Length of array
        */
        unsigned int getLen() const { return len; }

        /*!
        Checks if a null-terminated string is a substring of the Word
        @param substr Null-terminated string (const char*)
        @returns Bool value (checks if substr is a substring of the Word)
        */
        bool substr(const char* substr);

        /*!
        Moves Word to lowercase
        @returns Reference to Word
        */
        Word &toLower() noexcept;

        /*!
        Prints full information of the Word
        @param out Reference to output stream (std::ostream&)
        @returns Reference to Word
        */
        Word &print(std::ostream& out) noexcept;

        /*!
        Compares 2 Words
        @param lhs Reference to Word (const Word&)
        @returns Bool (checks if Words are equal)
        */
        bool operator == (const Word &lhs) const {
            return (std::strcmp(word, lhs.getWord()) == 0);
        }

        /*!
        Compares 2 Words
        @param lhs Reference to Word (const Word&)
        @returns Bool (checks if first Word is less than the second)
        */
        bool operator < (const Word &lhs) const {
            return (std::strcmp(word, lhs.getWord()) < 0);
        }

        /*!
        Compares 2 Words
        @param lhs Reference to Word (const Word&)
        @returns Bool (checks if first Word is less or equal to the second)
        */
        bool operator <= (const Word& lhs) const {
            return (std::strcmp(word, lhs.getWord()) <= 0);
        }

        /*!
        Compares 2 Words
        @param lhs Reference to Word (const Word&)
        @returns Bool (checks if first Word is greater or equal to the second)
        */
        bool operator >= (const Word& lhs) const {
            return (std::strcmp(word, lhs.getWord()) >= 0);
        }

        /*!
        Compares 2 Words
        @param lhs Reference to Word (const Word&)
        @returns Bool (checks if first Word is greater than the second)
        */
        bool operator > (const Word& lhs) const {
            return (std::strcmp(word, lhs.getWord()) > 0);
        }

        /*!
        Compares 2 Words
        @param lhs Reference to Word (const Word&)
        @returns Bool (checks if Words are not equal)
        */
        bool operator != (const Word& lhs) const {
            return (std::strcmp(word, lhs.getWord()) != 0);
        }

        /*!
        Copy operator for Word
        @param lhs Reference to another Word (const Word&)
        @returns Reference to changed Word (Word&)
        */
        Word& operator = (const Word& ob);

        /*!
        Move operator for Word
        @param ob Another word (rvalue reference Word&&)
        @returns Reference to changed Word (Word&)
        */
        Word& operator = (Word&& ob) noexcept;

        /*!
        Output operator for Word
        @param out Reference to output stream (std::ostream&)
        @param word Reference to Word
        @returns Reference to output stream (std::ostream&)
        */
        friend std::ostream& operator<< (std::ostream& out, const Word& word);

        /*!
        Input operator for Word
        @param in Reference to input stream (std::istream&)
        @param word Reference to Word
        @returns Reference to input stream (std::istream&)
        */
        friend std::istream& operator>> (std::istream& in, Word& word);
    };

    /*!
    Checks if string doesn't contain spaces.
    @param arr Not null-terminated char array
    @param len Length of array
    @returns Bool (checks if arr doesn't contain space symbol)
    */
    bool checkWord(const char* arr, unsigned int len) noexcept;

    /*!
    Realloc for char arrays
    @param arr Char array (const char*)
    @param prev_size Previous length of array
    @param size New length of array
    @throws std::bad_alloc on failure to allocate memory or if the function does not return on allocation failure
    @throws std::bad_alloc on failure to allocate memory
    @throws std::terminate if execution of a function invoked as part of the algorithm throws an exception
    @returns Char array (const char*) with new length
    */
    const char* str_realloc(const char* arr, int prev_size, int size);

    /*!
    Realloc for Word arrays
    @param arr Word array (const Word*)
    @param prev_size Previous length of array
    @param size New length of array
    @throws std::bad_alloc on failure to allocate memory
    @throws std::terminate if execution of a function invoked as part of the algorithm throws an exception
    @returns Word array (const Word*) with new length
    */
    const Word* word_realloc(const Word* arr, int prev_size, int size);

    /*!
    Comparator for Words
    @param w1 1st Word
    @param w2 2st Word
    @returns int (-1, 0, 1) as a result of comparison between 2 Words
    */
    int comp(const void* w1, const void* w2);
}

#endif