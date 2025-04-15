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
    const string    agencyType;
    const char      id;
    vsp <Driver>    drivers;
    float           revenue = 0.0;
    vector <Region> regions;
    float           starting_fee;
    float           region_fee;

public:
    Agency(char id, string type = "normal");
    virtual ~Agency() = default;

    // setters
    void addDriver(const shared_ptr<Driver>& driver);

    template <size_t N>
    void setRegions     (const Region (&arr)[N]);
    void setRegionFee   (const float fee);
    void setStartingFee (const float fee);
    void updateRevenue  (const float price);

    // getters
    char            getId()         const;
    string          getType()       const;
    virtual float   getRegionFee()  const;
    float           getStartingFee()const;
    vsp <Driver>    getDrivers()    const;
    vector <char>   getRegions()    const;
    void            getInfo()       const;

    // functions
    bool operatesInRegion(const char region) const;
};

class PremiumAgency : public Agency
{
private:
    float premiumFee;

public:
    PremiumAgency(const char id);

    void  setPremiumFee(const float fee);

    float getPremiumFee() const;
    float getRegionFee()  const override;
};

class Driver
{
private:
    string              name;        // Name and surname
    const unsigned int  license;
    float               revenue = 0.0;
    vector <Region>     regions;
    vector <Region>     premiumRegions;
    vsp <Trip>          history;
    vwp <Agency>        agencies;

public:
    Driver(const string name, const unsigned int license);

    // setters
    void setRegions(const vector <char> regions);
    void setName(const string name);

    void addRegion      (const char reg, const string type = "normal");
    void addAgency      (const weak_ptr<Agency>& agency);
    void appendRegions  (const vector <char>& regs, const string type = "normal");
    void addTrip        (const shared_ptr <Trip>& trip);
    void updateRevenue  (const float price);

    // getters
    void         getInfo()                  const;
    void         listRegions(string type)   const;
    void         listAgencies()             const;
    string       getName()                  const;
    vwp <Agency> getAgencies()              const;
    template <typename T>
    T            getBestStartingProp(const Region region, const string type) const;


    // functions
    bool        operatesInRegion(const char region, const string type) const;
    Graph       createSubmap    (const Graph& graph, const string type);
    pathInfo    findBestPath    (const char start, const char end, const Graph& graph, const string type);
};

class Customer : public enable_shared_from_this <Customer>
{
private:
    const unsigned short    id;
    vsp <Trip>              history;
    float                   total_expenses = 0.0;

    static unsigned short       nextId;

public:
    Customer();

    void addTrip            (const shared_ptr <Trip>& trip);
    void updateExpenses     (const float price);
    void requestRide        (const char startingRegion, const char endingRegion,
                             const Registry& registry, const Graph& graph, const string type = "normal");
    void requestPremiumRide (const char startingRegion, const char endingRegion,
                             const Registry& registry, const Graph& graph);

    void getInfo()  const;
    int  getId()    const ;
};

class Trip
{
private:
    const int             id;
    const Region          origin, destination;
    const float           price;
    weak_ptr <Driver>     driver;
    weak_ptr <Customer>   customer;
    vwp <Agency>          agencies;
    const string          type;

    static unsigned short           nextId;

public:
    Trip(const Region               origin,
         const Region               destination,
               float                price,
               weak_ptr <Driver>    driver,
               weak_ptr <Customer>  customer,
               vwp <Agency>         agency,
         const string               type);

    ~Trip();

    int                 getId()     const;
    void                getInfo()   const;
    weak_ptr <Driver>   getDriver() const;
    Region              getStart()  const;
    Region              getEnd()    const;
};

class Registry
{
private:
    vsp <Agency> agencyList;
    vsp <Customer> customerList;

public:
    Registry();
    void addAgency(const shared_ptr <Agency>& agency);
    vsp <Agency> getAgencies() const;

    void addCustomer(const shared_ptr <Customer>& customer);
    vsp <Customer> getCustomers() const;
};

struct pathInfo
{
    weak_ptr <Driver>       driver;
    list <pathSegment>      directions;
    int                     time;
    float                   price;
};

template <size_t N>
void Agency::setRegions(const Region (&arr)[N])
{
    regions.clear();
    for (auto i : arr)
        if (isalpha(i))
            regions.push_back(toupper(i));

    sort(regions.begin(), regions.end());

    vector <Region> vec;
    for (auto i : arr)
        vec.push_back(i);

    for (auto dr : drivers)
        dr->appendRegions(vec, agencyType);
}

template <typename T>
T Driver::getBestStartingProp(const Region region, const string type) const
{
    weak_ptr <Agency> agency;
    float min = FLT_MAX;
    for (const auto& ag : agencies)
    {
        if (ag.lock() -> getStartingFee() < min && ag.lock() -> getType() == type && ag.lock() -> operatesInRegion(region))
        {
            min = ag.lock() -> getStartingFee();
            agency = ag;
        }
    }
    if constexpr (is_same_v<T, float>)
        return min;
    else
        return agency;
}

#endif
