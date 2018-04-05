#include <string>
#include <iostream>
#include "rstr_test.cpp"
#include "basename_test.cpp"
#include "nopath_test.cpp"
#include "exist_test.cpp"
#include "lstr_test.cpp"
#include "exten_test.cpp"
#include "filelength_test.cpp"
#include "addrear_test.cpp"
#include "addfront_test.cpp"
#include "valid_test.cpp"
#include "nameform_test.cpp"

using namespace Macchiato;

int main()
{

rstr_test();
basename_test();
nopath_test();
exist_test();
lstr_test();
exten_test();
path_test();
filelength_test();
addrear_test();
addfront_test();
valid_test();
nameform_test();

std::cout << Macchiato::GetResultantTestOutput() << std::endl;

return 0;




}