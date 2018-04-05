#include <iostream>
#include <string>
#include "Macchiato.h"
#include "filelib.h"
// Optionally use the namespace to do `describe` instead of `Macchiato::describe`, etc
using namespace Macchiato;

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

void nopath_test() {


	describe("no_path", [&]() {
			it("this will cut chars from the right of a string when it comes across either a ':' '//' ", [&]() {
				return expect(no_path("wow.")).to->equal("wow.")->getResult();
			});

	});

    

	

	
}

