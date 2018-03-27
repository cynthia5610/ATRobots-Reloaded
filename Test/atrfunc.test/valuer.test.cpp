#include <string>
#include <iostream>
#include "../maccHeaders/Macchiato.h"
#include "../../bin/atrrfunc.hh"
using namespace Macchiato;

void valuer_test();

void valuer_test(){
    	describe("Testing valuer(string i)", [&]() {
			it("i = '1000'", [&]() {
			    return expect(valuer("1000")).to->equal(1000)->getResult();
			});
	    });
}   