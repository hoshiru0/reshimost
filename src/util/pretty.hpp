#pragma once
#include <iostream>
// pretty
void pretty(auto&&) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}
