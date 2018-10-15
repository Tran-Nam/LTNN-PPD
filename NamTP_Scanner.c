// gcc Scanner.c
// ./a.out filename


#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_IDENT_LEN 10

typedef enum{
    NONE=0, IDENT, NUMBER, BEGIN, CALL, CONST, DO, ELSE, END, FOR, IF, ODD, 
    PROCEDURE, PROGRAM, THEN, TO, VAR, WHILE, PLUS, MINUS, TIMES, SLASH, EQU, 
    NEQ, LSS, LEQ, GTR, GEQ, LPARENT, RPARENT, LBRACK, RBRACK, PERIOD, COMMA, 
    SEMICOLON, ASSIGN, PERCENT
} TokenType;

static const char *str[] = {"NONE", "IDENT", "NUMBER", "BEGIN", "CALL", "CONST", "DO", "ELSE", "END", "FOR", "IF", "ODD", 
    "PROCEDURE", "PROGRAM", "THEN", "TO", "VAR", "WHILE", "PLUS", "MINUS", "TIMES", "SLASH", "EQU", 
    "NEQ", "LSS", "LEQ", "GTR", "GEQ", "LPARENT", "RPARENT", "LBRACK", "RBRACK", "PERIOD", "COMMA", 
    "SEMICOLON", "ASSIGN", "PERCENT"};

typedef struct {
    TokenType Token; //Token nhan dang duoc
    int Num; //Tu vung khi Token la NUMBER
    char Id[MAX_IDENT_LEN + 1]; //Tu vung khi Token la IDENT
} TokenStruct;

const char* KeyWord[] = {
    "begin", "const", "do", "else", "end", "for", "if", "odd", "procedure",
    "program", "then", "to", "var", "while"
};

// int getCh(void){
//     int c = fgetc(f);
//     return tolower(c);
// }

TokenStruct tokenList[500]; // mang luu cac tu vung duoc doan nhan
int indexToken=0;

void main(int argc, char **argv){
    // printf("%s\n", str[2]);

    FILE* f;
    f = fopen(argv[1], "r");
    
    int c;
    c = fgetc(f);
    
    // int k=0;
    while(c!=EOF){
        
        // bo ki tu thua
        // printf("-----");
        if(c==' ' || c=='\n' || c=='\t'){
            c = fgetc(f);
            // printf("%c", c);
            continue;
        }
        

        // ident
        if(isalpha(c)){
            char ident[MAX_IDENT_LEN];
            memset(ident, 0, sizeof ident);
            int j=0;
            ident[j]=tolower(c);
            j++;
            // printf("%d", i);
            // c = fgetc(f);
            // printf("%c", c);
            while(isalpha(c=fgetc(f)) || isdigit(c)){
                if(j>9){
                    continue;// Ident dai hon 10 ki tu
                }

                ident[j] = tolower(c);
                j++;
                // printf("%d", i);
            }

            // Kiem tra trung keyword
            int position; // tu khoa bi trung
            // printf("%s\n", ident);
            for(j=0; j<14; j++){
                if(!strcmp(ident, KeyWord[j])){
                    position = j;
                    break;
                }
                else position = -1;
            }
            // printf("%d\n", position);
            //neu bi trung
            switch(position){
                case 0:
                    tokenList[indexToken].Token = BEGIN;
                    break;

                case 1:
                    tokenList[indexToken].Token = CONST;
                    break;

                case 2:
                    tokenList[indexToken].Token = DO;
                    break;

                case 3:
                    tokenList[indexToken].Token = ELSE;
                    break;

                case 4:
                    tokenList[indexToken].Token = END;
                    break;
                
                case 5:
                    tokenList[indexToken].Token = FOR;
                    break;
                
                case 6:
                    tokenList[indexToken].Token = IF;
                    break;
                
                case 7:
                    tokenList[indexToken].Token = ODD;
                    break;
                
                case 8:
                    tokenList[indexToken].Token = PROCEDURE;
                    break;
                
                case 9:
                    tokenList[indexToken].Token = PROGRAM;
                    break;
                
                case 10:
                    tokenList[indexToken].Token = THEN;
                    break;
                
                case 11:
                    tokenList[indexToken].Token = TO;
                    break;
                
                case 12:
                    tokenList[indexToken].Token = VAR;
                    break;
                
                case 13:
                    tokenList[indexToken].Token = WHILE;
                    break;
                    
                default:
                    tokenList[indexToken].Token = IDENT;
                    strcpy(tokenList[indexToken].Id, ident);
                    break;               
            }
            
            indexToken+=1;
        }

        else if(isdigit(c)){
            int a = c - 48;
            // int b = a;
            while(isdigit(c=fgetc(f))){
                a = 10*a + c - 48;
            }

            tokenList[indexToken].Token = NUMBER;
            tokenList[indexToken].Num = a;
            indexToken++;
        }

        else if(c=='+'){
            tokenList[indexToken].Token = PLUS;
            indexToken++;
            c = fgetc(f);
        }

        else if(c=='-'){
            tokenList[indexToken].Token = MINUS;
            indexToken++;
            c = fgetc(f);
        }

        else if(c=='*'){
            tokenList[indexToken].Token = TIMES;
            indexToken++;
            c = fgetc(f);
        }

        else if(c=='/'){
            tokenList[indexToken].Token = SLASH;
            indexToken++;
            c = fgetc(f);
        }

        else if(c=='='){
            tokenList[indexToken].Token = EQU;
            indexToken++;
            c = fgetc(f);
        }

        else if(c=='<'){
            c=fgetc(f);
            if(c=='>'){
                tokenList[indexToken].Token = NEQ;
            }
            else if(c=='='){
                tokenList[indexToken].Token = LEQ;
            }
            else tokenList[indexToken].Token = LSS;
            indexToken++;
            c = fgetc(f);
        }

        else if(c=='>'){
            c=fgetc(f);
            if(c=='='){
                tokenList[indexToken].Token = GEQ;
            }
            else tokenList[indexToken].Token = GTR;
            indexToken++;
            c = fgetc(f);
        }

        else if(c=='('){
            tokenList[indexToken].Token = LPARENT;
            indexToken++;
            c = fgetc(f);
        }

        else if(c==')'){
            tokenList[indexToken].Token = RPARENT;
            indexToken++;
            c = fgetc(f);
        }

        else if(c=='['){
            tokenList[indexToken].Token = LBRACK;
            indexToken++;
            c = fgetc(f);
        }

        else if(c==']'){
            tokenList[indexToken].Token = RBRACK;
            indexToken++;
            c = fgetc(f);
        }

        else if(c=='.'){
            tokenList[indexToken].Token = PERIOD;
            indexToken++;
            c = fgetc(f);
        }

        else if(c==','){
            tokenList[indexToken].Token = COMMA;
            indexToken++;
            c = fgetc(f);
        }

        else if(c==';'){
            tokenList[indexToken].Token = SEMICOLON;
            indexToken++;
            c = fgetc(f);
        }

        else if(c=='%'){
            tokenList[indexToken].Token = PERCENT;
            indexToken++;
            c = fgetc(f);
        }

        else if(c==':'){
            c=fgetc(f);
            if(c=='='){
                tokenList[indexToken].Token = ASSIGN;
                indexToken++;
            }
            c = fgetc(f);
        }
        else{
            tokenList[indexToken].Token = NONE;
            indexToken++;
            c = fgetc(f);
        }

       


    }
    int j;
    for (j=0; j<indexToken; j++){
        int k = tokenList[j].Token;
        printf("Index: %d\t", j);
        if(k==1){
            printf("Token: %s\tName: %s\n", str[k], tokenList[j].Id);
        }
        else if(k==2){
            printf("Token: %s\tNum: %d\n", str[k], tokenList[j].Num);
        }
        else printf("Token: %s\n", str[k]);

        // printf("Index: %d\tToken: %d\tName: %s\n", j, tokenList[j].Token, tokenList[j].Id);
    }
    
}

