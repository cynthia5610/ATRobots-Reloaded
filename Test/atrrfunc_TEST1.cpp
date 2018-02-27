#include <iostream>
#include <string>
#include "atrrfunc.hh"

// This is a test file for ATRFUNC.CPP

using namespace std;

int main()
{

// Testing value function
cout << "-value-" << endl;
for(int i=0;i<42;i++)
{
    int long exampvalue;
   cout << "Pushing through value: this is a test of value" <<  value("this is a test of value") << endl;
   cout << value("abcdefghijklmnopqrstuvwxyznowiknowmyabcsnexttimewontyousingwithme special char ;'.,/?[]-=!@#$^&*()") << endl;
   exampvalue = value("This will turn a string into its long int value");
   cout << exampvalue << endl;
}

// Testing valuer function
cout << " " << endl;
cout << "-valuer-" << endl;
double exampvaluer;
exampvaluer = valuer("This will be converted from string to a real number");
cout << exampvaluer << endl;

// Testing cstrr
cout << " " << endl;
cout << "-cstrr-" << endl;
double exampcstrr = 15.3;
cout << cstrr(exampcstrr) << endl;
cout << cstrr(12.3) << endl;
cout << "this is not a double" << cstrr(21) << endl;

// Testing cstr
cout << " " << endl;
cout << "-cstr-" << endl;
string resultcstr;
long exampcstr = 2147483647;
cout << cstr(exampcstr) << endl;
cout << "This is not a long" << cstr(21) << endl;

// Testing ucase
cout << " " << endl;
cout << "-uCase-" << endl;
string resultucase;
string exampucase ="this is a test. this should be in allcaps";
resultucase = uCase(exampucase);
cout << resultucase << endl;
cout << uCase("THIS IS ALREADY CAPPED. WHAT WILL HAPPEN?") << endl;

// Testing lcase
cout << " " << endl;
cout << "-lcase-" << endl;
string resultlcase;
string examplcase = "THIS IS A TEST. THIS SHOULD BE IN LOWERCASE";
resultlcase = lcase(examplcase);
cout << resultlcase  << endl;
cout << lcase("this is already lowercase") << endl;





















return 0;
}