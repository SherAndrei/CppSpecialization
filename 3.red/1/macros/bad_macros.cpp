#include <iostream>
#include <sstream>

#include "test_runner.h"

using namespace std;

#define PRINT_VALUES(out, x, y)  (out) << (x) << endl << (y) << endl

void Test() {
    {
        ostringstream os;
        PRINT_VALUES(os, 1, 2);
        AssertEqual(os.str(), "1\n2\n");
    }
    {
        ostringstream os;
        PRINT_VALUES(os, 1 == 1, 2 == 1);
        AssertEqual(os.str(), "1\n0\n");
    }
    {
        ostringstream os;
        if (true)
            PRINT_VALUES(os, 1, 2);
        else
            PRINT_VALUES(os, 3, 4);

        AssertEqual(os.str(), "1\n2\n");
    }
    {
        ostringstream os;

        do
            PRINT_VALUES(os, 1, 2);
        while (false);

        AssertEqual(os.str(), "1\n2\n");
    }
    {
        ostringstream os;

        int isTrue = 0;
        while (isTrue++ != 1)
            PRINT_VALUES(os, 1, 2);

        AssertEqual(os.str(), "1\n2\n");
    }
    {
        ostringstream os;

        bool isTrue = true;
        switch (isTrue) {
        case true:
            PRINT_VALUES(os, 1, 1);
            PRINT_VALUES(os, 2, 2);
                break;
        case false: PRINT_VALUES(os, 0, 0);
            break;
        default:
            break;
        }
            AssertEqual(os.str(), "1\n1\n2\n2\n");
    }
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, Test);
}
