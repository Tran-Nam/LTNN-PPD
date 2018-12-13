#include <stdio.h>
#include <ctype.h>
#define MAX_IDENT_LEN 10

typedef enum{
    NONE=0, IDENT, NUMBER, BEGIN, CALL, CONST, DO, ELSE, END, FOR, IF, ODD, 
    PROCEDURE, PROGRAM, THEN, TO, VAR, WHILE, PLUS, MINUS, TIMES, SLASH, EQU, 
    NEQ, LSS, LEQ, GTR, GEQ, LPARENT, RPARENT, LBRACK, RBRACK, PERIOD, COMMA, 
    SEMICOLON, ASSIGN, PERCENT
} TokenType;

typedef struct {
    TokenType Token; //Token nhan dang duoc
    int Num; //Tu vung khi Token la NUMBER
    char Id[MAX_IDENT_LEN + 1]; //Tu vung khi Token la IDENT
} TokenStruct;

TokenStruct tokenList[1000];
int indexToken;

TokenType getToken(FILE *f);
void error(const char msg[]);
void factor(void);
void term(void);
void expression(void);
void condition(void);
void statement(void);
void block(void);
void program(void);
void parser(FILE *f);