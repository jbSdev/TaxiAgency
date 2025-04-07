#include "headers/main.h"

unsigned short Customer::nextId = 1;

Customer::Customer() : id(nextId++), total_expenses(0.0) {}

void Customer::addTrip(const shared_ptr <Trip>& trip)
{
    cout << "Adding trip\n";
    trip -> getInfo(); cout << endl;
    history.push_back(trip);
}

void Customer::updateExpenses(const float price) { total_expenses += price; }

int Customer::getId() const { return id; }

void Customer::getInfo() const
{
    int size = history.size() > 10 ? 10 : history.size();
    cout << "Customer: " << id << endl;
    cout << "Total expenses: " << total_expenses << endl;
    cout << "Number of rides: " << history.size() << endl;
    cout << "Last 10 rides:\n";
    for (int i = 0; i < size; i++)
    {
        cout << "  " << i + 1 << ". ";
        cout << history[i] -> getId() << endl;
    }
}

void Customer::requestRide(const char startingRegion, const char endingRegion, const Registry& registry, const Graph& graph, const string type)
{
    vsp <Driver> availableDrivers = findDrivers(startingRegion, endingRegion, registry, type);

    if (availableDrivers.size() == 0)
    {
        cout << "There are no drivers that are able to take this route.\n";
        return;
    }

    // Find the best path for each of the drivers
    vector <pathInfo> bestDrives;
    for (const auto& driver : availableDrivers)
    {
        pathInfo path = driver -> findBestPath(startingRegion, endingRegion, graph, type);
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
        path.price = calculatePrice(path, registry, type);
        if (type == "premium")
            path.time /= 2;
        cout << "Driver: " << path.driver.lock() -> getName() << endl;
        cout << "Time: " << path.time << endl;
        cout << "Price: " << path.price << endl;
        cout << "Directions: ";
        for (const auto& reg : path.directions)
            cout << reg.region << reg.time << ' ';
        cout << endl << endl;
    }

    unsigned long int input = 0;
    cout << "Select which journey do you want: ("; for (unsigned long int i = 1; i <= bestDrives.size(); i++) { cout << i; if (i != bestDrives.size()) cout << ", "; } cout << "): ";
    while (input <= 0 || input > bestDrives.size())
    {
        cin >> input;
        if (input <= 0 || input > bestDrives.size())
            cout << "Please input a valid number: ";
    }; input--;
    
    createTrip(startingRegion, endingRegion, bestDrives[input], weak_from_this(), type);
}

void Customer::requestPremiumRide(const char startingRegion, const char endingRegion, const Registry& registry, const Graph& graph)
{
    requestRide(startingRegion, endingRegion, registry, graph, "premium");
}

