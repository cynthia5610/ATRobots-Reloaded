#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

#include "filelib.hh"
#include "atrrfunc.hh"


//the attribs and file_length functions still need to be converted to c++;
/* -- This unit contains functions useful for dealing with filenames. -- */

using namespace std;

//char* addfront(char* b, int l);
char* addrear(char* b, int l);
char* lstr(char *s1, int l);
char* rstr(char *s1, int l);
bool EXIST(char* thisfile);
//bool VALID(char* thisfile);
char* name_form(char* name);
char* exten(char* name);
char* base_name(char* name);
//char* attribs(int byte);
char* path(char* fn);
//char* no_path(char* fn);
long file_length(char* fn);


/**char* addfront(char* b, int l)
{
    while(strlen(b) < l)
    {
        b[strlen(b)] = ' ';
    }
    return b;
}**/

char* addrear(char* b, int l)
{
    while(strlen(b) < l)
    {
        b[strlen(b)] = ' ';
    }
    b[strlen(b)+1] = '\0';
    return b;
}

char* lstr(char *s1, int l)
{
    if(strlen(s1) <= l)
    {
        return s1;
    }
    else
    {
        s1[strlen(s1) - l] = '\0';
        return s1;
    }
}

char* rstr(char *s1, int l)
{
    if(strlen(s1) <= l)
    {
        return s1;
    }
    else
    {
        s1[strlen(s1) - l] = '\0';
        return s1;
    }
}

bool EXIST(char* thisfile)
{
    ifstream inFile;
    inFile.open(thisfile);
    if(!inFile.is_open())
    {
        return false;
    }
    else
    {
        inFile.close();
        return true;
    }
}

/**bool VALID(string thisfile)
{
    file afile;
    bool check;

    if (!EXIST(thisfile)){

    }
    return false;
}**/

char* name_form(char* name){
    int i, j, k, l;
    char *s1; 
    char *s2;
    k = 0;
    if (name[strlen(name)] == '.' /* || name[strlen(name)] == '..'*/)
    {
        return addrear(name,12);
    }
    while(k <= strlen(name) && name[k] != '.')
    {
        //s1 = s1 + name[k];
        strncat(s1, name, k);
        k++;
    }
    if (k < strlen(name))
    {
        k++;
        while (k < strlen(name) && name[k] != '.'){
            //s2 = s2 + name[k];
            strncat(s2,name, k);
            k++;
        }
    }
    return strcat(addrear(s1,9),addrear(s2,3));
}

char* exten (char* name)
{
    int i, j, k, l;
    char *s1, *s2, *s3;
    k = 0;
    while(k < strlen(name) && name[k] != '.')
    {
        //s1 = s1 + name[k];
        strncat(s1, name, k);
        k++;
    }
    if (k < strlen(name))
    {
        k++;
        while (k < strlen(name) && name[k] != '.'){
            //s2 = s2 + name[k];
            strncat(s2, name, k);
            k++;
        }
    }
    return (addrear(s2,3));
}

char* base_name(char* name)
{
    char * s1;
    s1 = strrchr(name, '.');
    name[strlen(name)-strlen(s1)] = '\0';
    return name;
}

/**string attribs(int b){
  return
}**/

char* path(char* fn){
    int i, k;
    k = 0;
    for (i = strlen(fn)-1; i >= 0; i--)
    {
        if ((fn[i] == '\\' || fn[i] == ':') && k<i)
        {
            k = i;
        }
    }
    if (k != 0)
    {
        return (lstr(fn,k));
    }
    else
    {
        return NULL;
    }
}

/*
string no_path(string fn){
    int i, k;
    k = 0;
    for (i = fn.length()-1; i>= 0; i--){
        if ((fn[i] == '\\' || fn[i] == ':') && k<i){
            k = i;
        }
    }
    if (k != 0){
        return (rstr(fn, fn.length() - k));
    }
    else{
        return fn;
    }
}

long file_length(string fn){

}
*/
