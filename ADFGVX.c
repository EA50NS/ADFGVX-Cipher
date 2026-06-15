#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ADFGVX "ADFGVX"
#define KEY "BISMARCK"
char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
char square[6][6];
char substitution[128];

void square_lookup(char *message){
    int a = 0;
    for (int i = 0; i < strlen(message); i++){
        for (int j = 0; j < 6; j++){
            for (int k = 0; k < 6; k++){
                if (square[j][k] == message[i]){
                    substitution[a] = ADFGVX[j];
                    substitution[a+1] = ADFGVX[k];
                    a += 2;
                }
            }
        }
    }
}

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

    int length = 6;
   
    int k = 0;
    for(int i = 0; i < length; i++){
        for (int j = 0; j < length; j++){
            square[i][j] = alphabet[k];
            k++;
        }
    }
   
    printf("Initialising Polyibus Square\n");
    printf(" | A D F G V X\n");
    printf("--------------\n");
    for (int i = 0; i < length; i++){
        printf("%c| ", ADFGVX[i]);
        for (int j = 0; j < length; j++){
            printf("%c ", square[i][j]);
        }
        printf("\n");
    }
}


int main (void){

    char message[] = "ATTACKAT1200AM";
    initialise_polybius_square();
    square_lookup(message); 

    printf("plain text message: %s\n", message);
    printf("substitued message: %s\n", substitution);
    
    return 0;
}
