#include <iostream>
#include <string>
#include "Macchiato.h"
#include "filelib.h"
// Optionally use the namespace to do `describe` instead of `Macchiato::describe`, etc
using namespace Macchiato;



void filelength_test() {

   

	describe("File Length", [&]() {
			it("This should display the length of the file", [&]() {
				return expect(file_length(sample.txt)).to->equal("2")->getResult();
			});

	});

    
	

	
}