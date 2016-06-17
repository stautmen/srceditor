#include "LexicalAnalyser.h"

std::vector<std::string> split(std::string str, char delimiter) {
    std::vector<std::string> internal;
    std::stringstream ss(str);
    std::string tok;

    while(getline(ss, tok, delimiter)) {
        internal.push_back(tok);
    }

    return internal;
}

void LexicalAnalyser::analyze(std::string in,std::string out) {
    initKeywords();
    initDelimiters();
    initOperators();

    auto color = [](int type) {
            if (type == START) return "black";
            if (type == COMMENT) return "green";
            if (type == PREPROCESSOR_DIRECTIVE) return "blue";
            if (type == NUMERIC_CONST) return "RosyBrown";
            if (type == STRING_CONST) return "Chocolate";
            if (type == IDENTIFIER) return "DarkOrchid";
            if (type == KEY_WORD) return "Red";
            if (type == OPERATOR) return "Brown";
            if (type == OPERATOR_TWO) return "Brown";
            if (type == PUNCTUATION) return "AntiqueWhite3";
            if (type == NONE) return "Ngrey21";
            return "white";
    };

    auto title = [](int type) {
        if (type == START) return "START";
        if (type == COMMENT) return "COMMENT";
        if (type == PREPROCESSOR_DIRECTIVE) return "PREPROCESSOR_DIRECTIVE";
        if (type == NUMERIC_CONST) return "NUMERIC_CONST";
        if (type == STRING_CONST) return "STRING_CONST";
        if (type == IDENTIFIER) return "IDENTIFIER";
        if (type == KEY_WORD) return "KEY_WORD";
        if (type == OPERATOR) return "OPERATOR";
        if (type == OPERATOR_TWO) return "OPERATOR_TWO";
        if (type == PUNCTUATION) return "PUNCTUATION";
        if (type == NONE) return "NONE";
        return "";
    };

    std::ifstream file("/Users/sproskurnya/ClionProjects/Lexer/in2.txt");

    std::string line;

    std::vector<std::string> tokens;

    while(std::getline(file, line)) {

        std::istringstream iss(line);
        std::string token;
        while(std::getline(iss, token, '\t'))
            tokens.push_back(token);
    }

    auto endStr = [](bool hasBr){
        return hasBr ? std::string("<br>") : std::string("");
    };

    std::ofstream myfile;
    myfile.open("/Users/sproskurnya/ClionProjects/Lexer/out.html");
    myfile << "</pre>";

    pos = 0;

    if (myfile.is_open())
    {
        currentToken = "";
        for (auto string : tokens)
        {
            if(string[0] == ' ' && string[1] == ' ')
                myfile << "&nbsp;&nbsp;&nbsp;&nbsp;";

            std::vector<std::string> words = split(string,' ');

            for(auto word : words) {
                nextToken(word);
                myfile << " ";
                type = string.find("//") != std::string::npos ? COMMENT : type;
                myfile << "<span style=\"color:" << color(type) << "\" title=\" " << title(type) << "\">" <<
                currentToken.c_str() << " </span>";
            }
            myfile << "<br>";
            myfile.flush();
        }
        myfile << "</pre>";
        myfile.flush();
    }
    file.close();
    myfile.close();
    std::cout<<outFile.c_str();
}

void LexicalAnalyser::nextToken(std::string word) {
    pos++;
        type = START;
    for(auto string : keywords) {
        if(word.find(string) != std::string::npos) {
            type = KEY_WORD;
            currentToken = word;
            return;
        }
    }
        if (delimiters.find(word) != std::string::npos){
            type = PUNCTUATION;
            currentToken = word;
            return;
        }
        if (isdigit(word[0])){
            type = NUMERIC_CONST;
            currentToken = word;
            return;
        }
        if (word[0] == '\'') {
            type = STRING_CONST;
            currentToken = word;
            return;
        }
        if (word[0] == '$'){
            type = PREPROCESSOR_DIRECTIVE;
            currentToken = word;
            return;
        }
        if (word.find("//") != std::string::npos){
            type = COMMENT;
            currentToken = word;
            return;
        }

    for(auto string : operatorsTWO) {
        if(word.find(string) != std::string::npos) {
            type = OPERATOR_TWO;
            currentToken = word;
            return;
        }
    }

    for(auto string : operatorsONE) {
        if(word.find(string) != std::string::npos) {
            type = OPERATOR;
            currentToken = word;
            return;
        }
    }
        type = NONE;
        currentToken = word;
        //return 0;
}

std::string LexicalAnalyser::encode(std::string data) {
    std::string tmp = "";
        for (int i = 0; i < data.size(); i++) {
            switch (data[i]) {
                case '&':  tmp += "&amp;"; break;
                case '\"': tmp += "&quot;";break;
                case '\'': tmp += "&apos;";break;
                case '<':  tmp += "&lt;";  break;
                case '>':  tmp += "&gt;";  break;
                default:   tmp +=  data[i]; break;
            }
        }
        return tmp;
}

void LexicalAnalyser::initKeywords(){
    keywords.push_back("and");
    keywords.push_back("case");
    keywords.push_back("dispinterface");
    keywords.push_back("end");
    keywords.push_back("finally");
    keywords.push_back("implementation");
    keywords.push_back("interface");
    keywords.push_back("nil");
    keywords.push_back("out");
    keywords.push_back("raise");
    keywords.push_back("shl");
    keywords.push_back("to");
    keywords.push_back("uses");
    keywords.push_back("array");
    keywords.push_back("class");
    keywords.push_back("div");
    keywords.push_back("except");
    keywords.push_back("for");
    keywords.push_back("in");
    keywords.push_back("is");
    keywords.push_back("if");
    keywords.push_back("not");
    keywords.push_back("packed");
    keywords.push_back("record");
    keywords.push_back("shr");
    keywords.push_back("var");
    keywords.push_back("try");
    keywords.push_back("as");
    keywords.push_back("const");
    keywords.push_back("do");
    keywords.push_back("exports");
    keywords.push_back("function");
    keywords.push_back("inherited");
    keywords.push_back("label");
    keywords.push_back("object");
    keywords.push_back("procedure");
    keywords.push_back("repeat");
    keywords.push_back("string");
    keywords.push_back("type");
    keywords.push_back("while");
    keywords.push_back("asm");
    keywords.push_back("constructor");
    keywords.push_back("downto");
    keywords.push_back("file");
    keywords.push_back("goto");
    keywords.push_back("initialization");
    keywords.push_back("library");
    keywords.push_back("of");
    keywords.push_back("program");
    keywords.push_back("resourcestring");
    keywords.push_back("then");
    keywords.push_back("unit");
    keywords.push_back("with");
    keywords.push_back("begin");
    keywords.push_back("destructor");
    keywords.push_back("else");
    keywords.push_back("finalization");
    keywords.push_back("inline");
    keywords.push_back("mod");
    keywords.push_back("or");
    keywords.push_back("property");
    keywords.push_back("set");
    keywords.push_back("threadvar");
    keywords.push_back("until");
    keywords.push_back("xor");

    keywords.push_back("break");
    keywords.push_back("continue");
    keywords.push_back("false");
    keywords.push_back("on");
    keywords.push_back("operator");
    keywords.push_back("true");
}
void LexicalAnalyser::initDelimiters(){
    delimiters = ", \t\n\r\b;()";
}
void LexicalAnalyser::initOperators(){

    operatorsTWO.push_back(":=");
    operatorsTWO.push_back("<>");
    operatorsTWO.push_back(">=");
    operatorsTWO.push_back("<=");
    operatorsTWO.push_back("..");
    operatorsTWO.push_back("^=");
    operatorsTWO.push_back(">>");
    operatorsTWO.push_back("<<");

    operatorsONE.push_back("+");
    operatorsONE.push_back("-");
    operatorsONE.push_back("*");
    operatorsONE.push_back("/");
    operatorsONE.push_back(":");
    operatorsONE.push_back("=");
    operatorsONE.push_back(">");
    operatorsONE.push_back("<");
    operatorsONE.push_back(".");

    operatorsONE.push_back("div");
    operatorsONE.push_back("mod");
    operatorsONE.push_back("and");
    operatorsONE.push_back("or");
    operatorsONE.push_back("not");
    operatorsONE.push_back("xor");
    operatorsONE.push_back("sqr");
    operatorsONE.push_back("sqrt");
    operatorsONE.push_back("pow");
    operatorsONE.push_back("abs");
    operatorsONE.push_back("arctan");
    operatorsONE.push_back("cos");
    operatorsONE.push_back("sin");
    operatorsONE.push_back("frac");
    operatorsONE.push_back("random");
    operatorsONE.push_back("inc");
    operatorsONE.push_back("dec");
}