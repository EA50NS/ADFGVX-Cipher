#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define ADFGVX "ADFGVX"
#define ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"

char random_char(int index){
    return ALPHABET[index];
}

void initialise_polybius_square(){
    srand(time(NULL));
    char square[37];
    int index, i = 0;
    for(i = 0; i < 36; i++){
        index = rand() % 36;
        square[i] = random_char(index);
    }
    square[i] = '\0';
    
    printf("testing random string %s\n", square);
}


int main (void){
   
    printf("Initialising Polyibus Square\n");
    printf(" | A D F G V X\n");
    printf("--------------\n");
    

    return 0;
}
