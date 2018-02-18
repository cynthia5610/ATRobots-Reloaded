#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>


//the attribs and file_length functions still need to be converted to c++;
/* -- This unit contains functions useful for dealing with filenames. -- */

using namespace std;

string addfront(string b, int l);
string addrear(string b, int l);
string lstr(string s1, int l);
string rstr(string s1, int l);
bool EXSIST(string thisfile);
bool VALID(string thisfile);
string name_form(string name);
string exten(string name);
string base_name(string name);
string attribs(int byte);
string path(string fn);
string no_path(string fn);
long file_length(string fn);


int main(){

}

string addfront(string b, int l){
    while(b.length() < l){
        b = ' ' + b;
    }
    return b;
}

string addrear(string b, int l){
    while(b.length() < l){
        b = b + ' ';
    }
    return b;
}

string lstr(string s1, int l){
    if(s1.length() <= l){
        return s1;
    }
    else{
        char temp[s1.length()];
        s1.copy(temp, l, 0);
        s1 = temp;
        return s1;
    }
}

string rstr(string s1, int l){
    if(s1.length() <= l){
        return s1;
    }
    else{
        char temp[s1.length()];
        s1.copy(temp, l, s1.length() - l);
        s1 = temp;
        return s1;
    } 
}

bool EXSIST(string thisfile){
    ifstream inFile;
    inFile.open(thisfile);
    if(!inFile.is_open()){
        return false;
    }
    else{
        inFile.close();
        return true;
    }
}

bool VALID(string thisfile){
    if (!EXSIST(thisfile)){

    }
}

string name_form(string name){
    int i, j, k = 0, l;
    string s1, s2, s3;
    if (name == "." || name == ".."){
        return addrear(name,12);
    }
    while(k <= name.length() && name[k] != '.'){  //prob should be < for every one of this
        s1 = s1 + name[k];
        k++;
    }
    if (k < name.length()){
        k++;
        while (k <= name.length() && name[k] != '.'){
            s2 = s2 + name[k];
            k++;
        }
    }
    return (addrear(s1,9) + addrear (s2,3));
}

string exten (string name){
    int i, j, k, l;
    string s1, s2, s3;
    k = 0;
    while(k <= name.length() && name[k] != '.'){
        s1 = s1 + name[k];
        k++;
    }
    if (k < name.length()){
        k++;
        while (k <= name.length() && name[k] != '.'){
            s2 = s2 + name[k];
            k++;
        }
    }
    return (addrear(s2,3));
}

string base_name(string name){
    int i, j, k, l;
    string s1, s2, s3;
    k = 1;
    while(k <= name.length() && name[k] != '.'){
        s1 = s1 + name[k];
        k++;
    }
    return s1;
}

string attribs(int b){
    
}

string path(string fn){
    int i, k;
    k = 0;
    for (i = fn.length(); i>= 1; i--){
        if ((fn[i] == '\\' || fn[i] == ':') && k<i){
            k = i;
        }
    }
    if (k != 0){
        return (lstr(fn,k));
    }
    else{
        return "";
    }  
}

string no_path(string fn){
    int i, k;
    k = 0;
    for (i = fn.length(); i>= 1; i--){
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