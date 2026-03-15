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
 * args: [adverb] and [verb] OR [verb]
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

/*
 * args: SubordinatingConjunction and SimpleSentence
 */
struct DepClause{
    std::string subord_conjunction;
    SimpleSentence simp_sentence; //lol
};

/*
 * args: depClause [connector] and SimpleSentence (independent clause)
 */
struct ComplexSentenceDI {
    DepClause depClause;
    std::string connector;
    SimpleSentence inClause;
};

/*
 * args: SimpleSentence (independent clause) and DependentClause
 */
struct ComplexSentenceID {
    SimpleSentence inClause;
    DepClause depClause;
};