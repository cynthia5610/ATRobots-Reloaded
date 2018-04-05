#ifndef __FILELIB_H__
#define __FILELIB_H__

#include <iostream>

using namespace std;

extern string addfront(string b, int l);
extern string addrear(string b, int l);
extern string lstr(string s1, int l);
extern string rstr(string s1, int l);
extern bool EXIST(string thisfile);
extern bool VALID(string thisfile);
extern string name_form(string name);
extern string exten(string name);
extern string base_name(string name);
extern string attribs(int byte);
extern string path(string fn);
extern string no_path(string fn);
extern long file_length(string fn);

#endif
