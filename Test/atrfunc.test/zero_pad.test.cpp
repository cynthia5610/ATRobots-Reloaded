#include <string>
#include <iostream>
#include "../maccHeaders/Macchiato.h"
#include "../../bin/atrrfunc.hh"
using namespace Macchiato;

void zero_pad_test();

void zero_pad_test(){
    	describe("Testing zero_pad(long n, long l)", [&]() {
			it("n = 800, l = 4", [&]() {
			    return expect(zero_pad(800, 4)).to->equal("0800")->getResult();
			});
	    });
}   