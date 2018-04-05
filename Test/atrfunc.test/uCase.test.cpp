#include <string>
#include <iostream>
#include "../maccHeaders/Macchiato.h"
#include "../../bin/atrrfunc.hh"
using namespace Macchiato;

void uCase_test();
char* uCase(char* lString);

char* uCase(char* lString){

	char a[100];
    while(*lString != '\0'){
        *lString = toupper((unsigned char)*lString);
        ++lString;
    }

    return lString;
}

void uCase_test(){
    	describe("Testing uCase(string lString)", [&]() {
			it("lString = 'lower'", [&]() {
			    return expect(uCase(0)).to->equal("LOWER")->getResult();
			});
	    });
}   

int main()
{
	uCase_test();
	return 0;
}