#ifndef __FILELIB_HH__
#define __FILELIB_HH__

#include <iostream>

using namespace std;

extern char* addfront(char* b, int l);
extern char* addrear(char* b, int l);
extern char* lstr(char* s1, int l);
extern char* rstr(char* s1, int l);
extern bool EXIST(char* thisfile);
extern bool VALID(char* thisfile);
extern char* name_form(char* name);
extern char* exten(char* name);
extern char* base_name(char* name);
extern char* attribs(int byte);
extern char* path(char* fn);
extern char* no_path(char* fn);
extern long file_length(char* fn);

#endif
