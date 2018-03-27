#include <string>
#include <iostream>
#include "../maccHeaders/Macchiato.h"
#include "../atrfiles/atrrfunc.hh"
using namespace Macchiato;

void addfront_test();

void addfront_test(){
    	describe("Testing addfront(string b, int l)", [&]() {
			it("b = 'dice', l = 8", [&]() {
			    return expect(addfront("dice", 8)).to->equal("    dice")->getResult();
			});
	    });
}   