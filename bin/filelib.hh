#ifndef __FILELIB_HH__
#define __FILELIB_HH__

#include <iostream>

using namespace std;

string addfront(string b, int l);
string addrear(string b, int l);
string lstr(string s1, int l);
string rstr(string s1, int l);
bool EXIST(string thisfile);
bool VALID(string thisfile);
string name_form(string name);
string exten(string name);
string base_name(string name);
string attribs(int byte);
string path(string fn);
string no_path(string fn);
long file_length(string fn);

#endif