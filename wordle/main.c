/*
    a WORDLE clone 
    written by:zeynepsturan (2024)

*/

#include "header.h"

int main(){

    #ifdef _WIN32
        system("CHCP 1254");
    #endif

    setlocale(LC_ALL, ""); /*for turkish characters*/
    srand(time(NULL));
    
    wchar_t target[WORD_LENGTH+1]; /*holds the word*/

    if(prepare_game()==1){
        gameplay(target); /*game runs*/
    }

    return 0;
}
