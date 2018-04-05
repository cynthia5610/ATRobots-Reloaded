#include <iostream>
#include <string>
#include "Macchiato.h"
#include "filelib.h"
// Optionally use the namespace to do `describe` instead of `Macchiato::describe`, etc
using namespace Macchiato;



void valid_test() {

   

	describe("valid", [&]() {
			it("This will test to see if the file is valid/exists", [&]() {
				return expect(VALID("sample.txt").to->equal(true)->getResult();
			});

	});

    
	

	
}