#ifndef __ATRRFUNC_HH__
#define __ATRRFUNC_HH__

#include <iostream>
#include <stdlib.h>
#include <algorithm>

using namespace std;

extern long delay_per_sec;
extern bool registered, graphix, sound_on;
extern string reg_name;
extern unsigned short int reg_num;
extern double sint, cost[255];

extern char hexnum(unsigned char num);
extern string hexb(unsigned char num);
extern string hex(unsigned short num);
extern double valuer(string i);
extern long value(string i);
extern string cstrr(double i);
extern string cstr(long int i);
extern string zero_pad(long n, long l);
extern string zero_pads(string s, long l);
extern string addfront(string b, int l);
extern string uCase(string lString);
extern string lcase(string s);
extern string space(unsigned char i);
extern string repchar(char c, unsigned char i);

#endif
