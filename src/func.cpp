#include "headers/func.h"
#include "headers/classes.h"
#include <climits>

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
        for (const auto &dr : ag -> getDrivers())
            if (dr -> operatesInRegion(startingRegion)
             && dr -> operatesInRegion(endingRegion)
             && !isIn(availableDrivers, dr))
                availableDrivers.push_back(dr);
    
    return availableDrivers;
}

float getBestFee(Region a, Region b, Registry reg, shared_ptr <Driver> driver)
{
    vwp <Agency> agencies = driver -> getAgencies();
    float min = INT_MAX;
    for (auto& ag : agencies)
        if (ag.lock() -> getRegionFee() < min) min = ag.lock() -> getRegionFee();

    return min;
}

float calculatePrice(pathInfo path, Registry registry)
{
    float totalPrice = -1;
    Region cur;
    Region prv;
    int time;
    for (const auto& move : path.directions)
    {
        cur = move.region;
        if (totalPrice == -1) // Start of the path
        {
            totalPrice = 0;
            prv = cur;
            time = move.time;
        }
        int fee = getBestFee(prv, cur, registry, path.driver);
        totalPrice += time * fee;
        prv = cur;
        time = move.time;
    }

    return totalPrice;
}
