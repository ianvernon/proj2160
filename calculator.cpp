#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <cstdio>

using namespace std;
// This is the token type, and contains all possible tokens in our language.
typedef enum {
    T_PLUS, //0
    T_MINUS, //1
    T_MULTIPLY, //2
    T_POWER, //3
    T_DIVIDE, //4
    T_OPENPAREN, //5
    T_CLOSEPAREN, //6
    T_OPENBRACKET, //7
    T_CLOSEBRACKET, //8
    T_EQUALS, //9
    T_SEMICOLON, //10
    T_M, //11
    T_PRINT, // 12
    T_NUMBER, //13
    T_EOF //14
} token;

// This function will convert a token to a string, for display.
std::string tokenToString(token toConvert) {
    switch (toConvert) {
        case T_PLUS:
            return std::string("+");
        case T_MINUS:
            return std::string("-");
        case T_MULTIPLY:
            return std::string("*");
        case T_POWER:
            return std::string("**");
        case T_DIVIDE:
            return std::string("/");
        case T_OPENPAREN:
            return std::string("(");
        case T_CLOSEPAREN:
            return std::string(")");
        case T_OPENBRACKET:
            return std::string("[");
        case T_CLOSEBRACKET:
            return std::string("]");
        case T_EQUALS:
            return std::string("=");
        case T_SEMICOLON:
            return std::string(";");
        case T_M:
            return std::string("M");
        case T_PRINT:
            return std::string("print");
        case T_NUMBER:
            return std::string("number");
        case T_EOF:
            return std::string("EOF");
    }
}

// Throw this error when the parser expects a given token from the scanner
// and the next token the scanner finds does not match.
void mismatchError(int line, token expected, token found) {
    std::cerr << "Parse error: expected " << tokenToString(expected) << " found " << tokenToString(found) << " at line " << line << std::endl;
    exit(1);
}

// Throw this error when the parser encounters a token that is not valid
// at the beginning of a specific grammar rule.
void parseError(int line, token found) {
    std::cerr << "Parse error: found invalid token " << tokenToString(found) << " at line " << line << std::endl;
    exit(1);
}

// Throw this error when an invalid character is found in the input, or
// if a bad character is found as part of a print token.
void scanError(int line, char badCharacter) {
    std::cerr << "Scan error: found invalid character " << badCharacter << " at line " << line << std::endl;
    exit(1);
}

// Throw this error when the index for memory is out of bounds (less
// than 0 or greater than 99). ONLY THROW IF evaluate flag is true.
void indexError(int line, int index) {
    std::cerr << "Semantic error: index " << index << " out of bounds at line " << line << std::endl;
    exit(1);
}

// Throw this error when a division by zero occurs. ONLY THROW IF evaluate flag is true.
void divideError(int line) {
    std::cerr << "Semantic error: division by zero at line " << line << std::endl;
    exit(1);
}

class Scanner {
    // You are allowed to private fields to the scanner, and this may be
    // necessary to complete your implementation. However, this is not
    // required as part of the project specification.
    
public:
    token nextToken(); 
    void eatToken(token);
    int lineNumber();
    int getNumberValue();
    Scanner();
    
    // You may need to write a constructor for the scanner. This is not
    // required by the project description, but you may need it to complete
    // your implementation.
    // WRITEME
    
private:
    int currentLineNumber;
};
Scanner::Scanner(){
    currentLineNumber = 1;
    
}

//TODO - what to do if the input we take in is bad?
token Scanner::nextToken() {
    // This is a placeholder token, you will need to replace this code
    // with code to return the correct next token.
    
    // WRITEME
    // get current position in file to reset to once we are done scanning for the next token
    // int startingPos = cin.tellg();
    //cout << "startingPos: " << startingPos << endl;
    // create string that will contain values that are in token
    string currentString;
    // current char we are analyzing in input stream
    char currentChar;
    // continue adding character to string until we reach white space
    // which is one of the cases in which we can delinate tokens from one another
    // also need checks within loop to see whether a certain character delineates a certain token
    // from the characters surrounding it - e.g., '+' in '5+5' being separate from 5 and 5 despite
    // there being no whitespace between it and its surrounding 5's
    //int whiteSpaceCount = 0;
    while((currentChar = cin.get()) != EOF)
    {
        //cout << "cin.tell(g)" << cin.tellg() << endl;
        if(!isspace(currentChar))
        {
            // return print token
            if(currentChar == 'p')
            {
                for(int i = 1; i < 5; i++)
                {
                    currentChar = cin.get();
                    if(currentChar == EOF)
                    {
                        scanError(currentLineNumber, currentChar);
                    }
                    else
                    {
                        if(i==1 && currentChar == 'r'){
                            continue;
                        }
                        else if(i==2 && currentChar == 'i')
                        {
                            continue;
                        }
                        else if(i==3 && currentChar == 'n')
                        {
                            continue;
                        }
                        else if(i==4 && currentChar == 't')
                        {
                            cin.putback('t');
                            cin.putback('n');
                            cin.putback('i');
                            cin.putback('r');
                            cin.putback('p');
                            return T_PRINT;
                        }
                        else
                        {
                            scanError(currentLineNumber, currentChar);
                        }
                    }
                }
            }
            else if(currentChar == '+')
            {
                //cout << startingPos << endl;
                cin.putback(currentChar);
                //cout << "+ Success" << endl;
                return T_PLUS;
            }
            else if(currentChar == '-')
            {
                //cout << startingPos << endl;
                
                cin.putback(currentChar);
                //cout << "- Success" << endl;
                return T_MINUS;
            }
            else if(currentChar == '/')
            {
                //cout << startingPos << endl;
                
                cin.putback(currentChar);
                return T_DIVIDE;
            }
            else if(currentChar == '(')
            {
                //cout << startingPos << endl;
                
                cin.putback(currentChar);
                return T_OPENPAREN;
            }
            else if(currentChar == ')')
            {
                //cout << startingPos << endl;
                
                cin.putback(currentChar);
                return T_CLOSEPAREN;
            }
            else if(currentChar == '[')
            {
                //cout << startingPos << endl;
                
                cin.putback(currentChar);
                return T_OPENBRACKET;
            }
            else if(currentChar == ']')
            {
                //cout << startingPos << endl;
                
                cin.putback(currentChar);
                //cout << "] Success" << endl;
                return T_CLOSEBRACKET;
            }
            else if(currentChar == '=')
            {
                //cout << startingPos << endl;
                
                cin.putback(currentChar);           // cout << "= Success" << endl;
                return T_EQUALS;
            }
            else if(currentChar == ';')
            {
                //cout << startingPos << endl;
                
                //cin.seekg(startingPos, cin.beg);
                // cout << "; Success" << endl;
                //cout << "SEMICOLON ENCOUNTERED" << endl;
                cin.putback(';');
                return T_SEMICOLON;
            }
            else if(currentChar == 'm' || currentChar == 'M')
            {
                //cout << startingPos << endl;
                
                cin.putback(currentChar);
                return T_M;
            }
            else if(isdigit(currentChar))
            {
                // fix this!
                //cout << startingPos << endl;
                while(isdigit(cin.peek()))
                {
                    currentChar = cin.get();
                }
                cin.putback(currentChar);
                return T_NUMBER;
            }
            else if(currentChar == '*')
            {
                if(cin.peek() == '*')
                {
                    //cout << startingPos << endl;
                    
                    cin.putback('*');
                    
                    //cout << "** Success" << endl;
                    return T_POWER;
                }
                else
                {
                    //cout << startingPos << endl;
                    
                    cin.putback('*');
                    // cout << "* Success" << endl;
                    return T_MULTIPLY;
                }
            }
            else if(currentChar == '\n')
            {
                currentLineNumber++;
            }
            else if(currentChar == EOF)
            {

                cin.putback(EOF);
                return T_EOF;
            }
            else
            {
                scanError(currentLineNumber, currentChar);
                continue;
            }

        }
        else
        {
            if(currentChar == '\n' || currentChar == '\r')
            {
                currentLineNumber++;
            }
        }
    }
    return T_EOF;
}

void Scanner::eatToken(token toConsume) {
    // This function consumes the next token.
    
    // WRITEME
    
    //string currentString;
    char currentChar;
   // cout << "*****************\nEating Token: " << toConsume << endl;
    // string nextTokenString = tokenToString(nextToken());
   // cout << "toConsume = " << toConsume << "\nnextTokenString  = " << tokenToString(nextToken()) << endl;
   // cout << "nextToken = " << nextToken() << endl;
    if(toConsume == nextToken())
    {
        switch(toConsume)
        {
            case(T_PLUS): //*
                cin.get();
                break;
            case(T_MINUS): //*
                cin.get();
                break;
            case(T_MULTIPLY) : //*
                cin.get();
                break;
            case(T_POWER) : //*
                cin.get();
                cin.get();
                break;
            case(T_DIVIDE): //*
                cin.get();
                break;
            case(T_OPENPAREN) : //*
                cin.get();
                break;
            case(T_CLOSEPAREN) : //*
                cin.get();
                break;
            case(T_OPENBRACKET) : //*
                cin.get();
                break;
            case(T_CLOSEBRACKET) : //*
                cin.get();
                break;
            case(T_EQUALS) : //*
                cin.get();
                break;
            case(T_SEMICOLON) : //*
                cin.get();
                break;
            case(T_M) : //*
                cin.get();
                break;
            case(T_PRINT) :
                cin.get();
                cin.get();
                cin.get();
                cin.get();
                cin.get();
                break;
            case(T_NUMBER) :
                cin.get();
                break;
            case(T_EOF) :
                cin.get();
                break;
        }
        return;
    }
    else
    {
        mismatchError(currentLineNumber, toConsume, nextToken());
        return;
    }
}

int Scanner::lineNumber() {
    // This is also a placeholder, you will need to replace this code
    // with code to return the current line number (to be used for errors).
    
    // WRITEME
    return currentLineNumber;
}

int Scanner::getNumberValue() {
    // This is also a placeholder, you will need to replace this code
    // with code to return the last number value that was scanned. This
    // will be used when evaluating expressions.
    
    // WRITEME
    return 0;
}

class Parser {
    // You are allowed to private fields to the parser, and this may be
    // necessary to complete your implementation. However, this is not
    // required as part of the project specification.
    
private:
    Scanner scanner;
    
    token lookahead;
    
    // This flag indicates whether we should perform evaluation and throw
    // out-of-bounds and divide-by-zero errors. ONLY evaluate and throw these
    // errors if this flag is set to TRUE.
    bool evaluate = false;
    
    // You will need to add more methods for handling nonterminal symbols here.
    void Start();
    void Statements();
    void StatementsPrime();
    void Statement();
    void Expression();
    void ExpressionPrime();
    void Term();
    void TermPrime();
    void Factor();
    void FactorPrime();
    void Thing();
    void match(token);
    // WRITEME

public:
    void parse();
    Parser(bool evaluate) : evaluate(evaluate) {
        // You may need to complete a Parser constructor here
        // WRITEME
    }
};

void Parser::parse() {
    // This is the entry point for the parser, which simply starts parsing
    // the grammar by calling the function for the start symbol.
    lookahead = scanner.nextToken();
   // cout << tokenToString(lookahead) << endl;
    Start();
    scanner.eatToken(T_EOF);
    
}

void Parser::Start() {
    // This is an example of a recursive-descent function for a
    // non-terminal symbol. In this case, it is just a placeholder
    // which accepts infinite numbers of T_PLUS. You will need to
    // replace this with correct code for the real grammar start symbol.
    
    // WRITEME
    /*switch (scanner.nextToken()) {
        case T_PLUS:
            scanner.eatToken(T_PLUS);
            Start();
            break;
        case T_EOF:
            break;
        default:
            parseError(scanner.lineNumber(), scanner.nextToken());
            break;
    }*/
    
    Statements();
}

void Parser::Statements(){
    //cout << "next Token = " << tokenToString(lookahead) << endl;

    Statement();
    StatementsPrime();
}

void Parser::StatementsPrime(){
    //cout << "next Token = " << tokenToString(lookahead) << endl;
    //cout << "statements prime" << endl;
    switch(lookahead){
        case T_SEMICOLON:
            // eat semicolon
            scanner.eatToken(T_SEMICOLON);
            lookahead = scanner.nextToken();
            Statement();
            StatementsPrime();
        case T_EOF:
            break;
        default:
           // cout << "parse error StatementsPrime" << endl;
            parseError(scanner.lineNumber(), lookahead);
            break;
    }
    
    
    // since Statements can be epsilon, we have to check what the lookahead is, and if the lookahead
    // isn't in the follow set of the current grammar rule (StatementsPrime), then throw parse Errror
    // only do this for the ones that have epsilon transitions
   /* if(lookahead != T_EOF)
    {
        parseError(scanner.lineNumber(),
    }*/
    
    
}
void Parser::Statement(){
    //cout << "next Token = " << tokenToString(lookahead) << endl;

    switch(lookahead)
    {
        case T_M:
            // TO DO LOOK AT THIS eatToken(T_)
            //cout << "here" << endl;
            // eat m
            scanner.eatToken(T_M);
            lookahead = scanner.nextToken();
            // eat [
            scanner.eatToken(T_OPENBRACKET);
            lookahead = scanner.nextToken();
            //cout << "lookahead is now: " << tokenToString(lookahead) << endl;
            //cout << "here again" << endl;
            Expression();
            // eat ]
            scanner.eatToken(T_CLOSEBRACKET);
            lookahead = scanner.nextToken();
            // eat =
            scanner.eatToken(T_EQUALS);
            lookahead = scanner.nextToken();
            Expression();
            break;
        case T_PRINT:
            // eat print
            scanner.eatToken(T_PRINT);
            lookahead = scanner.nextToken();
            Expression();
            break;
        default:
            //cout << "parse error Statement" << endl;
            parseError(scanner.lineNumber(), lookahead);
            break;
    }
    
}
void Parser::Expression()
{
    Term();
    ExpressionPrime();
}

void Parser::ExpressionPrime()
{
 //   cout << "next Token = " << tokenToString(lookahead) << endl;
  //  cout << "expression prime" << endl;
    switch(lookahead)
    {
        case(T_PLUS):
            scanner.eatToken(lookahead);
            lookahead = scanner.nextToken();
            Term();
            ExpressionPrime();
            break;
        case(T_MINUS):
            scanner.eatToken(lookahead);
            lookahead = scanner.nextToken();
            Term();
            ExpressionPrime();
            break;
        case(T_CLOSEBRACKET):
            break;
        case(T_CLOSEPAREN):
            break;
        case(T_SEMICOLON):
            break;
        case(T_EOF):
            break;
        default:
            //cout << "parse error Expr Prime" << endl;
            parseError(scanner.lineNumber(), lookahead);
            break;
        //eof case?
    }
}

void Parser::Term()
{
    Factor();
    TermPrime();
}

void Parser::TermPrime()
{
    //cout << "next Token = " << tokenToString(lookahead) << endl;

    switch(lookahead)
    {
        case(T_MULTIPLY):
            // eat multiply
            scanner.eatToken(lookahead);
            lookahead = scanner.nextToken();
            Factor();
            TermPrime();
            break;
        case(T_DIVIDE):
            // eat divide
            scanner.eatToken(lookahead);
            lookahead = scanner.nextToken();
            Factor();
            TermPrime();
            break;
        case(T_PLUS):
            break;
        case(T_MINUS):
            break;
        case(T_CLOSEBRACKET):
            break;
        case(T_CLOSEPAREN):
            break;
        case(T_SEMICOLON):
            break;
        case(T_EOF):
            break;
        default:
            //cout << "parse error Term Prime" << endl;
            parseError(scanner.lineNumber(), lookahead);
            break;
    }
}

void Parser::Factor()
{
    Thing();
    FactorPrime();
}

void Parser::FactorPrime()
{
    //cout << "next Token = " << tokenToString(lookahead) << endl;

    switch(lookahead)
    {
        case(T_POWER):
            // eat **
            scanner.eatToken(lookahead);
            lookahead = scanner.nextToken();
            Thing();
            FactorPrime();
            break;
        case(T_MULTIPLY):
            break;
        case(T_DIVIDE):
            break;
        case(T_PLUS):
            break;
        case(T_MINUS):
            break;
        case(T_CLOSEBRACKET):
            break;
        case(T_CLOSEPAREN):
            break;
        case(T_SEMICOLON):
            break;
        case(T_EOF):
            break;
        default:
           // cout << "parse error factor prime" << endl;
            parseError(scanner.lineNumber(), lookahead);
            break;
    }
}

void Parser::Thing()
{
    //cout << "next Token = " << tokenToString(lookahead) << endl;

    switch(lookahead)
    {
        case(T_OPENPAREN):
            scanner.eatToken(lookahead);
            lookahead = scanner.nextToken();
            Expression();
            scanner.eatToken(lookahead);
            lookahead = scanner.nextToken();
            break;
        case(T_M):
            scanner.eatToken(T_M);
            lookahead = scanner.nextToken();
            scanner.eatToken(lookahead);
            lookahead = scanner.nextToken();
            Expression();
            scanner.eatToken(lookahead);
            lookahead = scanner.nextToken();
            break;
        case(T_NUMBER):
            scanner.eatToken(lookahead);
            lookahead = scanner.nextToken();
            break;
        default:
          //  cout << "parse error Thing" << endl;
            parseError(scanner.lineNumber(), lookahead);
            break;
    }
}

void Parser::match(token currentToken)
{
    if(currentToken == lookahead)
    {
       // cout << "currentToken = " << tokenToString(currentToken) << endl;
        scanner.eatToken(currentToken);
        lookahead = scanner.nextToken();
    }
    else
    {
       // cout << "here 1" << endl;
        if((currentToken == T_CLOSEBRACKET && lookahead == T_CLOSEPAREN) || (currentToken == T_OPENBRACKET && lookahead == T_M))
      {
         // cout << "here 2" << endl;
          mismatchError(scanner.lineNumber(), currentToken, lookahead);
      }
       // cout << "here 3" << endl;
      parseError(scanner.lineNumber(), lookahead);
        //}
    }
}


int main(int argc, char* argv[]) {
    if (argc == 2 && (strcmp(argv[1], "-s") == 0)) {
        Scanner scanner;
        while (scanner.nextToken() != T_EOF) {
            std::cout << tokenToString(scanner.nextToken()) << " ";
            scanner.eatToken(scanner.nextToken());
        }
        std::cout<<std::endl;
    } else if (argc == 2 && (strcmp(argv[1], "-e") == 0)) {
        Parser parser(true);
        parser.parse();
    } else {
        //cout << "should be in here" << endl;
        Parser parser(false);
        parser.parse();
    }
    return 0;
}
