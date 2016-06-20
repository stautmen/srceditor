#ifndef SYNTAX_LEXICALANALYZER_H
#define SYNTAX_LEXICALANALYZER_H

#include <string>
#include <list>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

enum Keys { START, COMMENT, PREPROCESSOR_DIRECTIVE, NUMERIC_CONST, STRING_CONST, IDENTIFIER, KEY_WORD, OPERATOR, OPERATOR_TWO, PUNCTUATION, NONE};

class LexicalAnalyser {
public:
    LexicalAnalyser() { rekognized = false; }
    ~LexicalAnalyser() {}

    void analyze(std::string,std::string);
    std::string nextToken(std::string);

private:
    std::list<std::string> keywords;
    std::list<std::string> operatorsONE;
    std::list<std::string> operatorsTWO;
    std::string delimiters;
    std::string inFile,outFile;

    std::string currentToken;
    int type;
    std::string buffer;
    int pos;
    bool rekognized;

    void initKeywords();
    void initDelimiters();
    void initOperators();
    std::string encode(std::string);
};


#endif //SYNTAX_LEXICALANALYZER_H
