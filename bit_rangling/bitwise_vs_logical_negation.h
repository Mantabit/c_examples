/*
This test program illustrates the difference between logical and bitwise negation
it should be kept in mind when programming AVR C
*/

#include <iostream>
#include <bitset>
#include <cstdint>

using namespace std;

int main()
{
    std::bitset<8> mybits;
    uint8_t x;
    
    x=1;
    mybits=x;
    std::cout << mybits << std::endl;
    
    //bitwise negation will turn 0b00000001 to 0b11111110
    x=~x;
    mybits=x;
    std::cout << mybits << std::endl;
    
    //logical negation will turn 0b00000001 to 0b00000000
    x=1;
    x=!x;
    mybits=x;
    std::cout << mybits << std::endl;

    return 0;
}
