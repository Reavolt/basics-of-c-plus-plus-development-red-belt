#include "test_runner.h"

#include <iostream>

//-------------------------------------------------------------------------------------------------
#define UNIQ_ID_IMPL_2(lineno) _a_local_var_##lineno
#define UNIQ_ID_IMPL(lineno) UNIQ_ID_IMPL_2(lineno)
#define UNIQ_ID UNIQ_ID_IMPL(__LINE__)
//-------------------------------------------------------------------------------------------------
int main()
{
    int UNIQ_ID = 0;
    std::string UNIQ_ID = "hello";
    std::vector<std::string> UNIQ_ID = { "hello", "world" };
    std::vector<int> UNIQ_ID = { 1, 2, 3, 4 };
    return 0;
}
//-------------------------------------------------------------------------------------------------