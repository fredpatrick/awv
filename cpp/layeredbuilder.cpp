#include "layeredbuilder.h"

#include <iostream>

awv::LayeredBuilder::
LayeredBuilder() : ModelBuilder()
{
    std::cout << "awv::LayeredBuilder-ctor:" << std::endl;
}

awv::LayeredBuilder::
~LayeredBuilder()
{
}

void
awv::LayeredBuilder::
buildit()
{
    std::cout << "awv::LayeredBuilder: buildit()" << std::endl;
}
