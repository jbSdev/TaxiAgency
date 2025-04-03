#include "headers/classes.h"
#include "headers/func.h"

unsigned short Customer::nextId = 1;

Customer::Customer()
{
    id              = nextId++;
    total_distance  = 0;
    total_expenses  = 0;
}

void Customer::requestRide(const char startingRegion, const char endingRegion, const Registry registry, const Graph graph)
{
    vsp <Driver> availableDrivers = findDrivers(startingRegion, endingRegion,  registry);

    // Find the best path for each of the drivers
    vector <pathInfo> bestDrives;
    for (const auto& driver : availableDrivers)
    {
        pathInfo path = driver -> findBestPath(startingRegion, endingRegion, graph);
        path.driver = driver;
        bestDrives.push_back(path);
    }

    // Sort the best paths based on time
    sort(bestDrives.begin(), bestDrives.end(), [](const pathInfo& a, const pathInfo& b) { return a.time < b.time; });

    // Get the best 3
    if (bestDrives.size() > 3)
        bestDrives.resize(3);

    cout << "Found best drives:\n";
    for (auto& path : bestDrives)
    {
        path.price = calculatePrice(path, registry);
        // cout << "Driver: " << path.driver -> getName() << endl;
        path.driver -> getInfo();
        cout << "Time: " << path.time << endl;
        cout << "Price: " << path.price << endl;
        cout << "Directions: ";
        for (const auto& reg : path.directions)
            cout << reg.region << ' ';
        cout << endl << endl;
    }
}
