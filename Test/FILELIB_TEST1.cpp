#include <iostream>
#include <string>
#include "filelib.hh"
using namespace std;


int main()
{


// Testing addfront 
cout << "-addfront-" << endl; 
string exampaddfrontb;
int exampaddfronti;
exampaddfrontb = "This is char long";
exampaddfronti = 27;
cout << "b length " << exampaddfrontb.length << endl;
cout << "Putting b through addfront" << endl;
string result = addfront(exampaddfrontb,exampaddfronti);
string b ="      ";
int i = 2;
string f = addfront(b,i);

if(f.length == i)
{
    cout << "f passed" << endl;
}
else{
    cout << "f failed" << endl;
}

if(result.length == 27)
{
    cout << "b passed " << endl;
}
else{
    cout << "b failed " << endl;
}


// Testing addrear
cout << "-addrear-" << endl; 
string exampaddrearb;
int exampaddreari;
exampaddrearb = "This is char long";
exampaddreari = 27;
cout << "b length " << exampaddrearb.length << endl;
cout << "Putting b through addrear" << endl;
string result_rear = addrear(exampaddrearb,exampaddreari);
string b_rear ="      ";
int i_rear = 2;
string f = addfront(b,i);

if(f.length == i)
{
    cout << "f passed" << endl;
}
else{
    cout << "f failed" << endl;
}

if(result_rear.length == 27)
{
    cout << "b passed " << endl;
}
else{
    cout << "b failed " << endl;
}

// Testing lstr
cout << " " << endl;
cout << "-lstr-" << endl;
string lstrexamp = "This string will get cut by 4 char";
int lstrvar=4;
cout << lstrexamp << endl;
cout << lstr(lstrexamp,lstrvar) << endl;

// Testing rstr
cout << " " << endl;
cout << "-rstr-" << endl;
string rstrexamp = " This is an example string";
int rstrvar = 5;
cout << rstrexamp << endl;
cout << rstr(rstrexamp,rstrvar) << endl;

// Testing Exist
cout << " " << endl;
cout << "-exist-" << endl;
string file = "examp.txt";      // examp.txt will be include. make sure before running test, both files are in the same directory
bool existbool;

existbool = exist(file);

cout << "File exists? " << existbool << endl;












return 0;
}