#pragma once
#include <string>
#include <optional>

struct Noun {
    std::optional<std::string> vowelnoun;
    std::optional<std::string> consonantnoun;
};

/*
 * args: [article] and [noun]
 */
struct Subject {
    std::optional<std::string> article;
    Noun noun;
};

/*
 * args: [adverb] and [verb] OR [verb]1
 */
struct VerbPhrase {
    std::optional<std::string> adverb;
    std::string verb;
};

/*
 * args: Subject and VerbPhrase
 */
struct SimpleSentence {
    Subject subject;
    VerbPhrase verb;
};

struct DepClause{
    std::string subord_conjunction;
    SimpleSentence simp_sentence; //lol
};

struct ComplexSentenceDI {
    DepClause depClause;
    std::string connector;
    SimpleSentence inClause;
};

//this only works because subordinating conjunctions are the GOAT
struct ComplexSentenceID {
    SimpleSentence inClause;
    DepClause depClause;
};