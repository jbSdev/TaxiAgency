#include "headers/classes.h"

Agency::Agency(char id) : id(id) {};

char Agency::getId() const { return id; }

float Agency::getRegionFee() const { return region_fee; }

void Agency::addDriver(shared_ptr<Driver> driver)
{
    drivers.push_back(driver);
    if (auto self = shared_from_this())
        driver -> addAgency(self);

    driver -> appendRegions(regions);
}

vsp <Driver> Agency::getDrivers() const
{
    return drivers;
}

vector <char> Agency::getRegions() const
{
    return regions;
}

void Agency::setRegionFee(const float fee)
{
    region_fee = fee;
}
