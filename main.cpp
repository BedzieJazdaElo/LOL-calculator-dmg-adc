#include<iostream>
#include <fstream>
#include "calculator_dmg.hpp"
int main()
{
    Champion_class champion1("Aphelios");
    Champion_class champion2("Aatrox");
    fight(champion1, champion2, 1, 1);// output: Aatrox won in 6.05694 seconds
}