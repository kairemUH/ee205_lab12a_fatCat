///////////////////////////////////////////////////////////////////////////////
///         University of Hawaii, College of Engineering
/// @brief  ee205_lab12a_fatCat - EE 205 - Spr 2022
///
/// @file Weight.cpp
/// @version 1.0
///
/// rules: 1) once weight is known it cannot be unknown and must be greater than zero, or it can be unknown
///        2) once weight unit is set it cannot be changed
///        3) once weight max is set and known it cannot be changed or unknown
///
/// @author Kai Matsusaka <kairem@hawaii.edu>
/// @date   16_Apr_2022
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <stdexcept>
#include <iomanip>

#include "Weight.h"

#define FORMAT_LINE( className, member ) std::cout << std::setw(8) << (className) << std::setw(20) << (member) << std::setw(52)


////////////////////  Constructors  ////////////////////

Weight::Weight() noexcept {
    Weight::bIsKnown = false;
    Weight::bHasMax  = false;
    Weight::unitOfWeight = POUND;   // defaults to pound
    Weight::weight = UNKNOWN_WEIGHT;
    Weight::maxWeight = UNKNOWN_WEIGHT;
}


Weight::Weight( float newWeight ) {
    Weight::bIsKnown = true;
    Weight::bHasMax  = false;
    Weight::unitOfWeight = POUND;   // defaults to pound
    Weight::weight = newWeight;
    Weight::maxWeight = UNKNOWN_WEIGHT;
}


Weight::Weight( UnitOfWeight newUnitOfWeight ) noexcept {
    Weight::bIsKnown = false;
    Weight::bHasMax  = false;
    Weight::unitOfWeight = newUnitOfWeight;
    Weight::weight = UNKNOWN_WEIGHT;
    Weight::maxWeight = UNKNOWN_WEIGHT;
}


Weight::Weight( float newWeight, UnitOfWeight newUnitOfWeight ) {
    Weight::bIsKnown = true;
    Weight::bHasMax  = false;
    Weight::unitOfWeight = newUnitOfWeight;
    Weight::weight = newWeight;
    Weight::maxWeight = UNKNOWN_WEIGHT;
}


Weight::Weight( float newWeight, float newMaxWeight ) {
    Weight::bIsKnown = true;
    Weight::bHasMax  = true;
    Weight::unitOfWeight = POUND;   // defaults to pound
    Weight::weight = newWeight;
    Weight::maxWeight = newMaxWeight;
}


Weight::Weight( UnitOfWeight newUnitOfWeight, float newMaxWeight ) {
    Weight::bIsKnown = false;
    Weight::bHasMax  = true;
    Weight::unitOfWeight = newUnitOfWeight;
    Weight::weight = UNKNOWN_WEIGHT;
    Weight::maxWeight = newMaxWeight;
}


Weight::Weight( float newWeight, UnitOfWeight newUnitOfWeight, float newMaxWeight ) {
    Weight::bIsKnown = true;
    Weight::bHasMax  = true;
    Weight::unitOfWeight = newUnitOfWeight;
    Weight::weight = newWeight;
    Weight::maxWeight = newMaxWeight;
}



////////////////////  Getters  ////////////////////

bool Weight::isWeightKnown() const noexcept {
    return Weight::bIsKnown;
}


bool Weight::hasMaxWeight() const noexcept {
    return Weight::bHasMax;
}


float Weight::getWeight() const noexcept {
    return Weight::weight;
}


float Weight::getWeight( UnitOfWeight weightUnits ) const noexcept {

    if ( Weight::bIsKnown ) {
        return convertWeight(Weight::weight, Weight::unitOfWeight, weightUnits);
    }

    else {
        return UNKNOWN_WEIGHT;
    }

}


float Weight::getMaxWeight() const noexcept {

    return Weight::maxWeight;

}


Weight::UnitOfWeight Weight::getWeightUnit() const noexcept {

    return Weight::unitOfWeight;

}



////////////////////  Setters  ////////////////////

void Weight::setWeight( float newWeight ) {

    if ( isWeightValid(newWeight) ) {
        Weight::weight = newWeight;
        Weight::bIsKnown = true;
    }

}


void Weight::setWeight( float newWeight, UnitOfWeight weightUnits ) {

    if ( isWeightValid(newWeight) ) {
        Weight::weight = convertWeight(newWeight, weightUnits, Weight::unitOfWeight);
        Weight::bIsKnown = true;
    }

}


void Weight::setMaxWeight( float newMaxWeight ) {

    if ( Weight::bHasMax ) {
        throw std::logic_error( "Max weight has already been set." );
    }

    if ( newMaxWeight < Weight::weight ) {
        throw std::logic_error( "Max weight is less than set weight." );
    }

    if ( isWeightValid(newMaxWeight) ) {
            Weight::maxWeight = newMaxWeight;
            Weight::bHasMax = true;
    }

}



////////////////////  Unit Conversion Functions  ////////////////////

 float Weight::fromKilogramToPound(float kilogram) noexcept {

    return kilogram / KILOS_IN_A_POUND;

}


float Weight::fromPoundToKilogram(float pound) noexcept {

    return pound * KILOS_IN_A_POUND;

}


float Weight::fromSlugToPound(float slug) noexcept {

    return slug / SLUGS_IN_A_POUND;

}


float Weight::fromPoundToSlug(float pound) noexcept {

    return pound * SLUGS_IN_A_POUND;

}


float Weight::convertWeight(float fromWeight, UnitOfWeight fromUnit, UnitOfWeight toUnit) noexcept {

    switch ( fromUnit ) {
        case POUND:
            switch ( toUnit ) {
                case POUND: return fromWeight;
                case KILO:  return fromPoundToKilogram(fromWeight);
                case SLUG:  return fromPoundToSlug(fromWeight);
                default:    return fromWeight;
            }

        case KILO:
            switch ( toUnit ) {
                case POUND: return fromKilogramToPound(fromWeight);
                case KILO:  return fromWeight;
                case SLUG:  return fromPoundToSlug(fromKilogramToPound(fromWeight));
                default:    return fromWeight;
            }

        case SLUG:
            switch ( toUnit ) {
                case POUND: return fromSlugToPound(fromWeight);
                case KILO:  return fromPoundToKilogram(fromSlugToPound(fromWeight));
                case SLUG:  return fromWeight;
                default:    return fromWeight;

            }

        default: return fromWeight;

    }

}



////////////////////  Operator  ////////////////////

bool Weight::operator==( const Weight& rhs_Weight ) const {
    /// Remember to convert the two weight's units into a common unit!
    /// Treat unknown weights as 0 (so we can sort them without dealing
    /// with exceptions)
    float lhs_weight = (bIsKnown) ? getWeight(Weight::POUND) : 0;
    float rhs_weight = (rhs_Weight.bIsKnown) ? rhs_Weight.getWeight(Weight::POUND) : 0;
    return lhs_weight == rhs_weight;
}

bool Weight::operator<(const Weight &rhs_Weight) const {

    float lhs_weight = (bIsKnown) ? getWeight(Weight::POUND) : 0;
    float rhs_weight = (rhs_Weight.bIsKnown) ? rhs_Weight.getWeight(Weight::POUND) : 0;
    return lhs_weight < rhs_weight;

}

Weight & Weight::operator+=(float rhs_addToWeight) {

    if ( ! Weight::bIsKnown ) {
        throw std::out_of_range( "Cannot add to unknown weight." );
    }

    Weight::weight += rhs_addToWeight;
    return *this;

}

std::ostream& operator<<( std::ostream& lhs_stream
        ,const Weight::UnitOfWeight rhs_UnitOfWeight ) {
    switch( rhs_UnitOfWeight ) {
        case Weight::POUND: return lhs_stream << "Pounds" ;
        case Weight::KILO: return lhs_stream << "Kilograms" ;
        case Weight::SLUG: return lhs_stream << "Slugs" ;
        default:
            throw std::out_of_range( "The unit can’t be mapped to a string" );
    }
}



////////////////////  Validation and Dump Functions  ////////////////////

bool Weight::isWeightValid( float checkWeight ) const {

    if ( checkWeight <= 0 ) {
        throw std::invalid_argument( "Weight must be greater than 0." );
    }

    if ( Weight::bHasMax ) {
        if ( checkWeight > Weight::maxWeight ) {
            throw std::invalid_argument( "Weight must be less than or equal to the max weight." );
        }
    }

    return true;

}


bool Weight::validate() const {

    if ( ! Weight::bIsKnown && Weight::weight == UNKNOWN_WEIGHT ) {
        return true;
    }

    else if ( Weight::bIsKnown && Weight::isWeightValid(Weight::weight) ) {
        return true;
    }

    return false;

}


void Weight::dump() const noexcept {

    std::cout << std::setw(80) << std::setfill( '=' ) << "" << std::endl ;
    std::cout << std::setfill( ' ' ) ;
    std::cout << std::left ;
    std::cout << std::boolalpha ;
    FORMAT_LINE( "Weight", "this" )         << this                 << std::endl ;
    FORMAT_LINE( "Weight", "isKnown" )      << Weight::bIsKnown     << std::endl ;
    FORMAT_LINE( "Weight", "weight" )       << Weight::weight       << std::endl ;
    FORMAT_LINE( "Weight", "unitOfWeight" ) << Weight::unitOfWeight << std::endl ;
    FORMAT_LINE( "Weight", "hasMax" )       << Weight::bHasMax      << std::endl ;
    FORMAT_LINE( "Weight", "maxWeight" )    << Weight::maxWeight    << std::endl ;

}