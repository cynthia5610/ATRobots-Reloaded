#include <iostream>
#include <string>
#include "Macchiato.h"
#include "filelib.hh"
// Optionally use the namespace to do `describe` instead of `Macchiato::describe`, etc
using namespace Macchiato;


string base_name(string name){
    int i, j, k, l;
    string s1, s2, s3;
    k = 0;
    while(k < name.length() && name[k] != '.'){
        s1 = s1 + name[k];
        k++;
    }
    return s1;
}

void basename_test() {

   
   

	describe("exten", [&]() {
			it("Will end a string when a '.' is found", [&]() {
				return expect(base_name("cir.cle")).to->equal("cir")->getResult();
			});

	});

    

	

	
}