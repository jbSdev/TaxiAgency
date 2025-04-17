#include "headers/main.h"
#include <termios.h>
#include <unistd.h>

inline int adminPanel   (Registry& reg, Graph& map, int& index);
inline int customerPanel(Registry& reg, Graph& map, int& index);

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
cout << "Press any key to continue..." << std::flush;
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

template <typename T>
inline void getVal(T& input)
{
    while (true)
    {
        cin.clear();
        cin >> input;
        
        if (!cin.fail())
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }
        // Invalid input
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please try again: ";
    }

}

inline vector <unsigned char> getCharLine()
{
    string input;
    vector <unsigned char> temp;
    cin.clear();

    while (temp.size() == 0 || temp.size() > 25)
    {
        cin.clear();
        temp.clear();
        getline(cin, input);

        for (auto ch : input)
            if (isalpha(ch))
                temp.push_back(toupper(ch));

        if (temp.size() == 0)
            cout << "Wrong input. No data found. Please try again.\n";
        else if (temp.size() > 25)
            cout << "Too much data. Please try again.\n";
    }
    return temp;
}

inline void createAgency(Registry& reg)
{
    char id = '.';
    cout << "Please insert an ID for the agency. It should be a character.\n";
    while (!isalpha(id))
    {
        getVal(id);
        if (!isalpha(id))
            cout << "Please input a valid character.\n";
        
        id = toupper(id);

        for (auto& ag : reg.getAgencies())
            if (ag -> getId() == id)
                id = '.';           // agency already exists

        if (id == '.')
            cout << "The agency with given ID already exists!\n";
    }
    cout << "\nNow let's select the regions in which the agency will operate:\n";
    cout << "This is the city map:\n";
    printMap();

    vector <unsigned char> temp = getCharLine();
    char regions[25] = {0};
    copy(temp.begin(), temp.end(), regions);

    float regionFee = 0, startingFee = 0;
    cout << "Set the starting fee: ";
    getVal(startingFee);            // agency already exists
    cout << "Set the region fee: ";
    getVal(regionFee);

    auto agency = make_shared<Agency>(id);
    reg.addAgency           (agency);
    agency -> setRegions    (regions);
    agency -> setStartingFee(startingFee);
    agency -> setRegionFee  (regionFee);
    
    cout << "Agency " << agency -> getId() << " created!\n";
    p2c();
    return;
}

inline void updateRegions(shared_ptr <Agency>& agn)
{
    cout << "Current regions of operation:\n";
    vector <Region> regs = agn -> getRegions();
    cout << "\nMap of the city:\n";
    printMap();
    vector <unsigned char> update = getCharLine();
    char copied[25];
    copy(update.begin(), update.end(), copied);
    agn -> setRegions(copied);
    cout << "Regions updated!\n";
    wait(500);
    return;
}

inline void updateStartingFee(shared_ptr <Agency>& agn)
{
    cout << "Current starting fee: " << agn -> getStartingFee() << endl;
    float input = 0;
    cout << "Please input the new starting fee: ";
    while (input <= 0)
    {
        getVal(input);
        if (input < 0)
            cout << "The fee cannot be negative. Please try again: ";
    }
    agn -> setStartingFee(input);
    cout << "Starting fee updated!\n";
    p2c();
    return;
}

inline void updateRegionFee(shared_ptr <Agency>& agn)
{
    cout << "Current region fee: " << agn -> getRegionFee() << endl;
    float input = 0;
    cout << "Please input the new region fee: ";
    while (input <= 0)
    {
        getVal(input);
        if (input < 0)
            cout << "The fee cannot be negative. Please try again: ";
    }
    agn -> setRegionFee(input);
    cout << "Region fee updated!\n";
    p2c();
    return;
}

inline void updatePremiumFee(shared_ptr <Agency>& agn)
{
    shared_ptr <PremiumAgency> pagn = dynamic_pointer_cast <PremiumAgency>(agn);
    cout << "Current premium fee: " << pagn -> getPremiumFee() << endl;
    float input = 0;
    cout << "Please input the new premium fee: ";
    while (input <= 0)
    {
        getVal(input);
        if (input < 0)
            cout << "The fee cannot be negative. Please try again: ";
    }
    pagn -> setPremiumFee(input);
    cout << "Premium fee updated!\n";
    pagn.reset();
    p2c();
    return;
}

inline void updateAgency(Registry& reg)
{
    clrscr();
    vsp <Agency> agencies = reg.getAgencies();
    int size = agencies.size();
    cout << "Available agencies: ";
    for (int i = 0; i <= size; i++)
        cout << i + 1 << ". " << agencies[i] -> getId() << " (" << agencies[i] -> getType() << ")\n";

    cout << "\nWhich agency would you like to update: ";
    int input = 0;
    while (input <= 0 || input > size)
    {
        getVal(input);
        if (input <= 0 || input > size)
            cout << "Invalid input. Please try again: ";
    }

    shared_ptr <Agency>& agn = agencies[input - 1];
    cout << "Selected agency " << agn -> getId() << endl;
    wait(500);
    clrscr();

    cout << "Selected agency " << agn -> getId() << endl;
    cout << "What would you like to update?\n";
    cout << "  1. Operating regions\n";
    cout << "  2. Starting fee\n";
    cout << "  3. Region fee\n";
    if (agn -> getType() == "premium")
        cout << "  4. Premium fee\n";

    input = 0;
    while (input <= 0 || input > ((agn -> getType() == "premium") ? 4 : 3))
        getVal(input);

    switch(input)
    {
        case 1:
            updateRegions(agn);     break;
        case 2:
            updateStartingFee(agn); break;
        case 3:
            updateRegionFee(agn);   break;
        case 4:
            updatePremiumFee(agn);  break;
    }
    return;
}

inline void createDriver(Registry& reg)
{
    clrscr();
    cout << "Creating a driver\n\n";
    string name;
    int license;

    cout << "Driver's name: ";
    getVal(name);

    cout << "Driver's license number (only digits [int]): ";
    getVal(license);

    cout << "Available agencies:\n";
    for (auto& ag : reg.getAgencies())
         cout << ag -> getId() << ' ';
    cout << endl;

    auto driver = make_shared <Driver>(name, license);
    cout << "Input driver's agencies:\n";
    bool ch_check = 0;
    int sum = -1;
    vector <unsigned char> newAgencies;
    while (sum != newAgencies.size())   // if every inputted agency is real
    {
        sum = 0;
        newAgencies = getCharLine();
        for (auto ch : newAgencies)
        {
            ch_check = 0;
            for (auto& ag : reg.getAgencies())
                if (ch == ag -> getId()) ch_check = 1;

            if (ch_check == 1)          // agency is real
                sum++;
        }
        if (sum != newAgencies.size())
            cout << "Some of the inputted agencies do not exist. Please try again\n";
    }

    for (auto& ag : reg.getAgencies())
        for (unsigned long int i = 0; i < newAgencies.size(); i++)
            if (ag -> getId() == newAgencies[i])
                ag -> addDriver(driver);

    cout << "Driver created!\n";
    p2c();
    return;
}

inline void updateDriverName(shared_ptr <Driver> drv)
{
    string name, oldname = drv -> getName();
    cout << "Driver's new name: ";
    getVal(name);
    drv -> setName(name);
    cout << "Updated driver's name from " << oldname << " to " << drv -> getName();
    p2c();
    return;
}

inline void updateDriverAgencies(shared_ptr <Driver> drv, Registry& reg)
{
    cout << "Current driver agencies:\n  ";
    for (auto& ag : drv -> getAgencies())
        cout << ag.lock() -> getId() << ' ';
    cout << endl;

    cout << "Available agencies:\n  ";
    for (auto& ag : reg.getAgencies())
        cout << ag -> getId() << ' ';
    cout << endl;

    cout << "List new agencies:\n";
    vector <unsigned char> newAgencies = getCharLine();

    for (auto& ag : reg.getAgencies())
        for (auto ch : newAgencies)
            if (ch == ag -> getId())
                ag -> addDriver(drv);

    cout << "Driver's agencies updated!\n";
    p2c();
    return;
}

inline void updateDriver(Registry& reg)
{
    clrscr();
    vsp <Driver> drivers;
    for (auto& ag : reg.getAgencies())
        for (auto& dr : ag -> getDrivers())
            if (!isIn(drivers, dr))
                drivers.push_back(dr);
    cout << "Available drivers: \n";
    for (unsigned long int i = 0; i < drivers.size(); i++)
        cout << i + 1 << ". " << drivers[i] -> getName() << endl;

    unsigned long int input = 0;
    cout << "Which driver would you like to update?\n";
    while (input <= 0 || input > drivers.size())
    {
        getVal(input);
        if (input <= 0 || input > drivers.size())
            cout << "Invalid input. Please try again: ";
    }
    auto drv = drivers[input - 1];
    cout << "Selected driver " << drv -> getName() << endl;
    wait(500);
    clrscr();
    cout << "What do you want to update:\n";
    cout << "  1. Name\n";
    cout << "  2. Agencies\n";
    input = 0;
    while (input != 1 && input != 2)
    {
        getVal(input);
        if (input != 1 && input != 2)
            cout << "Invalid input. Please try again: ";
    }
    switch(input)
    {
        case 1:
            updateDriverName(drv); break;
        case 2:
            updateDriverAgencies(drv, reg); break;
    }
}

inline void getAgencyData(Registry& reg)
{
    clrscr();
    vsp <Agency> agencies = reg.getAgencies();

    if (agencies.size() == 0)
    {
        cout << "There are no available agencies.\n";
        p2c();
        return;
    }

    cout << "Available agencies:\n";
    for (auto& ag : agencies)
        cout << ag -> getId() << ' ';
    cout << endl;
    char input;
    cout << "Select agency: ";
    while (input < 'A' || input > 'Z')
    {
        getVal(input);
        if (input < 'A' || input > 'Z')
            cout << "Invalid input. Please try again: ";
        bool check = 0;
        for (auto& ag : agencies)
             if (ag -> getId() == input)
                check = 1;
        if (check == 0)
        {
            cout << "Given agency doesn't exist. Please try again: ";
            input = '.';
        }
    }
    for (auto& ag : reg.getAgencies())
    {
        if (ag -> getId() == input)
        {
            ag -> getInfo();
            break;
        }
    }
    p2c();
    return;
}

inline void getDriverData(Registry& reg)
{
    clrscr();
    vsp <Driver> drivers;
    for (auto& ag : reg.getAgencies())
        for (auto& dr : ag -> getDrivers())
            if (!isIn(drivers, dr))
                drivers.push_back(dr);

    if (drivers.size() == 0)
    {
        cout << "There are no available drivers.\n";
        p2c();
        return;
    }

    cout << "Available drivers:\n";
    for (unsigned long int i = 0; i < drivers.size(); i++)
        cout << i + 1 << ". " << drivers[i] -> getName() << endl;

    cout << "Select the driver to get the info about: ";
    unsigned long int input = 0;
    while (input <= 0 || input > drivers.size())
    {
        getVal(input);
        if (input <= 0 || input > drivers.size())
            cout << "Invalid input. Please try again: ";
    }

    cout << "Selected driver's data:\n";
    drivers[input - 1] -> getInfo();

    p2c();
    return;
}

inline int adminPanel(Registry& reg, Graph& map, int& index)
{
    clrscr();
    cout << "Welcome to the ADMIN PANEL\n\n";
    cout << "In here, you can:\n";
    cout << "  1. Create agencies\n";
    cout << "  2. Update agency data\n";
    cout << "  3. Create drivers\n";
    cout << "  4. Update driver data\n";
    cout << "  5. Get agency data\n";
    cout << "  6. Get driver data\n";
    cout << "  9. Switch to customer panel\n";
    cout << "  0. Exit the program\n\n";
    cout << "Please input the number corresponding to the wanted action: ";
    int in;
    /*
     * cin.clear();
     * cin.ignore(numeric_limits<streamsize>::max(), '\n');
     */
    while (true)
    {
        getVal(in);
        switch (in)
        {
            case 1:
                createAgency(reg);  return 0;
            case 2:
                updateAgency(reg);  return 0;
            case 3:
                createDriver(reg);  return 0;
            case 4:
                updateDriver(reg);  return 0;
            case 5:
                getAgencyData(reg); return 0;
            case 6:
                getDriverData(reg); return 0;
            case 9:
                // customerPanel(reg, map, index); return 0;
                return 1;
            case 0:
                return -1;
            default:
                cout << "Invalid input. Please try again: ";
        }
    }
    return 0;
}

void getRide(Registry& reg, shared_ptr <Customer>& cst, Graph& map)
{
    clrscr();
    char start = '.', end = '.';
    cout << "Map of the city:\n";
    printMap();

    cout << "Where do you want to start the journey: ";
    while (start < 'A' || start > 'Y')      // Regions go A...Y
    {
        getVal(start);
        start = toupper(start);
        if (start < 'A' || start > 'Y')
            cout << "Incorrect input. Please try again: ";
    }
    cout << "Where do you want to end the journey: ";
    while (end < 'A' || end > 'Y')
    {
        getVal(end);
        end = (toupper(end));
        if (end < 'A' || end > 'Y')
            cout << "Incorrect input. Please try again: ";
    }

    cout << "What type of drive do you want to request?\n";
    cout << "  1. Normal\n";
    cout << "  2. Premium\n";
    int input = 0;
    while (input != 1 && input != 2)
    {
        getVal(input);
        if (input != 1 && input != 2)
            cout << "Incorrect input. Please try again.\n";
    }
    if (input == 1)
        cst -> requestRide(start, end, reg, map);
    else
        cst -> requestPremiumRide(start, end, reg, map);

    cout << "Ride created!\n";
    p2c();
    return;
}

void switchCustomer(Registry& reg, int& index)
{
    clrscr();
    cout << "Available customers";
    vsp <Customer> customers = reg.getCustomers();
    for (auto& cst : customers)
        cout << "  " << cst -> getId() << endl;

    unsigned long int input = 0;
    cout << "Select which customer do you want to switch to:\n";
    while (input <= 0 || input > customers.size())
    {
        getVal(input);
        if (input <= 0 || input > customers.size())
            cout << "Incorrect input. Please try again: ";
    }
    index = input - 1;
    return;
}

void createNewCustomer(Registry& reg, int& index)
{
    cout << "Creating a new customer with id: ";
    auto customer = make_shared <Customer> ();
    reg.addCustomer(customer);
    cout << customer -> getId();
    index = customer -> getId() - 1;
    cout << "Switching to the newly created customer...\n";
    wait(750);
    switchCustomer(reg, index);
    return;
}

void getCustomerInfo(shared_ptr <Customer>& cst)
{
    clrscr();
    cst -> getInfo();
    p2c();
}

int customerPanel(Registry& reg, Graph& map, int& index)
{
    clrscr();

    cout << "Welcome to the customer panel!\n";
    cout << "Here, you can request rides as a customer.\n";
    cout << "By default, you have 3 customers available,\n";
    cout << "but you can create more at any time you want\n";
    cout << "Using the menu below:\n\n";
    cout << "  1. Request a ride\n";
    cout << "  2. Get info about the customer\n";
    cout << "  3. Switch the customer\n";
    cout << "  4. Create a new customer\n";
    cout << "  9. Switch to admin panel\n";
    cout << "  0. Exit program\n\n";

    auto cst = reg.getCustomers()[index];
    cout << "You're using the customer " << cst -> getId() << "\n\n";

    cout << "Select the action you want to make: ";
    int in = -1;
    while (true)
    {
        getVal(in);
        if (cin.fail())
        {
            cout << "Invalid input. Please try again: ";
            continue;
        }

        switch (in)
        {
            case 1:
                getRide(reg, cst, map);         return 1;
            case 2:
                getCustomerInfo(cst);           return 1;
            case 3:
                switchCustomer(reg, index);     return 1;
            case 4:
                createNewCustomer(reg, index);  return 1;
            case 9:
                // adminPanel(reg, map, index);    return 1;
                return 0;
            case 0:
                return -1;
            default:
                cout << "Invalid input. Please try again: ";
        }

    }
    return 1;
}

void menu(Registry& registry, Graph& map)
{
    string input1, input2, input3;
    cout << "/--------------------------\\\n";
    cout << "| EOOP Preliminary Project |\n";
    cout << "|  Made by: Antoni Jesien  |\n";
    cout << "|  336969 II sem. CompSci  |\n";
    cout << "|    Topic: Taxi Agency    |\n";
    cout << "\\--------------------------/\n";
    p2c();
    clrscr();
    int index = 0;
    int state = 0;
    while (true)
    {
        if      (state == 0)
            state = adminPanel(registry, map, index);
        else if (state == 1)
            state = customerPanel(registry, map, index);
        else if (state == -1)
            return;
    }
}
