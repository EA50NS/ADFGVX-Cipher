#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define ADFGVX "ADFGVX"
char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

void random_alpha(){
    srand(time(NULL));
    int random_index = 0;
    char temp;
    int length = strlen(alphabet);

    for (int i = 0; i < length; i++){
        random_index = rand() % length; 

        temp = alphabet[random_index];
        alphabet[random_index] = alphabet[i];
        alphabet[i] = temp;
    }
}

void initialise_polybius_square(){
    random_alpha();
    printf("rand alpha test: %s \n", alphabet);
    char square[6][6];

    int length = sqrt(strlen(alphabet)); // Is this REALLY necessary? Why not just use '6'?
   
    int k = 0;
    for(int i = 0; i < length; i++){
        for (int j = 0; j < length; j++){
            square[i][j] = alphabet[k];
            k++;
        }
    }

    printf("printing square: \n");
    for (int i = 0; i < length; i++){
        for (int j = 0; j < length; j++){
            printf("%c ", square[i][j]);
        }
        printf("\n");
    }


}


int main (void){
   
   // printf("Initialising Polyibus Square\n");
   // printf(" | A D F G V X\n");
   // printf("--------------\n");
   initialise_polybius_square();
    



    return 0;
}
