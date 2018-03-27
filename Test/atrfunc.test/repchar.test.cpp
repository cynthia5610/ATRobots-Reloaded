#include <string>
#include <iostream>
#include "../maccHeaders/Macchiato.h"
#include "../../bin/atrrfunc.hh"
using namespace Macchiato;

void repchar_test();

void repchar_test(){
    	describe("Testing repchar(char c, unsigned char i)", [&]() {
			it("c = 'p', i = '5'", [&]() {
			    return expect(repchar('p', '5')).to->equal("ppppppppppppppppppppppppppppppppppppppppppppppppppppp")->getResult();
			});
	    });
}   