#include <string>
#include <iostream>
#include "../maccHeaders/Macchiato.h"
#include "../../bin/atrrfunc.hh"
using namespace Macchiato;

void valuer_test2();

void valuer_test2(){
    	describe("Testing valuer(char *i)", [&]() {
			it("i = '1000'", [&]() {
			    return expect(valuer("10.5")).to->equal(10.5)->getResult();
			});
	    });

     
}   
int main()
{
	std::cout << Macchiato::GetResultantTestOutput() << std::endl;
}