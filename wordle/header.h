#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>

/*defining all color codes*/
#define COL_GREEN "\033[32m"
#define COL_YELLOW "\033[33m"
#define COL_GRAY "\033[90m"
#define COL_WHITE "\033[97m"
#define COL_RED "\033[38;5;9m"

#define NUMBER_OF_TOTAL_WORDS_EN 3984
#define NUMBER_OF_TOTAL_WORDS_TR 3210
#define MAX_WORD_LENGTH 100
#define WORD_LENGTH 5
#define MAX_GUESS_COUNT 6

int lang_choice;
wchar_t messages[14][100];

wchar_t upper_letters(wchar_t letter){

    if(letter >= 'a' && letter <= 'z' && letter!=L'i'){
        return letter-32;
    }

    else{
        switch(letter){

            case L'ğ':  return L'Ğ';    break;
            case L'ş':  return L'Ş';    break;
            case L'i':
                if(lang_choice==2)  return L'İ';
                else  return L'I';
                break;
            case L'ı':  return L'I';    break;
            case L'ü':  return L'Ü';    break;
            case L'ö':  return L'Ö';    break;
            case L'ç':  return L'Ç';    break;
            default:  return letter;    break;
        }
    }

}

wchar_t lower_letters(wchar_t letter){

    if(letter >= 'A' && letter <= 'Z' && letter!=L'I'){
        return letter+32;
    }

    else{
        switch(letter){

            case L'Ğ':  return L'ğ';    break;
            case L'Ş':  return L'ş';    break;
            case L'İ':  return L'i';    break;
                
            case L'I':
                if(lang_choice==2)  return L'ı';
                else return L'i';
                break;
            case L'Ü':  return L'ü';    break;
            case L'Ö':  return L'ö';    break;
            case L'Ç':  return L'ç';    break;
            default:  return letter;    break;
        }
    }

}

int check_turkish_char(wchar_t letter){

    wchar_t tr_chars[59] = L"AaBbCcÇçDdEeFfGgĞğHhIıİiJjKkLlMmNnOoÖöPpRrSsŞşTtUuÜüVvYyZz";
    int i;

    for(i=0; i<59; i++){

        if(letter==tr_chars[i]){
            return 1;
        }
    }
    
    return 0;
}

int check_english_char(wchar_t letter){

    wchar_t en_chars[53] = L"AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz";

    int i;

    for(i=0; i<53; i++){

        if(letter==en_chars[i]){
            return 1;
        }
    }
    
    return 0;
}

void select_word(wchar_t target[]){

    FILE *ptr;
    int number_of_total_words;

    if(lang_choice==1){
        ptr = _wfopen(L"word_database_files\\word_database_en.txt", L"r, ccs=UTF-8");
        number_of_total_words=NUMBER_OF_TOTAL_WORDS_EN;
    }
    
    else if(lang_choice==2){
        ptr = _wfopen(L"word_database_files\\word_database_tr.txt", L"r, ccs=UTF-8");
        number_of_total_words=NUMBER_OF_TOTAL_WORDS_TR;
    }

    if(ptr == NULL){ /*if the file cannot be opened*/
        printf("%s", COL_WHITE);
        wprintf(L"%ls\n", messages[13]);
        return;
    }
    
    int random;
    int i;
    
    /*choosing a random word*/
    random=rand() % number_of_total_words;

    /*going to that word and storing it*/
    for(i=0;i<random;i++){
        fwscanf(ptr,L"%ls", target);
    }

    fclose(ptr);
}

int prepare_game(){

    FILE *messageptr;
    int i;
    char c;

    /*language options*/
    wprintf(L"Language/Dil\n");
    wprintf(L"1- English\n");
    wprintf(L"2- Türkçe\n");
    wprintf(L"-> ");
    scanf("%d", &lang_choice);

    if(lang_choice==1){
        messageptr=_wfopen(L"lang_files\\lang_en.txt", L"r, ccs=UTF-8"); /*opens the english file*/
        
        if(messageptr == NULL){ /*if the file cannot be found*/
            printf("%s", COL_RED);
            wprintf(L"Language file is missing.\n");
            printf("%s",COL_WHITE);

            while((c=getchar())!='\n'){}
            getchar();
            return 0;
        }
    }

    else if(lang_choice==2){

        messageptr=_wfopen(L"lang_files\\lang_tr.txt", L"r, ccs=UTF-8"); /*opens the turkish file*/
        
        if(messageptr == NULL){ /*if the file cannot be found*/
            printf("%s", COL_RED);
            wprintf(L"Dil dosyası kayıp.\n");
            printf("%s",COL_WHITE);

            while((c=getchar())!='\n'){}
            getchar();
            return 0;
        }
    }

    else{
        printf("%s", COL_RED);
        wprintf(L"Invalid choice/Geçersiz seçim\n");
        printf("%s",COL_WHITE);
        
        while((c=getchar())!='\n'){}
        getchar();
        return 0;
    }

    for(i=0; i<14; i++){ /*stores the game texts according to chosen language*/

        if(fgetws(messages[i], sizeof(messages[i]) / sizeof(wchar_t), messageptr) != NULL){
            /* Remove newline character if present*/
            size_t len = wcslen(messages[i]);

            if(len>0 && messages[i][len-1] == '\n'){
                messages[i][len-1] = '\0';
            }
        }
    }

    fclose(messageptr); /*closes the language file*/
    return 1;
}

void print_info(){

    printf("\n\n\t\t");
    printf("WORDLE");
    printf("\n\n\n");

    printf("%s",COL_WHITE);
    printf("%ls\n",messages[0]);

    printf("%s%ls", COL_GREEN, messages[1]);
    printf("%s%ls\n", COL_WHITE, messages[2]);
    
    printf("%s%ls", COL_YELLOW, messages[3]);
    printf("%s%ls\n", COL_WHITE, messages[4]);

    printf("%s%ls", COL_GRAY, messages[5]);
    printf("%s%ls\n", COL_WHITE, messages[6]);

    printf("-------------------------------------------------------------------------\n");

}

void print_guesses(wchar_t all_guesses[][WORD_LENGTH][2], int shots){

    int i,j;
    printf("\n");

    for(i = 0; i<=shots; i++){
        
        printf("\t");
        for(j = 0; j<WORD_LENGTH; j++){

            switch(all_guesses[i][j][1]){

                case '1':
                printf("%s", COL_GREEN);
                wprintf(L"%lc", upper_letters(all_guesses[i][j][0]));
                break;

                case '2':
                printf("%s", COL_YELLOW);
                wprintf(L"%lc", upper_letters(all_guesses[i][j][0]));
                break;

                case '3':
                printf("%s", COL_GRAY);
                wprintf(L"%lc", upper_letters(all_guesses[i][j][0]));
                break;

            }
            printf("%s", COL_WHITE);
        }

        printf("\n");
    }
    printf("\n");

}

void gameplay(wchar_t target[]){

    wchar_t guess[MAX_WORD_LENGTH]; /*holds the words player guessed*/
    wchar_t all_guesses[MAX_GUESS_COUNT][WORD_LENGTH][2]; /*[][][0]->Letter [][][1]->Color*/
    char choice;

    int i, j, flag1, flag2, flag3;
    int shots;
    
    /*-----------GAME START--------------*/
    do{
        select_word(target);
        print_info();
        
        for(shots = 0; shots<MAX_GUESS_COUNT; shots++){ /*all guess shots*/

            /*guess check*/
            do{ /*takes input until player enters a valid guess*/
                flag2 = 1;
                printf("%s%ls ", COL_WHITE, messages[7]);
                wscanf(L"%ls",&guess);

                /* Check if the length of the guess is correct */
                if(wcslen(guess) != WORD_LENGTH){
                    printf("%s%ls\n", COL_WHITE, messages[8]);
                    flag2 = 0;
                }

                else if(lang_choice==1){

                    for(i=0; i<WORD_LENGTH; i++){

                        if(check_english_char(guess[i])==0){
                            printf("%s%ls\n", COL_WHITE, messages[8]);
                            flag2 = 0;
                            break;
                        }
                    }
                }

                else if(lang_choice==2){

                    for(i=0; i<WORD_LENGTH; i++){

                        if(check_turkish_char(guess[i])==0){
                            printf("%s%ls\n", COL_WHITE, messages[8]);
                            flag2 = 0;
                            break;
                        }
                    }

                }

            }while(!flag2);
            
            /*when the guess is valid*/

            for(i=0; i<WORD_LENGTH; i++){
                guess[i]=lower_letters(guess[i]);
            }

            for(i=0; i<WORD_LENGTH; i++){ /*stores the guessed word with right colors*/

                all_guesses[shots][i][0] = guess[i]; /*default color: gray*/
                all_guesses[shots][i][1] = '3'; /*3 represents gray*/

                if(guess[i] == target[i]){
                    all_guesses[shots][i][1] = '1'; /*1 represents green*/
                }
            }

            for(i=0; i<WORD_LENGTH; i++){

                for(j=0; j<WORD_LENGTH; j++){

                    if(target[j]==guess[i] && all_guesses[shots][i][1]=='3' && all_guesses[shots][j][1] != '1'){
                        all_guesses[shots][i][1] = '2'; /*2 represents yellow*/
                    }

                }
                
            }

            /*printing all the guesses*/
            print_guesses(all_guesses, shots);
            
            /*end check*/
            flag1 = 1;

            for(i=0; i<WORD_LENGTH; i++){
                if(target[i] != guess[i]){
                    flag1 = 0;
                }
            }

            if(flag1){
                printf("%s", COL_WHITE);
                wprintf(L"%ls\n", messages[9]);
                break;
            }
        }

        if(!flag1){
            printf("%s%ls", COL_WHITE, messages[10]);

            printf("%s", COL_GREEN);
            for(i=0; i<WORD_LENGTH; i++){
                wprintf(L"%lc", upper_letters(target[i]));
            
            }
            printf("\n");
        }

        printf("%s%ls ", COL_WHITE, messages[11]);
        scanf(" %c",&choice);

        switch (choice){
            case 'y':
            case 'Y':
            flag3=1;
            break;
        
            case 'n':
            case 'N':
            flag3=0;
            break;

            default:
            printf("%s%ls\n", COL_WHITE, messages[12]);
            break;
        }

    }while(flag3);

}
