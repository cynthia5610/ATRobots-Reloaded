#include <string>
#include <iostream>
#include "../maccHeaders/Macchiato.h"
#include "../../bin/atrrfunc.hh"
using namespace Macchiato;

void hexnum_test();

void hexnum_test(){
    	describe("Testing hexnum(unsigned char num)", [&]() {
			it("num = 9", [&]() {
			    return expect(hexnum(9)).to->equal('9')->getResult();
			});
	    });
}   