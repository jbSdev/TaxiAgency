#include "headers/classes.h"

Registry::Registry() {}

void Registry::addAgency(const shared_ptr <Agency>& agency)
{
    agencyList.push_back(agency);
}

vsp <Agency> Registry::getAgencies() const
{
    return agencyList;
}
