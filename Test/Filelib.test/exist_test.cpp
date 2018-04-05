#include <iostream>
#include <fstream>
#include "Macchiato.h"
#include "filelib.hh"
// Optionally use the namespace to do `describe` instead of `Macchiato::describe`, etc
using namespace Macchiato;

bool EXIST(string thisfile){
    ifstream inFile;
    inFile.open(thisfile);
    if(!inFile.is_open()){
        return false;
    }
    else{
        inFile.close();
        return true;
    }
}

void exist_test() {




	describe("EXIST", [&]() {
			it("Should check to see if a set file exists", [&]() {
				return expect(EXIST("samplefile.txt")).to->equal(true)->getResult();
			});

	});

    

	

	
}