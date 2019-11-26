#include "GFNumber.h"
#include <iostream>

/**
 * @brief Main function
 * @return 0 in case the program succeeded
 */
int main()
{
    GFNumber num1;
    GFNumber num2;
    std::cin >> num1 >> num2; // Getting the numbers

    assert(!std::cin.fail());
    assert(num1.getField() == num2.getField());

    // Print the requested information
    std::cout << num1 + num2 << std::endl;
    std::cout << num1 - num2 << std::endl;
    std::cout << num2 - num1 << std::endl;
    std::cout << num2 * num1 << std::endl;
    num1.printFactors();
    num2.printFactors();
    return 0;
}
