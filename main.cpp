///////////////////////////////////////////////////////////////////////////////
///         University of Hawaii, College of Engineering
/// @brief  ee205_lab12a_fatCat - EE 205 - Spr 2022
///
/// @file main.cpp
/// @version 1.0
///
/// @author Kai Matsusaka <kairem@hawaii.edu>
/// @date   16_Apr_2022
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cassert>

#include "Weight.h"


int main() {

    Weight firstWeight = Weight();
    assert( firstWeight.validate() );
    assert( firstWeight.hasMaxWeight() == false );
    assert( firstWeight.isWeightKnown() == false );
    firstWeight.dump();


    firstWeight.setWeight(5);
    firstWeight.setMaxWeight(20);
    assert( firstWeight.validate() );
    assert(firstWeight.hasMaxWeight() == true);
    assert( firstWeight.isWeightKnown() == true );
    firstWeight.dump();


    try {
        firstWeight.setMaxWeight(3);
        assert(false);
    } catch (std::exception const &e) {}


    try {
        firstWeight.setWeight(33);
        assert(false);
    } catch (std::exception const &e) {}


    firstWeight.setWeight(3.42, Weight::KILO); // should be ~ 7.54 pounds
    firstWeight.dump();



    Weight secondWeight = Weight( 0.4535, Weight::KILO );
    assert( secondWeight.validate() );
    assert( secondWeight.getWeightUnit() == Weight::KILO );
    secondWeight.dump();

    std::cout << secondWeight.getWeight( Weight::POUND ) << std::endl; // should be ~ 1 pound


    return 0;

}
