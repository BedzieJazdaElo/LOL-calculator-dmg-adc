#include<iostream>
#include "calculator_dmg.hpp"

int main()
{
    character_lol aatrox{580, 38, 32};
    std::cout<<aatrox.hp-dmg_calculator({100, 100, 100}, aatrox)<<std::endl; // output: 331.779
}