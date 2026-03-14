#pragma once
#include <string>
#include <optional>

/*
 * args: [article] and [noun]
 */
struct Subject {
    std::optional<std::string> article;
    std::string noun;
};

/*
 * arg: [verb]
 */
struct Verb {
    std::string verb;
};

/*
 * args: [adverb] and Verb OR Verb
 */
struct VerbPhrase {
    std::optional<std::string> adverb;
    Verb verb;
};

/*
 * args: Subject and VerbPhrase
 */
struct Sentence {
    Subject subject;
    VerbPhrase verb;
};

struct DepClause{
    std::string subord_conjunction;
    Sentence sentence;
};

struct IndepClause {
    Sentence sentence;
};

struct ComplexSentence {
    DepClause depClause;
    char comma = ',';
    IndepClause inClause;
};