#include "headers/classes.h"
#include <algorithm>

Agency::Agency(char id, string type) : agencyType(type), id(id) {};

char Agency::getId() const { return id; }

float Agency::getRegionFee() const { return region_fee; }

float Agency::getStartingFee() const { return starting_fee; }

string Agency::getType() const { return agencyType; }

void Agency::addDriver(const shared_ptr<Driver>& driver)
{
    drivers.push_back(driver);
    if (auto self = shared_from_this())
        driver -> addAgency(self);

    driver -> appendRegions(regions, agencyType);
}

vsp <Driver> Agency::getDrivers() const { return drivers; }

vector <char> Agency::getRegions() const { return regions; }

void Agency::setRegionFee(const float fee) { region_fee = fee; }

void Agency::setStartingFee(const float fee) { starting_fee = fee; }

bool Agency::operatesInRegion(const char region) const
{
    return binary_search(regions.begin(), regions.end(), region);
}

void Agency::getInfo() const
{
    cout << "ID: "      << id       << endl;
    cout << "Revenue: " << revenue  << endl;
    cout << "Drivers:\n";
    for (auto& dr : drivers)
        cout << dr -> getName() << endl;
}

// -------------- //
// PREMIUM AGENCY //
// -------------- //

PremiumAgency::PremiumAgency(char id) : Agency(id, "premium") {};

void PremiumAgency::setPremiumFee(const float fee) { premiumFee = fee; }

float PremiumAgency::getPremiumFee() const { return premiumFee; }

float PremiumAgency::getRegionFee() const { return Agency::getRegionFee() + premiumFee; }
