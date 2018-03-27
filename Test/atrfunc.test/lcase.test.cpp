#include <string>
#include <iostream>
#include "../maccHeaders/Macchiato.h"
#include "../atrfiles/atrrfunc.hh"
using namespace Macchiato;

void lcase_test();

void lcase_test(){
    	describe("Testing lcase(string s)", [&]() {
			it("s = 'upper'", [&]() {
			    return expect(lcase("UPPER")).to->equal("upper")->getResult();
			});
	    });
}   