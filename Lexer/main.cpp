#include <iostream>
#include "LexicalAnalyser.h"
using namespace std;

int main() {
    LexicalAnalyser analyzer;
    analyzer.analyze("in.txt","out.html");
    return 0;
}