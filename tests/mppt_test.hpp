#ifndef __MPPT_TEST__
#define __MPPT_TEST__

#include <iostream>

#include "mppt.h"

class MPPT_Test {
    private:

    public:
        MPPT_Test() = default;
        void test();
};

void MPPT_Test::test() {
    std::cout << "MPPT TEST" << std::endl; 
}

#endif
