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
string hexb(unsigned char num);
string hex(unsigned short num);
double valuer(string i);
long value(string i);
string cstrr(double i);
string cstr(long i);
string zero_pad(long n, long l);
string zero_pads(string s, long l);
string addfront(string b, int l);
string uCase(string lString);
string lcase(string s);
string space(unsigned char i);
string repchar(char c, unsigned char i);

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

/*
string hexb(unsigned char num){
    return (hexnum(num << 4) + hexnum(num & 15));
}
*/

/*
string hex(unsigned short num){
    return(hexb(num << 8) + hexb(num & 255));
}
*/

double valuer(string i){
    double s;
    s = stod(i);
    return s;
}

/*
long value(string i){
    long s;
    s = atol(i);
    return s;
}
*/

/* -- cstrr(i:real):string; -- */
string cstrr(double i){
    string s1;
    s1 = i;
    return s1;
}

/* -- cstr(i:longint):string -- */
string cstr(long int i){
    string s1;
    s1 = i;
    return s1;
}

/* -- zero_pad(n,l:longint):string -- */
string zero_pad(long n, long l){
    string s;
    s = cstr(n);
    while(s.length() < l){
        s = '0' + s;
    }
    return s;
}

/* -- zero_pads(s:string; l:longint):string; -- */
string zero_pads(string s, long l){
    string s1;
    s1 = s;
    while(s1.length() < l){
        s1 = '0' + s1;
    }
    return s1;
}

/* -- addfront(b:string; l:integer):string -- */
string addfront(string b, int l){
    while(b.length() < l){
        b = ' ' + b;
    }
    return b;
}

/* -- ucase(s:string):string -- */
string uCase(string lString){
    string uString;

    transform(lString.begin(), lString.end(),lString.begin(), ::toupper);
    uString = lString;

    return uString;
}

/* -- lcase(s:string):string -- */
string lcase(string s){
    string uString;

    transform(s.begin(), s.end(), s.begin(), ::tolower);
    uString = s;

    return uString;
}

/* -- space(i:byte):string -- */
string space(unsigned char i){
    string s;
    int k;

    if(i > 0){
        for(k = 0; k < i; k++){
            s = s + ' ';
        }
    }
    return s;
}

/* -- repchar(c:char; i:byte):string -- */
string repchar(char c, unsigned char i){
    string s;
    int k;

    if(i > 0){
        for(k = 0; k < i; k++){
            s = s + c;
        }
    }
    return s;
}

/*
string btrim(string s1){
    return ltrim(rtrim(s1));
}

string ltrim(string s1){
    int i;
    while( (s1.length() > 0) && ))
}

string rtrim(string s1){
    return;
}
*/