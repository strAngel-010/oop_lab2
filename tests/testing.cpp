#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include "../sentence/sentence.h"
#include "../word/word.h"

using namespace Prog2;

TEST_CASE("SentenceConstructor"){
    SECTION("DefaultConstructor"){
        Word w;
        Sentence s;
        REQUIRE(s.getLen() == 0);
    }
}