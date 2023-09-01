#include "faultbuilder.h"

#include <iostream>

awv::FaultBuilder::
FaultBuilder()  : ModelBuilder()
{
    std::cout << "awv::FaultBuilder-ctor:" << std::endl;
}

awv::FaultBuilder::
~FaultBuilder()
{
}

void
awv::FaultBuilder::
buildit()
{
    std::cout << "awv::FaultBuilder: buildit()" << std::endl;
}
