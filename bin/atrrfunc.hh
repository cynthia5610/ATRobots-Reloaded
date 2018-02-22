#ifndef __ATRRFUNC_HH__
#define __ATRRFUNC_HH__

#include <iostream>
#include <stdlib.h>

using namespace std;

long delay_per_sec;
bool registered, graphix, sound_on;
string reg_name;
unsigned short int reg_num;
double sint, cost[255];

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

#endif