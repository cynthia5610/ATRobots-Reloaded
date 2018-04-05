#include <iostream>
#include <string>
#include "Macchiato.h"
#include "filelib.hh"
// Optionally use the namespace to do `describe` instead of `Macchiato::describe`, etc
using namespace Macchiato;

string addrear(string b, int l){
    while(b.length() < l){
        b = b + ' ';
    }
    return b;
} 

string name_form(string name){
    int i, j, k = 0, l;
    string s1, s2, s3;
    if (name == "." || name == ".."){
        return addrear(name,12);
    }
    while(k < name.length() && name[k] != '.'){  //prob should be < for every one of this
        s1 = s1 + name[k];
        k++;
    }
    if (k < name.length()){
        k++;
        while (k < name.length() && name[k] != '.'){
            s2 = s2 + name[k];
            k++;
        }
    }
    return (addrear(s1,9) + addrear (s2,3));
}

void nameform_test() {

   
   

	describe("name_form", [&]() {
			it("Will make a string less than 12 = 12 and end when encountering .", [&]() {
				return expect(name_form("example")).to->equal("example     ")->getResult();
			});

	});

    

	

	return 0;
}