#include <iostream>
#include "Macchiato.h"
#include "filelib.hh"
// Optionally use the namespace to do `describe` instead of `Macchiato::describe`, etc
using namespace Macchiato;


void lstr_test() {




	describe("lstr", [&]() {
			it("should reduce wow to one char on left", [&]() {
				return expect(lstr("wow",1)).to->equal("w")->getResult();
			});

	});

    

	

	
}