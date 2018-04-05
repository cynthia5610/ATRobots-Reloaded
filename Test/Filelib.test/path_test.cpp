#include <iostream>
#include <string>
#include "Macchiato.h"
#include "filelib.hh"
// Optionally use the namespace to do `describe` instead of `Macchiato::describe`, etc
using namespace Macchiato;

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

string path(string fn){
    int i, k;
    k = 0;
    for (i = fn.length()-1; i>= 0; i--){
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

void path_test() {

	describe("pathtest", [&]() {
			it("Will make string empty if the line does not have a ':' or '//' ", [&]() {
				return expect(path("wow:wo")).to->equal("wowwo")->getResult();
			});

	});

    

	

	
}