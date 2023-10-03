#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <ctype.h>
#include <vector>
#include <cstring>
using namespace std;

//Checks if the given token is a punctuation
bool isPunctuation(char c) {
    //Predefined set of symbols
    char symbol[] = {'(', ')', '[', ']', '{', '}', ';', ' ', '+',
                     '-', '*', '/', '>', '<', '=', '&', '|', ','};
    //Compares the given token with predefined symbols
    for (int i = 0; i < strlen(symbol); i++) {
        if (c == symbol[i])
            return true;
    }
    //Fails to match. Proceeds onto the next state
    return false;
}

//Checks if given token is a seperator
bool isSeparator(char c) {
    //Predefined set of symbols - funct. and parameter seperators
    char separator[] = {'(', ')', '[', ']', '{', '}', ';'};
    //Compares the given token with predefined symbols
    for (int i = 0; i < strlen(separator); i++) {
        if (c == separator[i])
            return true;
    }
    //Fails to match. Proceeds onto the next state
    return false;
}

//Checks if the given token is an identifier
bool validIdentifier(char* str) {
    //Local variables
    int i;
    int len = strlen(str);
    //Checks for any identifier violations
    if (str[0] >= 0 && str[0] <= 9 && isPunctuation(str[0]))
        return false;
    // Checks if parameter is a 1 length character identifier
    if (len == 1) {
        return true;
    } else {
        //Checks identifer for any special characters
        for (i = 1 ; i < len ; i++) {
            if (isPunctuation(str[i]))
                return false;
        }
    }
    //Satisified all requirements for an identifier
    return true;
}

//Checks if the given character is an operator
bool isOperator(char c) {
    //Compares character with operators
    if (c == '-' || c == '+' || c == '*' || c == '/' || c == '>' ||
        c == '<' || c == '=' || c == '|' || c == '&')
       return true;
    //Fails to match. Proceeds onto the next state
    return false;
}

//Checks if the given substring is a reserved keyword
bool isKeyword(const char *str) {
    //Compares character with reserved keywords
    if (!strcmp(str, "extern")  || !strcmp(str, "else")     ||
        !strcmp(str, "while")   || !strcmp(str, "do")       ||
        !strcmp(str, "break")   || !strcmp(str, "continue") ||
        !strcmp(str, "int")     || !strcmp(str, "double")   ||
        !strcmp(str, "float")   || !strcmp(str, "return")   ||
        !strcmp(str, "char")    || !strcmp(str, "case")     ||
        !strcmp(str, "long")    || !strcmp(str, "short")    ||
        !strcmp(str, "typedef") || !strcmp(str, "switch")   ||
        !strcmp(str, "unsigned")|| !strcmp(str, "void")     ||
        !strcmp(str, "static")  || !strcmp(str, "struct")   ||
        !strcmp(str, "sizeof")  || !strcmp(str,"long")      ||
        !strcmp(str, "volatile")|| !strcmp(str, "typedef")  ||
        !strcmp(str, "enum")    || !strcmp(str, "const")    ||
        !strcmp(str, "union")   || !strcmp(str, "bool")     ||
        !strcmp(str, "if"))
    return true;
    //Fails to match. Proceeds onto the next state
    return false;
}


//Checks if the given substring is a number
bool isConstant(char* str) {
    //Local Variables
    int i;
    int len = strlen(str);
    int decimal = 0;
    //Examines whether the parameter is a double or float
    for (i = 0 ; i < len ; i++) {
        //Checks if the parameter contains a decimal pt
        if (decimal > 0 && str[i] == '.') {
            return true;
        } else if (decimal < 1) {
            decimal++;
        }
        //Checks if the parameter is NOT a numerical value
        if (!isdigit(str[i]) || (str[i] == '-' && i > 0))
            return false;
    }
    //Satisfies all requirements for constant
    return true;
}

//Extracts a sub-string from the container
char* subStr(char* realStr, int l, int r) {
    //Local variable
    int i;
    //Allocates memory for sub-string
    char* str = (char*) malloc(sizeof(char) * (r - l + 2));
    //Copies the elements to the new container
    for (i = l; i <= r; i++) {
        str[i - l] = realStr[i];
        str[r - l + 1] = '\0';
    }
    //Returns the extracted sub-string
    return str;
}

/* The "lexer() function" is an essential mediator in the lexical analysis 
   phase. It's responsible for breaking the source into tokens. Each
   token has its unique properties that is categorized as a keyword, identifier, 
   constant, operator, and etc... and is validated according to the language’s 
   syntactic and semantic rules. This funct. lays the groundwork for 
   subsequent stages of compilation, enabling further analysis and processing
   of the tokens to generate correct and efficient executable code. */
void lexer(char* input, ofstream& output_file) {
    //Local variables
    int l  = 0;
    int r  = 0; 
    int id = 0;
    int len = strlen(input);

    //Responsible for writing an output file
    output_file << "Welcome To Our Lexical Analyzer!\n\nCODE: ";
        /*Transcribes the source code stored in "input_scode.txt"
          or any file with a proper file path*/
        for (int i = 0; i < len; i++)
            output_file << input[i];
    output_file << "\n\nOUTPUT:\nTOKEN          | LEXEME \n";
    output_file << "------------------------------\n";

    //Responsible for displaying result on stdout - NOT REQUIRED
    cout << "Welcome To Our Lexical Analyzer!\n\nCODE: ";
        for (int i = 0; i < len; i++)
            cout << input[i];
    cout << "\n\nOUTPUT:\nTOKEN          | LEXEME \n";
    cout << "------------------------------\n";

    /*Breaks down the source into tokens, then goes through each function for analysis
      and categorized based off the token's unique properties */
    while (r <= len && l <= r ) {
        //Checks if character is a special character
        if (!isPunctuation(input[r]))
            r++;
        //Checks if the given string is a special character
        if (isPunctuation(input[r]) && l == r) {
            //The given string is categorized as an operator
            if (isOperator(input[r])) {
                output_file << "Operator         " << input[r] << endl;
                cout        << "Operator         " << input[r] << endl;
            }
            r++;
            l  = r;
            //Checks if the given string for further analysis
            } else if (isPunctuation(input[r]) && l  != r
                       || (r == len && l != r)) {
                //Extracts and stores the substring in "sub"
                char* sub = subStr(input, l, r - 1);

                //File writing method and displays on stdout
                if (isKeyword(sub)) {
                    output_file << "Keyword          " << sub << endl;
                    cout        << "Keyword          " << sub << endl;
                } else if (isConstant(sub)) {
                    output_file << "Constant         " << sub << endl;
                    cout        << "Constant         " << sub << endl;
                } else if (validIdentifier(sub) && !isPunctuation(input[r - 1])) {
                    if (input[l - 1] != ' ' && isSeparator(input[l - 1])) {
                            output_file << "Separator        " << input[l - 1] << endl;
                            cout        << "Separator        " << input[l - 1] << endl;
                            id++;
                    }
                    output_file << "Identifier       " << sub << endl;
                    cout        << "Identifier       " << sub << endl;
                }
                if (isSeparator(input[r])) {
                    if (input[r] != ' ' && !isOperator(input[r])) {
                        output_file << "Separator        " << input[r] << endl;
                        cout        << "Separator        " << input[r] << endl;
                    } else if (input[l - 1] != ' ' && isSeparator(input[l - 1]) && id == 0) {
                        output_file << "Separator        " << input[l - 1] << endl;
                        cout        << "Separator        " << input[l - 1] << endl;
                        id--;
                    }
                }
                l  = r;
            }
        }
    return;
}

int main(int argc, char* argv[]) {
    vector<string> args(argv + 1, argv + argc);
    string input_file_name = args[0];
    ifstream input_file_stream(input_file_name);
    ofstream output_file("output.txt");
    char src[100];
    //Checks if input file was provided
    if (argc < 2) {
        cerr << "ERROR: Lexical Analyzer cannot find a specified path.\n";
        return 1;
    }
    //Verify the file is open to read
    if (!input_file_stream.is_open()) {
        cerr << "Failed to open file: " << input_file_name << endl;
        exit(1);
    } else if (input_file_stream.is_open()) {
        input_file_stream.getline(src, 100);
        lexer(src, output_file);
    }
    //Closes input and output file
    input_file_stream.close();
    output_file.close();

    return 0;
}
