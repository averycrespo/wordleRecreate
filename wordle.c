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

/**
 * Get a 'random' word from a list of 5 letter words 
*/
int generateNum( void ) {
    //Generate a number to scan through text file and stop 
    srand(time(NULL));
    int i = rand() % MAX_LINE_NUM;
    return i;
}

/**
 * Validates the placement of a character
*/
bool validatePlacements( char arr[], char string[] ) {
    bool flag = true;
    for( int i = 0; i < strlen( arr ); i++ ) {
        //If correct placement 
        if( arr[i] == string[i]) { 
            printf("\033[0;32m"); //Set the text to the color red
            printf("%c", arr[i]);
            printf("\033[0m"); //Resets 
        } else if ( arr[i] == string[i+1] ) { 
            printf("\033[0;33m"); //Set the text to the color red
            printf("%c", arr[i + 1]);
            printf("\033[0m"); //Resets
            flag = false;
        } else { //Wrong character
            printf("%c", arr[i]);
            flag = false;
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
    FILE *file = fopen("stats.txt", "r");
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0; 
    int e = 0;


    fscanf( file, "%d%d%d%d%d", &a, &b, &c, &d, &e);

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

        file = fopen("stats.txt", "w");
        fprintf( file, "First attempt: %d\nSecond Attempt: %d\nThird Attempt: %d\nFourth Attempt: %d\nFifth Attempt: %d\n", a, b, c, d, e);
    
    
}

/**
 * Main function for wordle 
*/
int main(int argc, char *argv[] ) {
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
    char userGuess[6];
    char ch;
    bool flag = false;

    //Close file 
    fclose( fp );

    //Loop for five guesses until the user gets it correct
    while( counter != 5 ) {
        fscanf(stdin, "%5s", userGuess);
        userGuess[5] = '\0';

        //Convert to all lower
        for(int i = 0; i < strlen(userGuess); i++) {
            ch = userGuess[i];
            userGuess[i] = tolower(ch); 
            i++; 
        } 

    ///////
         printf("The word was: %s\n", string);

        //If user calls to quit 
        if( strcmp(userGuess, "quit") == 0) {
            printf("The word was: %s\n", string);
            return EXIT_SUCCESS;
        }
        flag = validatePlacements( userGuess, string );
        if( flag ) {
            break;
        }
        counter++;
    }
    counter += 1; 
    //Print out message 
    printf( "You won in %d attempts!\n", counter);
    //Save stats 
    saveStats( counter );
    
    //exit correctly
    return EXIT_SUCCESS;
}