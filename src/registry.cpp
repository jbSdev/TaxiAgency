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

void Registry::addCustomer(const shared_ptr <Customer>& customer)
{
    customerList.push_back(customer);
}

vsp <Customer> Registry::getCustomers() const
{
    return customerList;
}
