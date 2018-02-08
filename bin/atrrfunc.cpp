#include <iostream>
#include <stdlib.h>
#include <string>


/* -- This is a helper file for ATR2.PAS -- */

using namespace std;

/* -- function hexnum -- */
char hexNumber(int number){
    char hexNum;

    hexNum = number;

    switch(hexNum){

        case 0: hexNum = '0';
        case 1: hexNum = '1';
        case 2: hexNum = '2';
        case 3: hexNum = '3';
        case 4: hexNum = '4';
        case 5: hexNum = '5';
        case 6: hexNum = '6';
        case 7: hexNum = '7';
        case 8: hexNum = '8';
        case 9: hexNum = '9';
        case 10: hexNum = 'A';
        case 11: hexNum = 'B';
        case 12: hexNum = 'C';
        case 13: hexNum = 'D';
        case 14: hexNum = 'E';
        case 15: hexNum = 'F';
        default: hexNum = 'X';
           
    }
    return(hexNum);
}


