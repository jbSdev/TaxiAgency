#include "headers/classes.h"

void Registry::addAgency(shared_ptr <Agency> agency)
{
    agencyList.push_back(agency);
}

vsp <Agency> Registry::getAgencies()
{
    return agencyList;
}
