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

struct IndepClause {
    SimpleSentence simp_sentence;
};

struct ComplexSentenceDI {
    DepClause depClause;
    char comma = ',';
    IndepClause inClause;
};

//this only works because subordinating conjunctions are the goat
struct ComplexSentenceID {
    IndepClause inClause;
    DepClause depClause;
};

struct Sentence {

};