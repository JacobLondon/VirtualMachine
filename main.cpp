#include <iostream>
#include "processor.hpp"

int main()
{
    Processor p(1000);
    std::cout << p.mem.to_string() << std::endl;
    return 0;
}
