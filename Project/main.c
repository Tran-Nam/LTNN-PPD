#include "scanner.h"
// #include "parser.h"

TokenStruct tokenList[5000];
int indexToken;
int token;

void main(int argc, char **argv)
{
    FILE* f;
    f = fopen(argv[1], "r");

    scanner(f);

    // token = getToken();
    indexToken = 0;
    parser();
    // printf("%s", type(tokenList));
    // for(int j=0; j<indexToken; j++){
    //     printf("%d\n", tokenList[j].Token);
    // }
    // printf("%d\n", indexToken);
    // tmp();

    
}
