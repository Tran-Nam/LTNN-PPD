#include "scanner.h"

// int Token;
int indexToken;
int token;
int num;
TokenStruct tokenList[5000];
FILE *f;
char id[11];

// void tmp(void){
//     printf("%d\n", indexToken);
// }
void error(const char msg[]){
    printf("%s\n", msg);
    exit(0);
}

void term(){
    factor();
    while(token==TIMES || token==SLASH){
        token = getToken();
        factor();
    }
}
void factor(){
    if(token==IDENT){
        token = getToken();
        if(token==LBRACK){
            token = getToken();
            expression();
            if(token==RBRACK){
                token = getToken();
            } else error("Thieu dong ngoac!\n");
        }
    } else if(token==NUMBER){
        token = getToken();
    } else if(token==LPARENT){
        token = getToken();
        expression();
        if(token==RPARENT){
            token = getToken();
        } else error("Thieu dong ngoac!\n");
    } 
}

void expression(){
    if(token==PLUS || token==MINUS){
        token = getToken();
    }
    term();
    while(token==PLUS || token==MINUS){
        token = getToken();
        term();
    }
}

void condition(){
    expression();
    if(token==EQU || token==NEQ || token==LSS ||
    token==LEQ || token==GTR || token==GEQ){
            token = getToken();
            expression();
    } else error("Condition: Syntax error!\n");
}

void statement(){
    if(token==IDENT){
        token = getToken();
        if(token==LBRACK){
            token = getToken();
            expression();
            if(token==RBRACK){
                token = getToken();
            } else error("Thieu dong ngoac!\n");
        }
        if(token==ASSIGN){
            token = getToken();
            expression();
        } else error("Thieu toan tu gan!\n");    
    } 

    else if(token==CALL){
        token = getToken();
        if(token==IDENT){
            token = getToken();
            if(token==LPARENT){
                token = getToken();
                expression();
                while(token==COMMA){
                    token = getToken();
                    expression();
                }
                if(token==RPARENT){
                    token = getToken();
                } else error("Thieu dong ngoac!\n");
            } 
        } else error("Thieu ten ham!\n");
    }

    else if(token==BEGIN){
        token = getToken();
        statement();
        while(token==SEMICOLON){
            token = getToken();
            statement();
        }
        if(token==END){
            token = getToken();
        } else error("Thieu End!\n");
    }

    else if(token==IF){
        token = getToken();
        condition();
        if(token==THEN){
            token = getToken();
            statement();
            if(token==ELSE){
                token = getToken();
                statement();
            }
        } else error("Thieu ELSE!\n");
    }

    else if(token==WHILE){
        token = getToken();
        condition();
        if(token==DO){
            token = getToken();
            statement();
        } else error("Thieu DO!\n");
    }

    else if(token==FOR){
        token = getToken();
        if(token==IDENT){
            token = getToken();
            if(token==ASSIGN){
                token = getToken();
                expression();
                if(token==TO){
                    token = getToken();
                    expression();
                    if(token==DO){
                        token = getToken();
                        statement();
                    } else error("Thieu DO!\n");
                } else error("Thieu TO!\n");
            } else error("Thieu ASSIGN!\n");
        } else error("Thieu IDENT!\n");
    }

}

void block(){
    if(token==CONST){
        token = getToken();
        if(token==IDENT){
            token = getToken();
            if(token==EQU){
                token = getToken();
                if(token==NUMBER){
                    token = getToken();
                    while(token==COMMA){
                        token = getToken();
                        if(token==IDENT){
                            token = getToken();
                            if(token==EQU){
                                token = getToken();
                                if(token==NUMBER){
                                    token = getToken();
                                } else error("Thieu gia tri!\n");
                            } else error("Thieu dau gan!\n");
                        } else error("Thieu ten hang!\n");
                    } 

                    if(token==SEMICOLON){
                        token = getToken();
                    } else("Thieu cham phay!\n");
                } else error("Thieu gia tri!\n");
            } else error("Thieu dau gan!\n");
        } else error("Thieu ten hang!\n");
    }

    if(token==VAR){
        token = getToken();
        if(token==IDENT){
            token = getToken();
            if(token==LBRACK){
                token = getToken();
                if(token==NUMBER){
                    token = getToken();
                    if(token==RBRACK){
                        token = getToken();
                    } else error("Thieu dong ngoac!\n");
                } else error("Thieu kich thuoc mang!\n");
            }
            while(token==COMMA){
                token = getToken();
                if(token==IDENT){
                    token = getToken();
                    if(token==LBRACK){
                        token = getToken();
                        if(token==NUMBER){
                            token = getToken();
                            if(token==RBRACK){
                                token = getToken();
                            } else error("THieu dong ngoac!\n");
                        } else error("Thieu kich thuoc mang!\n");
                    }
                } else error("Thieu ten bien!\n");
                
            }
            if(token==SEMICOLON){
                token = getToken();
            } else error("THieu cham phay!\n");
        } else error("Thieu ten bien!\n");
    }

    while(token==PROCEDURE){
        token = getToken();
        if(token==IDENT){
            token = getToken();
            if(token==LPARENT){
                token = getToken();
                if(token==VAR){
                    token = getToken();
                }
                if(token==IDENT){
                    token = getToken();
                    while(token==SEMICOLON){
                        token = getToken();
                        if(token==VAR){
                            token = getToken();
                        }
                        if(token==IDENT){
                            token = getToken();
                        } else error("Thieu ten bien!\n");
                    }
                    if(token==RPARENT){
                        token = getToken();
                    } else error("Thieu dong ngoac!\n");
                } else error("Thieu ten bien!\n");
            }
            if(token==SEMICOLON){
                token = getToken();
                block();
                if(token==SEMICOLON){
                    token = getToken();
                } else error("Thieu cham phay!\n");
            } else error("Thieu cham phay!\n");
        } else error("Thieu ten thu tuc!\n");
    }
    
    if(token==BEGIN){
        token = getToken();
        statement();
        while(token==SEMICOLON){
            token = getToken();
            statement();
        }
        if(token==END){
            token = getToken();
        } else error("Thieu END!1\n"); 
    }
}

void program(){
    // token = getToken();
    // printf("%d\t%d", token, PROGRAM);
    if(token==PROGRAM){
        token = getToken();
        if(token==IDENT){
            token = getToken();
            if(token==SEMICOLON){
                token = getToken();
                block();
                if(token==PERIOD){
                    printf("Thanh cong!\n");
                } else error("Thieu dau cham!\n");
            } else error("Thieu cham phay!\n");
        } else error("Thieu ten chuong trinh!\n");
    } else error("Thieu tu khoa Program!\n");
}

void parser(){
    token = getToken();
    program();
}

TokenType getToken(){
    token = tokenList[indexToken].Token;

    // ident
    if(token==1){
        strcpy(id, tokenList[indexToken].Id);
    }

    // number
    if(token==2){
        num = tokenList[indexToken].Num;
    }

    indexToken++;
    return token;
}