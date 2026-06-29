#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ADFGVX "ADFGVX"
#define KEY "BISMARCK"
#define KEY_LENGTH strlen(KEY)
char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
char square[6][6];
char substitution[128];

// TODO: order the substitution by alpha order of key, then return full encrypted text.
int compare_chars(const void *a, const void *b){
    return *(const char *)a - *(const char *)b;
}

void swap_column(char* key, int col1, int col2, int rows, char** message){
    char temp = key[col1];
    key[col1] = key[col2];
    key[col2] = temp;

    for (int r = 0; r < rows; r++) {
        temp = message[r][col1];
        message[r][col1] = message[r][col2];
        message[r][col2] = temp;
    }
}

char** final_step(char **msg_substitution){
    char key[] = KEY;
    int rows = strlen(substitution) / KEY_LENGTH;
    if((strlen(substitution) % KEY_LENGTH) != 0){
        rows++;
    }
        
    for (int i = 0; i < KEY_LENGTH - 1; i++){
        for (int j = i+1; j < KEY_LENGTH; j++){
            if (key[i] > key[j]){
                swap_column(key, i, j, rows, msg_substitution);
            }
        }
    }
    return msg_substitution;
}


char** columnar_transposition(char *substitution){ 
    int len = strlen(substitution);
    int rows = strlen(substitution) / KEY_LENGTH; 
    if ((strlen(substitution) % KEY_LENGTH) != 0){
        rows++;
    }

    char **transposition = malloc(rows * sizeof(char*));
    for (int i = 0; i < rows; i++){
        transposition[i] = malloc(KEY_LENGTH * sizeof(char));
    }
    
    int k = 0;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < KEY_LENGTH; j++){
            transposition[i][j] = (k < len) ? substitution[k] : ' '; // explicit pad
            k++;
        }
    }
    
    return transposition;
}


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
   
    printf("Initialising Polybius Square\n");
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
    printf("substituted message: %s\n\n", substitution);
    
    char** msg_substitution = columnar_transposition(substitution);

    for (int i = 0; i < KEY_LENGTH; i++){
       printf("%c ", KEY[i]); 
    }
    printf("\n");
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < KEY_LENGTH; j++){
            printf("%c ", msg_substitution[i][j]);
        }
        printf("\n");
    }

    char** encrypted_msg = final_step(msg_substitution);

    printf("\n");
    printf("New substition: \n");
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < KEY_LENGTH; j++){
            printf("%c ", encrypted_msg[i][j]);
        }
        printf("\n");
    }

    printf("\n");
    printf("Final encrypted message:\n");
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < KEY_LENGTH; j++){
            if ( encrypted_msg[i][j] == ' '){
                continue;
            }
            else{
                printf("%c", encrypted_msg[i][j]);
            }
        }
    }

    return 0;
}
