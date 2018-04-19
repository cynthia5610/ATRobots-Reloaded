#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <ctype.h>
#include <algorithm>
#include <math.h>
#include <cmath>
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
char* lCase(char* s);
char* space(unsigned char i);
char* repchar(char c, unsigned char i);
double getDistance(double x1, double y1, double x2, double y2);
int robot_color(int n);
void textcolor(int num);
bool in(int value, int low, int high);

/* 
VARIABLES
*/
 long delay_per_sec;
 bool registered, graphix, sound_on;
 string reg_name;
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
    char* end;
    double result;

    result = strtod(i, &end);

    return result;
}

long value(char *i){
    char* end;
    long result;

    result = strtol(i, &end, 10);

    return result;
}

/* -- cstrr(i:real):string; -- */
char* cstrr(double i){

    char* result;
    sprintf(result, "%f", i);

    return result;

}

/* -- cstr(i:longint):string -- */
char* cstr(long int i){
    
    char* result;
    sprintf(result, "%ld", i);
    
    return result;
}

/* -- zero_pad(n,l:longint):string -- */
char* zero_pad(long n, long l){
    char* s;
    s = cstr(n);
    while(strlen(s) < l){
        snprintf(s, strlen(s), "0");    //s = '0' + s;
    }
    return s;
}

/* -- zero_pads(s:string; l:longint):string; -- */
char* zero_pads(char* s, long l){
    char* s1;
    s1 = s;
    while(strlen(s1) < l){
       snprintf(s1, strlen(s1), "0"); //s1 = '0' + s1;
    }
    return s1;
}

/* -- addfront(b:string; l:integer):string -- */
char* addfront(char* b, int l){
    while(strlen(b) < l){
        snprintf(b, strlen(b), " "); //b = ' ' + b;
    }
    return b;
}

/* -- ucase(s:string):string -- */
char* uCase(char* lString){

    for(int i=0;i<strlen(lString);i++) {
            lString[i] = toupper(lString[i]);
        }
    return lString;
}

/* -- lcase(s:string):string -- */
char* lCase(char* uString){

    for(int i=0;i<strlen(uString);i++) {
            uString[i] = tolower(uString[i]);
        }
    return uString;
}

/* -- space(i:byte):string -- */
char* space(unsigned char i){
    char* s;
    int k;

    if(i > 0){
        for(k = 0; k < i; k++){
            snprintf(s, strlen(s), " "); //s = s + ' ';
        }
    }
    return s;
}

/* -- repchar(c:char; i:byte):string --
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
*/

double getDistance(double x1, double y1, double x2, double y2)
{
    return abs(sqrt(pow(y1-y2,2)+pow(x1-x2,2)));
}

int robot_color(int n)
{
    int k;
    k = 7;
    switch(n % 14)
    {
        case 0: k = 10; break;
        case 1: k = 12; break;
        case 2: k = 9; break;
        case 3: k = 11; break;
        case 4: k = 13; break;
        case 5: k = 14; break;
        case 6: k = 7; break;
        case 7: k = 6; break;
        case 8: k = 2; break;
        case 9: k = 4; break;
        case 10: k = 1; break;
        case 11: k = 3; break;
        case 12: k = 5; break;
        case 13: k = 15; break;
        default: k = 15; break;
    }
    return k;
}

void textcolor(int num)
{
    string s = "\033[";
    switch(num)
    {
        case 0: s = s + "0;30"; break; //black
        case 1: s = s + "0;34"; break; //blue
        case 2: s = s + "0;32"; break; //green
        case 3: s = s + "0;36"; break; //cyan
        case 4: s = s + "0;31"; break; //red
        case 5: s = s + "0;35"; break; //magenta
        case 6: s = s + "38;5;94"; break; //brown
        case 7: s = s + "37"; break; //white
        case 8: s = s + "38;5;246"; break; //grey
        case 9: s = s + "34;1"; break; //light blue
        case 10: s = s + "32;1"; break; //light green
        case 11: s = s + "36;1"; break; //light cyan
        case 12: s = s + "31;1"; break; //light red
        case 13: s = s + "35;1"; break; //light magenta
        case 14: s = s + "33"; break; //yellow
        case 15: s = s + "37;1"; break; //bright white
        case 16: s = s + "0"; break; //reset
    }
    s = s + "m";
    cout << s;
    return;
}

bool in(int value, int low, int high){ 
     
    bool result = false; 
     
    for(int i = low; i < high; i++){ 
        if(value == i){ 
            result = true; 
        } 
    } 
    return(result);
}
