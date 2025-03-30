#include "headers/func.h"

template <typename Container, typename T> 
bool isIn(const Container& arr, const T& val)
{
    for (const auto& i : arr)
        if (i == val) return true;
    return false;
}

vsp <Driver> findDrivers(const char startingRegion, const char endingRegion, Registry registry)
{
    vsp <Driver> availableDrivers;
    for (auto &ag : registry.getAgencies())
        for (auto &dr : ag -> getDrivers())
            if (dr -> operatesInRegion(startingRegion)
             && dr -> operatesInRegion(endingRegion)
             && !isIn(availableDrivers, dr))
                availableDrivers.push_back(dr);
    
    return availableDrivers;
}
