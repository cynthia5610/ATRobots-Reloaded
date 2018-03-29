#include <iostream>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include "atrrfunc.hh"
#include "filelib.hh"

/* -- This is a helper file for ATR2.PAS -- */

using namespace std;

/*
FUNCTION HEADERS
*/
char hexnum(unsigned char num);
double valuer(char* i);
long value(char* i);
char* cstrr(double i);
char* cstr(long i);
char* zero_pad(long n, long l);
char* zero_pads(char* s, long l);
char* addfront(char* b, int l);
char* uCase(char* lString);
char* lcase(char* s);
char* space(unsigned char i);
char* repchar(char c, unsigned char i);

/* 
VARIABLES
*/
 long delay_per_sec;
 bool registered, graphix, sound_on;
 char * reg_name;
 unsigned short int reg_num;
 double sint, cost[255];

/* -- function hexnum(num:byte):char -- */
char hexnum(unsigned char num){

    switch(num){

        case 0: return '0'; 
        case 1: return '1'; 
        case 2: return '2'; 
        case 3: return '3'; 
        case 4: return '4'; 
        case 5: return '5'; 
        case 6: return '6'; 
        case 7: return '7'; 
        case 8: return '8'; 
        case 9: return '9'; 
        case 10: return 'A'; 
        case 11: return 'B'; 
        case 12: return 'C'; 
        case 13: return 'D'; 
        case 14: return 'E';  
        case 15: return 'F';
        default: return 'X';
           
    }
}

double valuer(char *i){
    double s = atof(i);
    return s;
}

long value(char *i){
    long s = atoi(i);
    return s;
}

/* -- cstrr(i:real):string; -- */
char* cstrr(double i){
    char* s1;
    char* num_ptr = s1;
    s1 = i;
    return s1;
}

/* -- cstr(i:longint):string -- */
char* cstr(long int i){
    char* s1;

    s1 = i;
    return s1;
}

/* -- zero_pad(n,l:longint):string -- */
char* zero_pad(long n, long l){
    char* s;
    s = cstr(n);
    while(strlen(s) < l){
        s = '0' + s;
    }
    return s;
}

/* -- zero_pads(s:string; l:longint):string; -- */
char* zero_pads(char* s, long l){
    char* s1;
    s1 = s;
    while(strlen(s1) < l){
        s1 = '0' + s1;
    }
    return s1;
}

/* -- addfront(b:string; l:integer):string -- */
char* addfront(char* b, int l){
    while(strlen(b) < l){
        b = ' ' + b;
    }
    return b;
}

/* -- ucase(s:string):string -- */
char* uCase(char* lString){
    char* uString;

    transform(lString.begin(), lString.end(),lString.begin(), ::toupper);
    uString = lString;

    return uString;
}

/* -- lcase(s:string):string -- */
char* lcase(char* s){
    char* uString;

    transform(s.begin(), s.end(), s.begin(), ::tolower);
    uString = s;

    return uString;
}

/* -- space(i:byte):string -- */
char* space(unsigned char i){
    char* s;
    int k;

    if(i > 0){
        for(k = 0; k < i; k++){
            s = s + ' ';
        }
    }
    return s;
}

/* -- repchar(c:char; i:byte):string -- */
char* repchar(char c, unsigned char i){
    char* s;
    int k;

    if(i > 0){
        for(k = 0; k < i; k++){
            s = s + c;
        }
    }
    return s;
}