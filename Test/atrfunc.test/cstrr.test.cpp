#include <string>
#include <iostream>
#include "../maccHeaders/Macchiato.h"
#include "../../bin/atrrfunc.hh"
using namespace Macchiato;

void cstrr_test();

void cstrr_test(){
    	describe("Testing cstrr(double i)", [&]() {
			it("i = 1000", [&]() {
			    return expect(cstrr(1000)).to->equal("1000")->getResult();
			});
	    });
}   