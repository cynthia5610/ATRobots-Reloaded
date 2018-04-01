#include <iostream>
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

void rstr_test() {




	describe("rstr", [&]() {
			it("should reduce examples to one char on right 's' should be output", [&]() {
				return expect(rstr("examples",1)).to->equal("s")->getResult();
			});

	});

    

	

	
}