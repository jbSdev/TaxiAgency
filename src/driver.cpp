#include "headers/includes.h"
#include "headers/main.h"
#include "headers/map.h"

Driver::Driver(string in_name, unsigned int in_license)
{
    name    = in_name;
    license = in_license;
    revenue = 0;
}

void Driver::setRegions(vector <char> regs)
{
    regions.clear();
    for (auto i : regs)
        regions.push_back(toupper(i));

    sort(regions.begin(), regions.end());
}

void Driver::appendRegions(vector <char> regs)
{
    for (const auto reg : regs)
        addRegion(reg);
}

void Driver::addRegion(const char reg)
{
    // if (!isIn(regions, reg))
    if (!binary_search(regions.begin(), regions.end(), reg))
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

vwp <Agency> Driver::getAgencies() const
{
    return agencies;
}

bool Driver::operatesInRegion(const char region) const
{
    return binary_search(regions.begin(), regions.end(), region);
}

// -------------------
Graph Driver::createSubmap(const Graph& graph)
{
    Graph submap;
    for (const auto& region : graph)
        if (this -> operatesInRegion(region.first))
            submap.insert(region);
    return submap;
}

pathInfo Driver::findBestPath(const char start, const char end, const Graph graph)
{
    Graph submap = createSubmap(graph);
    map <Region, Region>    allPaths;
    map <Region, int>       pathTimes = dijkstra(submap, start, allPaths);
    list <pathSegment>      bestPath = getShortestPath(allPaths, graph, start, end);

    struct pathInfo best;
    best.directions = bestPath;
    best.time       = pathTimes[end];
    return best;
}

Graph createSubmap(const Graph& map, const Driver& driver)
{
    Graph submap;
    for (const auto& entry : map)
        if (driver.operatesInRegion(entry.first))
            submap.insert(entry);

    return submap;
}
