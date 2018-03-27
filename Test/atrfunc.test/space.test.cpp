#include <string>
#include <iostream>
#include "../maccHeaders/Macchiato.h"
#include "../atrfiles/atrrfunc.hh"
using namespace Macchiato;

void space_test();

void space_test(){
    	describe("Testing space(unsigned char i)", [&]() {
			it("i = '3'", [&]() {
			    return expect(space('3')).to->equal("                                                   ")->getResult();
			});
	    });
}   