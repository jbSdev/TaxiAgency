#ifndef FUNC_H
#define FUNC_H

#include "classes.h"

vsp <Driver> findDrivers(const char startingRegion, const char endingRegion, Registry registry);

float getBestFee(Region a, Region b, Registry reg, shared_ptr <Driver> driver);
float calculatePrice(pathInfo path, Registry registry);

#endif
