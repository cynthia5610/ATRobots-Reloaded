#include <string>
#include <iostream>
#include "hexnum.test.cpp"
#include "hexb.test.cpp"
#include "hex.test.cpp"
#include "valuer.test.cpp"
#include "value.test.cpp"
#include "cstrr.test.cpp"
#include "cstr.test.cpp"
#include "zero_pad.test.cpp"
#include "zero_pads.test.cpp"
#include "addfront.test.cpp"
#include "uCase.test.cpp"
#include "lcase.test.cpp"
#include "space.test.cpp"
#include "repchar.test.cpp"
#include "../../bin/atrrfunc.hh"
#include "../maccHeaders/Macchiato.h"

using namespace Macchiato;
int main(){
    	
    hexnum_test();
    hexb_test();
    hex_test();
    valuer_test();
    value_test();
    cstrr_test();
    cstr_test();
    zero_pad_test();
    zero_pads_test();    
    addfront_test();
    uCase_test();
    lcase_test();
    space_test();
    repchar_test();

    std::cout << Macchiato::GetResultantTestOutput() << std::endl;
    
    return 0;
}   