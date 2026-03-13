#pragma once
#include <string>
#include <optional>

/*
 * non-terminal
 */
struct Subject {
    std::optional<std::string> article;
    std::string noun;
};

/*
 * non-terminal
 */
struct Verb {
    std::optional<std::string> adverb;
    std::string verb;
};

/*
 * non-terminal
 */
struct Sentence {
    Subject subject;
    Verb verb;
};