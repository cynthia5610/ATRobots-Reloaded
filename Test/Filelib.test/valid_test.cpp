#include <iostream>
#include <string>
#include "Macchiato.h"
#include "filelib.hh"
// Optionally use the namespace to do `describe` instead of `Macchiato::describe`, etc
using namespace Macchiato;

bool VALID(string thisfile){
    if (!EXIST(thisfile)){
		
    }
}

void valid_test() {
   
	describe("valid", [&]() {
			it("This will test to see if the file is valid/exists", [&]() {
				return expect(path("samplefile.txt")).to->equal("true")->getResult();
			});

	});

    
	

	
}