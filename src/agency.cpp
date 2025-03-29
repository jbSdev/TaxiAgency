#include "headers/classes.h"
#include <memory>

char Agency::getId() { return id; }

void Agency::addDriver(shared_ptr<Driver> driver)
{
    drivers.push_back(driver);
    driver -> addAgency(shared_from_this());
}
