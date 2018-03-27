#include <string>
#include <iostream>
#include "../maccHeaders/Macchiato.h"
#include "../../bin/atrrfunc.hh"
using namespace Macchiato;

void zero_pads_test();

void zero_pads_test(){
    	describe("Testing zero_pads(string s, long l)", [&]() {
			it("s = 600, l = 6", [&]() {
			    return expect(zero_pads("600", 6)).to->equal("000600")->getResult();
			});
	    });
}   