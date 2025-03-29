#ifndef CLASSES_H
#define CLASSES_H

#include "includes.h"
#include <memory>

class Agency;
class Driver;
class Customer;
class Trip;

class Agency : enable_shared_from_this<Agency>
{
private:
    char                        id;
    vector <shared_ptr<Driver>> drivers;
    vector <shared_ptr<Trip>>   trips;
    vector <char>               regions;

public:
    Agency(char id) : id(id) {};

    void addDriver(shared_ptr<Driver> driver);

    char getId();
};

class Driver
{
private:
    string                      name;        // Name and surname
    unsigned int                license;
    float                       revenue;
    vector <char>               regions;
    vector <shared_ptr<Trip>>   history;
    vector <weak_ptr<Agency>>   agencies;

public:
    Driver(string name, unsigned int license);

    // setters
    template <size_t N>
    void setRegions(const char (&arr)[N])
    {
        regions.clear();
        for (auto i : arr)
            regions.push_back(toupper(i));

        sort(regions.begin(), regions.end());
    }

    void addRegion(const char reg);
    void addAgency(weak_ptr<Agency> agency);

    // getters
    void getInfo();
    void listRegions();
    void listAgencies();
};

class Customer
{
private:
    unsigned short              id;
    vector <shared_ptr <Trip>>  history;
    unsigned int                total_distance;
    float                       total_expenses;

    static unsigned short       nextId;

public:
    Customer();
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

#endif
