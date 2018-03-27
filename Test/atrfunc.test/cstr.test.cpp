#include <string>
#include <iostream>
#include "../maccHeaders/Macchiato.h"
#include "../../bin/atrrfunc.hh"
using namespace Macchiato;

void cstr_test();

void cstr_test(){
    	describe("Testing cstr(long int i)", [&]() {
			it("i = 1000", [&]() {
			    return expect(cstr(1000)).to->equal("1000")->getResult();
			});
	    });
}   