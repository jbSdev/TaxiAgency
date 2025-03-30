#include "headers/classes.h"

Agency::Agency(char id) : id(id) {};

char Agency::getId() { return id; }

void Agency::addDriver(shared_ptr<Driver> driver)
{
    drivers.push_back(driver);
    if (auto self = shared_from_this())
        driver -> addAgency(self);
}

vsp <Driver> Agency::getDrivers()
{
    return drivers;
}
