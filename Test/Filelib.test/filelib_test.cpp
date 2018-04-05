#include <string>
#include <iostream>
#include "exist_test.cpp"
#include "path_test.cpp"
#include "valid_test.cpp"
#include "rstr_test.cpp"
#include "lstr_test.cpp"
#include "exten_test.cpp"
#include "addrear_test.cpp"

using namespace Macchiato;

int main()
{


exist_test();
path_test();
valid_test();
rstr_test();
lstr_test();
exten_test();
addrear_test();

std::cout << Macchiato::GetResultantTestOutput() << std::endl;

return 0;




}