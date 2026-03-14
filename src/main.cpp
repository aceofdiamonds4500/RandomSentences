#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "Rules.h"

std::vector<std::string> parse_words(const std::string& filename);

//initialize words as vectors
std::vector<std::string> articles = {"a","an","the"};
int articlesSize = static_cast<int>(articles.size());

std::vector<std::string> adverbs = parse_words("../words/adverbs.txt");
int adverbsSize = static_cast<int>(adverbs.size());

std::vector<std::string> v_nouns = parse_words("../words/vowel_nouns.txt");
int vnounsSize = static_cast<int>(v_nouns.size());

std::vector<std::string> c_nouns = parse_words("../words/consonant_nouns.txt");
int cnounsSize = static_cast<int>(c_nouns.size());

std::vector<std::string> verbs = parse_words("../words/verbs.txt");
int verbsSize = static_cast<int>(verbs.size());

int randomNumber(const int min, const int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    int min_val = min;
    int max_val = max;
    std::uniform_int_distribution<> distrib(min_val, max_val);

    int random_num = distrib(gen);
    return random_num;
}

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

Noun createNoun(int choice) {
    Noun noun;
    if (choice == 1 || choice == 3) {
        noun = {c_nouns[randomNumber(0, cnounsSize-1)],std::nullopt};
    }
    else if (choice == 2) {
        noun = {std::nullopt, v_nouns[randomNumber(0, vnounsSize-1)]};
    }
    else {
        std::cerr << "Invalid choice: " << choice << std::endl;
    }
    return noun;
}

Subject createSubject() {
    std::string articlePick = articles[randomNumber(0, articlesSize-1)];

    Noun noun;

    if (articlePick == "a") {
        noun = createNoun(1);
    }
    else if (articlePick == "an") {
        noun = createNoun(2);
    }
    else if (articlePick == "the") {
        noun = createNoun(3);
    }

    Subject subject = {articlePick, noun};

    return subject;
}

std::string subject_ToString(const Subject& subject) {
    std::string full_subject = "";
    if (subject.article) full_subject += subject.article.value() + " ";

    if (subject.noun.consonantnoun) full_subject += subject.noun.consonantnoun.value();

    if (subject.noun.vowelnoun) full_subject += subject.noun.vowelnoun.value();

    return full_subject;
}

void simpsentence_ToString(const Sentence& sentence) {
    const Subject subject = createSubject();
    std::cout << subject_ToString(subject) << std::endl;

}

int main() {
    int input = 1;
    printf("Run a random sentence?\n> ");

    do {
        std::cin >> input;

        if (input == 1) {
            //add sentence constructor here
            Sentence sentence;
            simpsentence_ToString(sentence);
        }
    } while (input != 0);


    return 0;
}

/*
 * test code for if somethings not working
    Subject subject = {std::nullopt,nouns[8]};
    VerbPhrase verb = {adverbs[6], verbs[4]};

    Sentence s = {subject, verb};

    if (s.subject.article)
        std::cout << *s.subject.article << " ";
    std::cout << s.subject.noun << " ";

    if (s.verb.adverb)
        std::cout << *s.verb.adverb << " ";
    std::cout << s.verb.verb.verb;

    std::cout << "\n";
 */