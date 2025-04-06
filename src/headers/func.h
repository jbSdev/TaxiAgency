#ifndef FUNC_H
#define FUNC_H

#include "classes.h"

vsp <Driver> findDrivers(const char startingRegion, const char endingRegion, const Registry& registry, const string type = "normal");

template <typename T>
T getBestRegionProp(const Region a, const Region b, const shared_ptr <Driver>& driver, const string type)
{
    const vwp <Agency> agencies = driver -> getAgencies();
    float min = FLT_MAX;
    weak_ptr <Agency> agency;
    for (const auto& ag : agencies)
    {
        if (ag.lock() -> getRegionFee() < min && ag.lock() -> getType() == type && ag.lock() -> operatesInRegion(a) && ag.lock() -> operatesInRegion(b))
        {
            min = ag.lock() -> getRegionFee();
            agency = ag;
        }
    }

    if constexpr(is_same_v<T, float>)
        return min;
    else
        return agency;
};

vwp <Agency> getUsedAgencies(const pathInfo& path, const string type);

float calculatePrice(pathInfo& path, const Registry& registry, const string type);

void createTrip(const Region                start,
                const Region                end,
                const pathInfo&             path,
                const weak_ptr <Customer>   customer,
                const string                type);

#endif
