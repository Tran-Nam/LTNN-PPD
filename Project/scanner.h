#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define MAX_IDENT_LEN 10
#define MAX_NUM_LEN 9

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

extern TokenStruct tokenList[5000];
extern int indexToken;

void scanner(FILE *f);

TokenType getToken(void);
void error(const char msg[]);
void factor(void);
void term(void);
void expression(void);
void condition(void);
void statement(void);
void block(void);
void program(void);
void parser(void);
// void tmp(void);
// void parser(FILE *f);
// TokenType *getToken();