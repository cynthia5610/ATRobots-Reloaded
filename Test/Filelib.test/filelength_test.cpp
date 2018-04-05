#include <iostream>
#include <string>
#include "Macchiato.h"
#include "filelib.hh"

using namespace Macchiato;



void filelength_test() {

   

	describe("File Length", [&]() {
			it("This should display the length of the file", [&]() {
				return expect(file_length("sample.txt")).to->equal("2")->getResult();
			});

	});

    
	

	
}