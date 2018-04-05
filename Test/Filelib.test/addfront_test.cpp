#include <iostream>
#include <string>
#include "Macchiato.h"
#include "filelib.hh"
// Optionally use the namespace to do `describe` instead of `Macchiato::describe`, etc
using namespace Macchiato;



void addfront_test() {

   

	describe("addfront", [&]() {
			it("This will append a certain amount of characters to the front of the string", [&]() {
				return expect(addfront("wow",2)).to->equal("wow  ")->getResult();
			});

	});

    
	

	
}