#include <string>
#include <iostream>
#include "../maccHeaders/Macchiato.h"
#include "../../bin/atrrfunc.hh"
using namespace Macchiato;

void uCase_test();

void uCase_test(){
    	describe("Testing uCase(string lString)", [&]() {
			it("lString = 'lower'", [&]() {
			    return expect(uCase("lower")).to->equal("LOWER")->getResult();
			});
	    });
}   