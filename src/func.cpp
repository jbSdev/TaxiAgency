#include "headers/main.h"

void clrscr()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void p2c()  // press to continue
{
    cout << "Press any key to continue...\n" << std::flush;
#ifdef _WIN32
    _getch();
#else
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    char ch;
    read(STDIN_FILENO, &ch, 1);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif
}

void wait(const int ms)
{
    this_thread::sleep_for(chrono::milliseconds(ms));
}

template <typename Container, typename T> 
bool isIn(const Container& arr, const T& val)
{
    for (const auto& i : arr)
        if (i == val) return true;
    return false;
}

vsp <Driver> findDrivers(const char startingRegion, const char endingRegion, const Registry& registry, const string type)
{
    vsp <Driver> availableDrivers;
    for (const auto &ag : registry.getAgencies())
    {
        if (type == "premium" && ag -> getType() != "premium")
            continue;

        if (type == "normal"  && ag -> getType() != "normal")
            continue;

        for (const auto &dr : ag -> getDrivers())
            if (dr -> operatesInRegion(startingRegion, type)
             && dr -> operatesInRegion(endingRegion, type)
             && !isIn(availableDrivers, dr))
                availableDrivers.push_back(dr);
    }
    
    return availableDrivers;
}

float calculatePrice(pathInfo& path, const Registry& registry, const string type)
{
    float   totalPrice = -1;
    Region  cur;
    Region  prv;
    Time    time;

    for (const auto& move : path.directions)
    {
        cur = move.region;
        if (totalPrice == -1) // Start of the path
        {
            totalPrice = 0.0;
            prv = cur;
            time = move.time;
            continue;
        }
        time = move.time;
        totalPrice += time * getBestRegionProp<Time>(prv, cur, path.driver.lock(), type);
        prv = cur;
    }
    totalPrice += path.driver.lock() -> getBestStartingProp<float>(path.directions.front().region, type);
    return totalPrice;
}

vwp <Agency> getUsedAgencies(const pathInfo& path, const string type)
{
    vwp <Agency> agencies;
    weak_ptr <Agency> agn;
    Region cur;
    Region prv;

    for (const auto& move : path.directions)
    {
        cur = move.region;
        if (agencies.size() == 0)
            agn = path.driver.lock() -> getBestStartingProp<weak_ptr <Agency>>(path.directions.front().region, type);
        else
            agn = getBestRegionProp<weak_ptr <Agency>>(prv, cur, path.driver.lock(), type);

        if (!binary_search(agencies.begin(), agencies.end(), agn,
                           [](const weak_ptr <Agency>& lhs, const weak_ptr <Agency>& rhs) { return lhs.lock() -> getId() < rhs.lock() -> getId(); }))
        {
            const auto pos = lower_bound(agencies.begin(), agencies.end(), agn,
                            [](const weak_ptr<Agency>& lhs, const weak_ptr<Agency>& rhs) { return lhs.lock() < rhs.lock(); } );
            agencies.insert(pos, agn);
        }
        prv = cur;
    }
    return agencies;
}

void createTrip(const Region start, const Region end, const pathInfo& path, weak_ptr <Customer> customer, const string type)
{
    const float                price    = path.price;
    const weak_ptr <Driver>&   driver   = path.driver;
    const vwp <Agency>&        agencies = getUsedAgencies(path, type);
    const auto journey                  = make_shared <Trip> (start, end, price, driver, customer, agencies, type);

    driver.lock()   -> addTrip(journey);
    driver.lock()   -> updateRevenue(price / 2);
    customer.lock() -> addTrip(journey);
    customer.lock() -> updateExpenses(price);
    for (auto& ag : agencies)
        ag.lock() -> updateRevenue((price / 2) / agencies.size());
    return;
}
