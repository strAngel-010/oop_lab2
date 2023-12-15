#include "sentence/sentence.h"

using namespace Prog2;

int main(){
    std::cout << "Testing constructors:" << std::endl;
    Sentence sentence;
    Word word;
    std::cout << "Sentence created with default constructor:" << std::endl;
    std::cout << sentence << std::endl;
    std::string ans;
    while (true){
        std::cout << "Enter words or N to finish input:" << std::endl;
        try { 
            std::cin >> sentence; 
            if (std::cin.eof()){ return 0; }
        }
        catch (...){ throw; }
        std::cout << sentence << std::endl;

        try { 
            if (sentence.getLen()){
                Sentence s1(sentence[0]); 
                std::cout << "Sentence created with one word:" << std::endl;
                std::cout << s1 << std::endl;
            }

            char** arr = sentence.toCharArray();
            Sentence s2(arr, sentence.getLen());
            std::cout << "Sentence created with char* array:" << std::endl;
            std::cout << s2 << std::endl;
            delete[] arr;
        }
        catch (...){ throw; }

        std::cout << "Move to next module? y/n" << std::endl;
        std::cin >> ans;
        if (std::cin.eof()) { return 0; }
        if (std::cin.bad()){ throw std::runtime_error("Input broken"); }
        if (std::cin.good() && (ans == "y" || ans == "Y")){ break; }
    }
    std::cout << "-------" << std::endl;

    std::cout << "Testing += operator" << std::endl;
    while (true){
        Sentence s1, s2;
        Word w;
        std::cout << "Enter first sentence (N to finish):" << std::endl;
        try { 
            std::cin >> s1;
            if (std::cin.eof()){ return 0; }
        }
        catch (...){ throw; }

        std::cout << "Enter second sentence (N to finish):" << std::endl;
        try { 
            std::cin >> s2;
            if (std::cin.eof()){ return 0; }
        }
        catch (...){ throw; }

        s1 += s2;
        std::cout << "Merged sentences:" << std::endl;
        std::cout << s1 << std::endl;

        std::cout << "Enter word:" << std::endl;
        try { 
            std::cin >> w;
            if (std::cin.eof()){ return 0; }
        }
        catch (...){ throw; }

        s1 += w;
        std::cout << "Sentence and word merge:" << std::endl;
        std::cout << s1 << std::endl;
        
        std::cout << "Move to next module? y/n" << std::endl;
        std::cin >> ans;
        if (std::cin.eof()) { return 0; }
        if (std::cin.bad()){ throw std::runtime_error("Input broken"); }
        if (std::cin.good() && (ans == "y" || ans == "Y")){ break; }
    }
    std::cout << "-------" << std::endl;

    std::cout << "Testing functions:" << std::endl;
    while (true){
        Sentence s;
        std::cout << "Enter sentence (N to finish):" << std::endl;
        try { 
            std::cin >> s;
            if (std::cin.eof()){ return 0; }
        }
        catch (...){ throw; }

        std::cout << "Enter word to search:" << std::endl;
        std::cin >> ans;
        if (std::cin.eof()) { return 0; }
        if (std::cin.bad()){ throw std::runtime_error("Input broken"); }
        if (std::cin.good()){ 
            int find_res = s.findWord(ans.c_str());
            std::cout << "Search result: " << find_res << std::endl;
        }

        char c;
        std::cout << "Enter char to create subset:" << std::endl;
        std::cin >> c;
        if (std::cin.eof()) { return 0; }
        if (std::cin.bad()){ throw std::runtime_error("Input broken"); }
        if (std::cin.good()){ 
            Sentence* subset = s.createSubset(c);
            std::cout << "Subset:" << std::endl;
            std::cout << *subset << std::endl;
            delete subset;
        }

        std::cout << "Sorted sentence:" << std::endl;
        std::cout << s.sort() << std::endl;

        std::cout << "Finish? y/n" << std::endl;
        std::cin >> ans;
        if (std::cin.eof()) { return 0; }
        if (std::cin.bad()){ throw std::runtime_error("Input broken"); }
        if (std::cin.good() && (ans == "y" || ans == "Y")){ break; }
    }
}