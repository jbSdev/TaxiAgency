#include "headers/classes.h"

Driver::Driver(string in_name, unsigned int in_license)
{
    name    = in_name;
    license = in_license;
    revenue = 0;
}

void Driver::addRegion(const char reg)
{
    if (binary_search(regions.begin(), regions.end(), reg) != true)
    {
        auto pos = lower_bound(regions.begin(), regions.end(), reg);
        regions.insert(pos, toupper(reg));
    }
}

void Driver::addAgency(weak_ptr<Agency> agency)
{
    agencies.push_back(agency);
}

void Driver::listRegions() const
{
    for (auto i : regions)
    {
        cout << i;
        if (i != regions.back())
            cout << ", ";
    }
    cout << endl;
}

void Driver::listAgencies() const
{
    for (const auto& linkedAgency : agencies)
    {
        if (auto agency = linkedAgency.lock())
        {
            cout << agency->getId();
            if (agency != agencies.back().lock())
                cout << ", ";
        }
        else
            cout << "OLD AGENCY ";
    }
    cout << endl;
}

void Driver::getInfo() const
{
    cout << "\nName:\t\t\t"             << name << endl;
    cout << "License:\t\t"              << license << endl;
    cout << "Regions of operation:\t";  listRegions();
    cout << "Revenue:\t\t"              << revenue << endl;;
    cout << "Agencies:\t\t";            listAgencies();
}

bool Driver::operatesInRegion(const char region) const
{
    return binary_search(regions.begin(), regions.end(), region);
}
