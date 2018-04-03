#ifndef __ATRRFUNC_HH__
#define __ATRRFUNC_HH__

#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <math.h>

using namespace std;

extern long delay_per_sec;
extern bool registered, graphix, sound_on;
extern string reg_name;
extern unsigned short int reg_num;
extern double sint, cost[255];

extern char hexnum(unsigned char num);
extern char* hexb(unsigned char num);
extern char* hex(unsigned short num);
extern double valuer(char* i);
extern long value(char* i);
extern char* cstrr(double i);
extern char* cstr(long int i);
extern char* zero_pad(long n, long l);
extern char* zero_pads(char* s, long l);
extern char* addfront(char* b, int l);
extern char* uCase(char* lString);
extern char* lcase(char* s);
extern char* space(unsigned char i);
extern char* repchar(char c, unsigned char i);
double distance(double x1, double y1, double x2, double y2);

#endif
