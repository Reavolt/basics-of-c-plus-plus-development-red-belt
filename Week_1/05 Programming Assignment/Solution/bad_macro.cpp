//This is a personal academic project. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "test_runner.h"

#include <iostream>
#include <sstream>

//-------------------------------------------------------------------------------------------------
#define PRINT_VALUES(out, x, y) out << (x) << std::endl << (y) << std::endl
//-------------------------------------------------------------------------------------------------
int main()
{
    TestRunner tr;
    tr.RunTest([] 
    {
        std::ostringstream output;
        PRINT_VALUES(output, 5, "red belt");
        ASSERT_EQUAL(output.str(), "5\nred belt\n");
    }, "PRINT_VALUES usage example");

    tr.RunTest([]
    {
        std::ostringstream output;
        int x = 6;
        if (false)
            PRINT_VALUES(output, x, x-3);
        else
            PRINT_VALUES(output, --x, x+3);
        ASSERT_EQUAL(output.str(), "5\n8\n");
    }, "PRINT_VALUES IF (FALSE) 6 6 ELSE 5 6");

    return 0;
}
//-------------------------------------------------------------------------------------------------