#include <iostream>
#include <string>
#include "Macchiato.h"
#include "filelib.h"
// Optionally use the namespace to do `describe` instead of `Macchiato::describe`, etc
using namespace Macchiato;



void addrear_test() {

   

	describe("addrear", [&]() {
			it("This should append a certain number of characters on the left side of the string", [&]() {
				return expect(addrear("wow",2)).to->equal("  wow")->getResult();
			});

	});

    
	

	
}