#ifndef CLASSES_H
#define CLASSES_H

#include "includes.h"

class Agency;
class Driver;
class Customer;
class Trip;
class Registry;
struct pathInfo;

class Agency : public enable_shared_from_this <Agency>
{
private:
    char            id;
    vsp <Driver>    drivers;
    vsp <Trip>      trips;
    vector <char>   regions;
    float           starting_fee;
    float           region_fee;

public:
    Agency(char id);

    // setters
    void addDriver(shared_ptr<Driver> driver);

    template <size_t N>
    void setRegions(const char (&arr)[N]);
    void setRegionFee(const float fee);

    // getters
    char getId() const;
    float getRegionFee() const;
    vsp <Driver> getDrivers() const;
    vector <char> getRegions() const;
};

class Driver
{
private:
    string          name;        // Name and surname
    unsigned int    license;
    float           revenue;
    vector <char>   regions;
    vsp <Trip>      history;
    vwp <Agency>    agencies;

public:
    Driver(string name, unsigned int license);

    // setters
    void setRegions(vector <char> regions);

    void addRegion(const char reg);
    void addAgency(weak_ptr<Agency> agency);
    void appendRegions(vector <char> regs);

    // getters
    void getInfo() const;
    string getName() const;
    vwp <Agency> getAgencies() const;
    void listRegions() const;
    void listAgencies() const;

    bool operatesInRegion(const char region) const;

    // functions
    Graph createSubmap(const Graph& graph);
    pathInfo findBestPath(const char start, const char end, const Graph graph);
};

class Customer
{
private:
    unsigned short  id;
    vsp <Trip>      history;
    unsigned int    total_distance;
    float           total_expenses;

    static unsigned short       nextId;

public:
    Customer();

    void requestRide(const char startingRegion, const char endingRegion, Registry registry, const Graph graph);
};

class Trip
{
private:
    string      id;
    char        origin, destination;
    float       price;
    Driver*     driver;
    Customer*   customer;
    Agency*     agency;

public:
    Trip(const char          origin,
         const char          destination,
         weak_ptr <Customer> customer,
         weak_ptr <Driver>   driver,
         weak_ptr <Agency>   agency);
    // Calculates the price on its own, using regions * agency price

    ~Trip();
};

class Registry
{
private:
    vsp <Agency> agencyList;
public:
    void addAgency(shared_ptr <Agency> agency);
    vsp <Agency> getAgencies();
};

struct pathInfo
{
    shared_ptr <Driver> driver;
    list <pathSegment>  directions;
    int                 time;
    float               price;
};

template <size_t N>
void Agency::setRegions(const char (&arr)[N])
{
    regions.clear();
    for (auto i : arr)
        regions.push_back(toupper(i));

    sort(regions.begin(), regions.end());

    vector <char> vec;
    for (auto i : arr)
        vec.push_back(i);
    for (auto dr : drivers)
        dr->appendRegions(vec);
}

#endif
