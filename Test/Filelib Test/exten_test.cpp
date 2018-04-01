#include <iostream>
#include <string>
#include "Macchiato.h"
#include "filelib.h"
// Optionally use the namespace to do `describe` instead of `Macchiato::describe`, etc
using namespace Macchiato;

string addrear(string b, int l){
    while(b.length() < l){
        b = b + ' ';
    }
    return b;
} 

string exten (string name){
    int i, j, k, l;
    string s1, s2, s3;
    k = 0;
    while(k < name.length() && name[k] != '.'){
        s1 = s1 + name[k];
        k++;
    }
    if (k < name.length()){
        k++;
        while (k < name.length() && name[k] != '.'){
            s2 = s2 + name[k];
            k++;
        }
    }
    return (addrear(s2,3));
}

void exten_test() {

   
   

	describe("exten", [&]() {
			it("Will make a string less than 12 = 12 and end when encountering .", [&]() {
				return expect(exten("wow.")).to->equal("    ")->getResult();
			});

	});

    

	std::cout << Macchiato::GetResultantTestOutput() << std::endl;

	return 0;
}