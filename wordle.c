/**
 * Simple version of wordle given a command line UI 
*/

#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <stdbool.h>
#include <time.h>
#include <ctype.h>
#define MAX_LINE_NUM 5758
#define NUMBER_OF_CHARS_WITH_NULL_TERMIN 6 

void printBaner( void ) {
    printf("\033[0;31m");
    printf("WWW          W          WWW      OOOOOOO       RRRRRRRRRR     DDDDDDDD        LLL            EEEEEEEEEEE  \n");
    printf(" WWW       WWWWW       WWW     OOO     OOO     RRR     RRR    DDD     DDD     LLL            EEE          \n");
    printf("  WWW     WWW WWW     WWW     OOO       OOO    RRR     RRR    DDD      DDD    LLL            EEE          \n");
    printf("    WW  WWW     WWW  WW      OOO         OOO   RRRRRRRRRR     DDD       DDD   LLL            EEEEEEEEEEE  \n");
    printf("     WWWWW       WWWWW        OOO       OOO    RRR   RRR      DDD      DDD    LLL            EEE          \n");
    printf("      WWW         WWW          OOO     OOO     RRRR    RRR    DDD     DDD     LLL            EEE          \n");
    printf("       WW         WW             OOOOOOO       RRR      RRR   DDDDDDDD        LLLLLLLLLLL    EEEEEEEEEEE  \n");
    printf("\033[0m"); 
    printf("Start Guessing 5 Lettered Words Below!\n");
}

/**
 * Dynamically allocate a list of avaliable words from input.txt
 * @return 2D array of entire list of strings from input.txt
*/
char** createList( void ) {
    FILE *fp = fopen("input.txt", "r");

    //Word to be guessed 
    char string[6];

    //Allocate for list
    char **list = malloc( MAX_LINE_NUM  * sizeof( char * ) );
    //allocate each string 
    for(int i = 0; i < MAX_LINE_NUM; i++) {
        fscanf( fp, "%s", string );
        // list[i] = malloc( )
        list[i] = malloc(( NUMBER_OF_CHARS_WITH_NULL_TERMIN ) * sizeof(char));
        strcpy( list[i], string);
    }
    //Close file 
    fclose( fp );
    //return list 
    return list;
}

/**
 * Frees allocated list 
 * @param list entire list of valid 5 letter words from input.txt
*/
void freeList( char **list ) {
    //Loop through all allocated strings
    for(int i = 0; i < MAX_LINE_NUM; i++) {
      free( list[i] );
    }
    //Free list 
    free(list);
}

/**
 * Checks if word provided from userInput is a word from the existing list
 * @param list a list of valid words from the input file
 * @param userInput is the character array of what the user entered
 * @return true if word is valid
 * @return false if word is invalid
*/
bool isValidWord( char **list, char userInput[] ) {
    //Loop through all words 
    //Could be optimized if word list was sorted 
    for( int i = 0; i < MAX_LINE_NUM; i++) {
        if( strcmp(list[i], userInput) == 0) {
            return true;
        }
    }
    return false; 
}

/**
 * Get a 'random' word from a list of 5 letter words 
 * @return i the integer generated from the list of 5758 number of words
*/
int generateNum( void ) {
    //Generate a number to scan through text file and stop 
    srand(time(NULL));
    int i = rand() % MAX_LINE_NUM;
    return i;
}

/**
 * Validates the placement of a character
 * @param arr user's guess in char array format
 * @param string the word to solve 
 * @return true or false if the placement is in the correct order
*/
bool validatePlacements( char arr[], char string[] ) {
    bool flag = true;
    for( int i = 0; i < 5; i++ ) {
        //If correct placement 
        if( arr[i] == string[i]) { 
            printf("\033[0;32m"); //Set the text to the color green
            printf("%c", arr[i]);
            printf("\033[0m"); //Resets 
        } else { //Wrong character report as grey 
            //Incorrect guess 
            flag = false;
            //Boolean to check if any correct letter was found in the incorrect placement 
            bool printRegular = true;
            for(int j = 0; j < 4; j++) {
                if( arr[i] == string[j]) { 
                    printf("\033[0;33m"); //Set the text to the color green
                    printf("%c", arr[i]);
                    printf("\033[0m"); //Resets
                    printRegular = false; 
                } 
            }
            if( printRegular == true ) {
                printf("%c", arr[i]);
                flag = false;
            }
        }
  }
  printf("\n");
  return flag; 
}

/**
 * Records stats by saving and printing output to a file named "stats.txt"
 * @param counter the number of attempts it took to solve the word 
*/
void saveStats( int counter ) {
    //Open file 
    FILE *file = fopen("stats.txt", "r");
    int a = 0; int b = 0; int c = 0; int d = 0; int e = 0;
    //Scan through decimal values while ignoring the strings 
    fscanf( file, "%*s%*s %d%*s%*s %d%*s%*s %d%*s%*s %d%*s%*s %d%*s%*s",
        &a, &b, &c, &d, &e);

    //Counter is updated to correct variable placement 
    if( 1 == counter ) {
        a += 1;
    } else if( 2 == counter ) {
        b += 1;
    } else if( 3 == counter ) {
        c += 1;
    } else if( 4 == counter ) {
        d += 1;
    } else if( 5 == counter ) {
        e += 1;
    }
    //Open file to write to 
    file = fopen("stats.txt", "w");
    //Print to file
    fprintf( file, "First attempt: %d\nSecond Attempt: %d\nThird Attempt: %d\nFourth Attempt: %d\nFifth Attempt: %d\n", a, b, c, d, e);
    //Close file 
    fclose( file ) ;
}

/**
 * Main function for wordle 
*/
int main(int argc, char *argv[] ) {

    //Printing banner
    printBaner();

    //Create list
    char **list = createList();

    //Start counter 
    int counter = 0;

    //Open file
    FILE *fp = fopen("input.txt", "r");

    //Generate num
    int i = generateNum(); 

    //Serves as index
    int search = 0;

    //Word to be guessed 
    char string[6];

    //Search through
    while( search != i ) {
        fscanf( fp, "%s", string );
        search++;
    }
    
    //String to store user input from command line 
    char userGuess[100];
    char ch;
    bool flag = false;

    //Close file 
    fclose( fp );

    //Loop for five guesses until the user gets it correct
    while( counter != 5 ) {
        fscanf(stdin, "%s", userGuess);
        userGuess[6] = '\0';
        //Convert to all lower
        for(int i = 0; i < 5; i++) {
            ch = userGuess[i];
            userGuess[i] = tolower(ch); 
            i++; 
        } 
        if( strcmp( userGuess, "quit" ) == 0 ) {  //If user calls to quit 
            printf("The word was: %s\n", string);
            return EXIT_SUCCESS;
        } else if( strlen( userGuess ) != 5 ) { //User entered word that is not a five lettered word 
            printf("Invalid guess\n");
            counter--;
        } else if( isValidWord( list, userGuess) == false ) { //User entered word not in list 
            printf("Not in word list\n");
            counter--;
        } else {
            flag = validatePlacements( userGuess, string );
            if( flag ) {
               //Increment counter to adjust for rounds
                counter += 1; 
                //Print out message 
                printf( "You won in %d attempts!\n", counter);
                //Save stats 
                saveStats( counter ); 
                printf("Stats saved to --> stats.txt\n");
                //Free list 
                freeList( list );
                return EXIT_SUCCESS;
            }
        }
        counter++;
    } //end of loop

    //If reached
    printf("You lost, the word was: %s\n", string); 

    //Free list 
    freeList( list );
    
    //exit correctly
    return EXIT_SUCCESS;
}