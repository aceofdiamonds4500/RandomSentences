#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Rules.h"

std::vector<std::string> parse_words(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;

        return {};
    }

    std::string line;
    std::vector<std::string> words;
    while (getline(file, line)) {
        //std::cout << line << std::endl;
        words.push_back(line);
    }
    return words;
}

int main() {
    //initialize words as vectors
    std::vector<std::string> articles = {"a","an","the"};
    std::vector<std::string> adverbs = parse_words("../words/adverbs.txt");
    std::vector<std::string> nouns = parse_words("../words/nouns.txt");
    std::vector<std::string> verbs = parse_words("../words/verbs.txt");


    Subject subject = {articles[0],nouns[8]};
    VerbPhrase verb = {adverbs[6], verbs[4]};

    Sentence s = {subject, verb};

    if (s.subject.article)
        std::cout << *s.subject.article << " ";
    std::cout << s.subject.noun << " ";

    if (s.verb.adverb)
        std::cout << *s.verb.adverb << " ";
    std::cout << s.verb.verb.verb;

    std::cout << "\n";

    return 0;
}