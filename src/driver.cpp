#include "headers/main.h"

Driver::Driver(const string in_name, const unsigned int in_license) : name(in_name), license(in_license), revenue(0.0) {};

void Driver::setRegions(const vector <Region> regs)
{
    regions.clear();
    for (const auto i : regs)
        regions.push_back(toupper(i));

    sort(regions.begin(), regions.end());
}

void Driver::setName(const string in_name) { name = in_name; }

void Driver::appendRegions(const vector <Region>& regs, const string type)
{
    for (const auto reg : regs)
        addRegion(reg, type);
}

void Driver::addRegion(const Region reg, const string type)
{
    vector <Region>& arr = (type == "normal") ? regions : premiumRegions;

    if (!binary_search(arr.begin(), arr.end(), reg))
    {
        const auto pos = lower_bound(arr.begin(), arr.end(), reg);
        arr.insert(pos, toupper(reg));
    }
}

void Driver::updateRevenue(const float price) { revenue += price; }

void Driver::addTrip(const shared_ptr <Trip>& trip) { history.push_back(trip); }

void Driver::addAgency(const weak_ptr<Agency>& agency) { agencies.push_back(agency); }

void Driver::listRegions(const string type) const
{
    const vector <Region>& arr = (type == "normal") ? regions : premiumRegions;
    for (auto i : arr)
    {
        cout << i;
        if (i != arr.back())
            cout << ", ";
    }
    cout << endl;
}

void Driver::listAgencies() const
{
    for (const auto& linkedAgency : agencies)
    {
        if (const auto agency = linkedAgency.lock())
        {
            cout << agency -> getId();
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
    cout << "Normal regions:\t";        listRegions("normal");
    cout << "Premium regions:\t";       listRegions("premium");
    cout << "Revenue:\t\t"              << revenue << endl;;
    cout << "Agencies:\t\t";            listAgencies();
}

string Driver::getName() const { return name; }

vwp <Agency> Driver::getAgencies() const { return agencies; }

bool Driver::operatesInRegion(const Region region, const string type) const
{
    const vector <Region>& arr = (type == "normal") ? regions : premiumRegions;
    return binary_search(arr.begin(), arr.end(), region);
}

// -------------------

Graph Driver::createSubmap(const Graph& graph, const string type)
{
    Graph submap;
    for (const auto& region : graph)
        if (this -> operatesInRegion(region.first, type))
            submap.insert(region);
    return submap;
}

pathInfo Driver::findBestPath(const char start, const char end, const Graph& graph, string type)
{
    const Graph submap = createSubmap(graph, type);
    map <Region, Region>    allPaths;
    map <Region, int>       pathTimes = dijkstra(submap, start, allPaths);
    list <pathSegment>      bestPath = getShortestPath(allPaths, graph, start, end);

    struct pathInfo best;
    best.directions = bestPath;
    best.time       = pathTimes[end];
    return best;
}
