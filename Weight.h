///////////////////////////////////////////////////////////////////////////////
///         University of Hawaii, College of Engineering
/// @brief  ee205_lab12a_fatCat - EE 205 - Spr 2022
///
/// @file Weight.h
/// @version 1.0
///
/// rules: 1) once weight is known it cannot be unknown and must be greater than zero, or it can be unknown
///        2) once weight unit is set it cannot be changed
///        3) once weight max is set and known it cannot be changed or unknown
///
/// @author Kai Matsusaka <kairem@hawaii.edu>
/// @date   16_Apr_2022
///////////////////////////////////////////////////////////////////////////////

#pragma once


class Weight {

////////////////////  Enum  ////////////////////
public:
    enum UnitOfWeight {POUND, KILO, SLUG};


////////////////////  Member Variables  ////////////////////
private:
    constexpr static const float UNKNOWN_WEIGHT   = -1;
    constexpr static const float KILOS_IN_A_POUND = 0.4536;
    constexpr static const float SLUGS_IN_A_POUND = 0.0311;
    bool bIsKnown;
    bool bHasMax;
    enum UnitOfWeight unitOfWeight;
    float weight;
    float maxWeight;


////////////////////  Constructors  ////////////////////
public:
    Weight() noexcept;
    Weight(float newWeight);
    Weight(UnitOfWeight newUnitOfWeight) noexcept;
    Weight(float newWeight, UnitOfWeight newUnitOfWeight);
    Weight(float newWeight, float newMaxWeight);
    Weight(UnitOfWeight newUnitOfWeight, float newMaxWeight);
    Weight(float newWeight, UnitOfWeight newUnitOfWeight, float newMaxWeight);


////////////////////  Getters and Setters  ////////////////////
public:
    bool isWeightKnown() const noexcept;
    bool hasMaxWeight() const noexcept;
    float getWeight() const noexcept;
    float getWeight(UnitOfWeight weightUnits) const noexcept;
    float getMaxWeight() const noexcept;
    UnitOfWeight getWeightUnit() const noexcept;
    void setWeight(float newWeight);
    void setWeight(float newWeight, UnitOfWeight weightUnits);
    void setMaxWeight(float newMaxWeight);


////////////////////  Unit Conversion Functions  ////////////////////
private:
    static float fromKilogramToPound(float kilogram) noexcept;
    static float fromPoundToKilogram(float pound) noexcept;
    static float fromSlugToPound(float slug) noexcept;
    static float fromPoundToSlug(float pound) noexcept;
    static float convertWeight(float fromWeight, UnitOfWeight fromUnit, UnitOfWeight toUnit) noexcept;


////////////////////  Operator  ////////////////////
public:
    bool operator==(const Weight &rhs_Weight) const;
    bool operator<(const Weight &rhs_Weight) const;
    Weight & operator+=(float rhs_addToWeight);


////////////////////  Validation and Dump Functions  ////////////////////
private:
    bool isWeightValid(float checkWeight) const;

public:
    bool validate() const;
    void dump() const noexcept;

};
