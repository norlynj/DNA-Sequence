#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


//FUNCTION PROTOTYPES
void getFileAndSequence(char [] , char [] );
int seqCounter(FILE *fptr, char [] );


//MAIN FUNCTION
int main()
{

    FILE * fptr;
    char filename[50], sequence[50];
    int direct, reverse, total;

    //get filename and sequence motif to be searched
    getFileAndSequence(filename, sequence);

     //open file in read mode
    fptr = fopen(filename, "r");

    if(fptr == NULL){
        printf("Can't open file.");
        return 0;
    }


    int i, j;
    int lenSeq = strlen(sequence);
    static char findRev[50];

    //convert uppercase to lowercase
    for(int x = 0; x < lenSeq; x++){
        if(sequence[x] >= 'A' && sequence[x] <= 'Z')
            sequence[x] = sequence[x] + 32;
    }



    //reverse complement of the string
    j = lenSeq - 1;
    for(i = 0; i < lenSeq; i++){
        if(sequence[i] == 'a'){
            findRev[j] = 't';
        }
        if(sequence[i] == 't'){
            findRev[j] = 'a';
        }
        if(sequence[i] == 'g'){
            findRev[j] = 'c';
        }
        if(sequence[i] == 'c'){
            findRev[j] = 'g';
        }

        j--;

    }

    direct = seqCounter(fptr, sequence);
    rewind(fptr); //resetting pointer to the start of file so reverse could work
    reverse = seqCounter(fptr, findRev);
    total = direct + reverse;

    //converting char sequence back to uppercase again for printing
    for(int x = 0; x < lenSeq; x++){
        if(sequence[x] >= 'a' && sequence[x] <= 'z')
            sequence[x] = sequence[x] - 32;
    }

    printf("%s sequence motif found: %d\n\n\n",sequence, total);

    fclose(fptr);

    return 0;
}


//FUNCTION DEFINITIONS
void getFileAndSequence(char inputFN[], char motif[]){
/*
function to get the file name and sequence
*/

    printf("Please enter a filename: ");
    gets(inputFN);

    //loop for user to reenter if invalid sequence is entered
    while(1) {
        const char *validLetters = "AGTCagtc*";  //valid letters
        printf("Please provide a sequence motif to be searched: ");
        gets(motif);

        int valid = 1;
        //checks if each input is an element of valid letters
        for(int i = 0; i < strlen(motif); i++) {
            if(strchr(validLetters, motif[i]) == NULL){
                printf("\nSorry, you entered an invalid sequence. Please try again.\n");
                valid = 0;
                break;
                }
        }
        if(valid) {
            break;
        }
    }
}

int seqCounter(FILE *fptr, char seq[]){

    //searching for substring in a string
    char str[1500];
    int i, found = 0;
    char *j;

    while((fgets(str, 1500, fptr)) != NULL){
        i = 0;
        while((j = (strstr(str + i, seq)))){
        //strstr function finds within the string pointed to by find for the string pointed to by pattern
            i = (j - str) + 1;
            found++;
        }

    }
    return found;
}
