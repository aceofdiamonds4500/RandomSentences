#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <cctype>
#include "Rules.h"

std::vector<std::string> parse_words(const std::string& filename);

//initialize words as vectors
std::vector<std::string> articles = {"a","an","the"};
int articlesSize = static_cast<int>(articles.size());

std::vector<std::string> adverbs = parse_words("../words/adverbs.txt");
int adverbsSize = static_cast<int>(adverbs.size());

std::vector<std::string> prop_nouns = parse_words("../words/proper_nouns.txt");
int propnounsSize = static_cast<int>(prop_nouns.size());

std::vector<std::string> v_nouns = parse_words("../words/vowel_nouns.txt");
int vnounsSize = static_cast<int>(v_nouns.size());

std::vector<std::string> c_nouns = parse_words("../words/consonant_nouns.txt");
int cnounsSize = static_cast<int>(c_nouns.size());

std::vector<std::string> verbs = parse_words("../words/verbs.txt");
int verbsSize = static_cast<int>(verbs.size());

std::vector<std::string> subords = parse_words("../words/subord_conjunctions.txt");
int subordsSize = static_cast<int>(subords.size());


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

VerbPhrase createVerbPhrase() {
    std::optional<std::string> adverb;

    int adverbExistance = randomNumber(1,10);
    if (adverbExistance > 2) {
        adverb = std::nullopt;
    }
    else {
        adverb = adverbs.at(randomNumber(0, adverbsSize-1));
    }

    VerbPhrase verb_phrase = {adverb, verbs.at(randomNumber(0, verbsSize-1))};
    return verb_phrase;
}

Noun createNoun(int vc_choice) {
    Noun noun;
    if (vc_choice == 1 || vc_choice == 3) {
        noun = {c_nouns.at(randomNumber(0, cnounsSize-1)),std::nullopt};
    }
    else if (vc_choice == 2) {
        noun = {std::nullopt, v_nouns.at(randomNumber(0, vnounsSize-1))};
    }
    else {
        noun = {prop_nouns.at(randomNumber(0, propnounsSize-1)), std::nullopt};
    }
    return noun;
}

Subject createSubject() {
    std::optional<std::string> article;

    int articleExistance = randomNumber(1,10);
    if (articleExistance > 6) {
        article = std::nullopt;
    }
    else {
        article = articles.at(randomNumber(0, articlesSize-1));
    }

    Noun noun;

    if (article == "a") {
        noun = createNoun(1);
    }
    else if (article == "an") {
        noun = createNoun(2);
    }
    else if (article == "the") {
        int rand = randomNumber(1,2);
        noun = createNoun(rand);
    }
    else {
        noun = createNoun(4);
    }


    Subject subject = {article, noun};

    return subject;
}

SimpleSentence createSimpleSentence() {
    SimpleSentence sentence = {createSubject(), createVerbPhrase()};
    return sentence;
}

DepClause createDepClause() {
    std::string subord_conj = subords.at(randomNumber(0, subordsSize-1));

    SimpleSentence sentence = createSimpleSentence();

    DepClause clause = {subord_conj, createSimpleSentence()};
    return clause;
}

ComplexSentenceDI createComplexSentenceDI() {
    DepClause depClause = createDepClause();
    SimpleSentence indepClause = createSimpleSentence();
    ComplexSentenceDI depind = {depClause,",",indepClause};

    return depind;
}

ComplexSentenceID createComplexSentenceID() {
    DepClause depClause = createDepClause();
    SimpleSentence indepClause = createSimpleSentence();
    ComplexSentenceID inddep = {indepClause,depClause};

    return inddep;
}

std::string subject_ToString(const Subject& subject) {
    std::string full_subject;
    if (subject.article) full_subject += subject.article.value() + " ";

    if (subject.noun.consonantnoun) full_subject += subject.noun.consonantnoun.value();

    if (subject.noun.vowelnoun) full_subject += subject.noun.vowelnoun.value();

    return full_subject;
}

std::string verbPhrase_ToString(const VerbPhrase& verb_phrase) {
    std::string full_verb_phrase;

    if (verb_phrase.adverb) full_verb_phrase += verb_phrase.adverb.value() + " ";

    full_verb_phrase += verb_phrase.verb;

    return full_verb_phrase;
}

std::string simpSentence_ToString(const SimpleSentence& simp_sentence) {
    std::string full_simpsentence = subject_ToString(simp_sentence.subject) + " " + verbPhrase_ToString(simp_sentence.verb);
    return full_simpsentence;
}

std::string depClause_ToString(const DepClause& depClause) {
    std::string full_depC = depClause.subord_conjunction + " " + simpSentence_ToString(depClause.simp_sentence);
    return full_depC;
}

std::string compSentenceDI_ToString(const ComplexSentenceDI& depind) {
    std::string full_complexSentence = depClause_ToString(depind.depClause) + depind.connector + " " + simpSentence_ToString(depind.inClause);
    return full_complexSentence;
}

std::string compSentenceID_ToString(const ComplexSentenceID& inddep) {
    std::string full_complexSentence = simpSentence_ToString(inddep.inClause) + " " + depClause_ToString(inddep.depClause);
    return full_complexSentence;
}

std::string capitalize(const std::string& s) {
    std::string capitalized_str;

    if (s[0] >= 97 && s[0] <= 122) {
        capitalized_str += static_cast<char>(std::toupper(s[0]));
        capitalized_str += s.substr(1);
    }
    else {
        return s;
    }
    return capitalized_str;
}

std::string generateSentence() {
    std::string sentence;

    int rand = randomNumber(1,100);
    if (rand < 33) {
        SimpleSentence simp_sentence = createSimpleSentence();
        sentence = simpSentence_ToString(simp_sentence);
    }
    else if (rand > 66) {
        ComplexSentenceDI complexDI = createComplexSentenceDI();
        sentence = compSentenceDI_ToString(complexDI);
    }
    else {
        ComplexSentenceID complexID = createComplexSentenceID();
        sentence = compSentenceID_ToString(complexID);
    }
    return sentence;
}

int main() {
    int input = 1;

    printf("Generate a random sentence? (1 to generate, 0 for quit)\n> ");

    do {
        std::cin >> input;

        if (std::cin.fail()) {
            std::cout << "Try again. (1 to generate, 0 for quit)" << std::endl;
            return 1;
        }

        if (input == 1) {
            std::cout << "\"" << capitalize(generateSentence()) << ".\"" << std::endl;
        }
        else if (input == 0) {
            std::cout << "Goodbye." << std::endl;
            return 0;
        }
        else {
            std::cout << "Try again. (1 to generate, 0 for quit)";
        }
    } while (input != 0);


    return 0;
}