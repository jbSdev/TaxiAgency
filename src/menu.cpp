#include "headers/classes.h"
#include "headers/main.h"
#include <chrono>
#include <memory>

inline int adminPanel   (Registry& reg);
inline int customerPanel(Registry& reg);

void clrscr()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void wait(const int ms)
{
    this_thread::sleep_for(chrono::milliseconds(ms));
}

template <typename T>
inline void getVal(T& input)
{
    cin >> input;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please try again: ";
    }
    return;
}

inline vector <Region> getCharLine()
{
    string input;
    vector <Region> temp;

    while (temp.size() == 0 || temp.size() > 25)
    {
        cout << "Please insert the regions in a row: ";
        getline(cin, input);

        stringstream ss(input);
        Region reg;
        while (ss >> reg)
        {
            if ((reg >= 'A' && reg <= 'Z') || (reg >= 'a' && reg <= 'z'))
                temp.push_back(reg);
        }
        if (temp.size() == 0)
            cout << "Wrong input. The regions are empty. Please try again.\n";
        else if (temp.size() > 25)
            cout << "Too many regions. Please try again.\n";
    }
    return temp;
}

inline void createAgency(Registry& reg)
{
    char id;
    cout << "Please insert an ID for the agency. It should be an uppercase character.\n";
    while (id < 'A' || id > 'Z')
    {
        id = getchar();
        if (id < 'A' || id > 'Z')
            cout << "Please input a valid character.\n";
    }
    cout << "\nNow let's select the regions in which the agency will operate:\n";
    cout << "This is the city map:\n";
    printMap();

    vector <Region> temp = getCharLine();
    char regions[25];
    copy(temp.begin(), temp.end(), regions);

    float regionFee = 0, startingFee = 0;
    while (startingFee <= 0)
    {
        cout << "Set the starting fee: ";
        cin >> startingFee;
        if (startingFee <= 0)
            cout << "Invalid input. Please try again.\n";
    }
    
    while (regionFee <= 0)
    {
        cout << "Set the region fee: ";
        cin >> regionFee;
        if (regionFee <= 0)
            cout << "Invalid input. Please try again.\n";
    }

    auto agency = make_shared<Agency>(id);
    reg.addAgency      (agency);
    agency -> setRegions    (regions);
    agency -> setStartingFee(startingFee);
    agency -> setRegionFee  (regionFee);
    
    cout << "Agency " << agency -> getId() << " created!\n";
    wait(500);
    return;
}

inline void updateRegions(shared_ptr <Agency>& agn)
{
    cout << "Current regions of operation:\n";
    vector <Region> regs = agn -> getRegions();
    cout << "\nMap of the city:\n";
    printMap();
    vector <Region> update = getCharLine();
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
    float input;
    cout << "Please input the new starting fee: ";
    while (input <= 0)
    {
        getVal(input);
        if (input < 0)
            cout << "The fee cannot be negative. Please try again: ";
    }
    agn -> setStartingFee(input);
    cout << "Starting fee updated!\n";
    wait(500);
    return;
}

inline void updateRegionFee(shared_ptr <Agency>& agn)
{
    cout << "Current region fee: " << agn -> getRegionFee() << endl;
    float input;
    cout << "Please input the new region fee: ";
    while (input <= 0)
    {
        getVal(input);
        if (input < 0)
            cout << "The fee cannot be negative. Please try again: ";
    }
    agn -> setRegionFee(input);
    cout << "Region fee updated!\n";
    wait(500);
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
    wait(500);
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
    cout << endl;
    cout << "Which agency would you like to update: ";
    int input;
    while (input <= 0 || input > size)
        getVal(input);

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
    cout << "Driver's agencies: ";
    vector <char> newAgencies = getCharLine();
    for (auto& ag : reg.getAgencies())
        for (unsigned long int i = 0; i < newAgencies.size(); i++)
            if (ag -> getId() == newAgencies[i])
                ag -> addDriver(driver);

    cout << "Driver created!\n";
    wait(500);
}

inline void updateDriverName(shared_ptr <Driver> drv)
{
    string name, oldname = drv -> getName();
    cout << "Driver's new name: ";
    getVal(name);
    drv -> setName(name);
    cout << "Updated driver's name from " << oldname << " to " << drv -> getName();
    wait(500);
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
    vector <char> newAgencies = getCharLine();
    for (auto& ag : reg.getAgencies())
        for (auto ch : newAgencies)
            if (ch == ag -> getId())
                ag -> addDriver(drv);

    cout << "Driver's agencies updated!\n";
    wait(500);
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
    while (input != 1 || input != 2)
    {
        getVal(input);
        if (input != 1 || input != 2)
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
    cout << "Available agencies:\n";
    vsp <Agency> agencies = reg.getAgencies();
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
    cout << "Click to continue\n";
    getchar();
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

    cout << "Available drivers:\n";
    for (unsigned long int i = 0; i < drivers.size(); i++)
        cout << i + 1 << drivers[i] -> getName() << endl;

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
    cout << "Click to continue\n";
    getchar();
    return;
}

inline int adminPanel(Registry& reg)
{
    cout << "Welcome to the ADMIN PANEL\n\n";
    cout << "In here, you can:\n";
    cout << "  1. Create agencies\n";
    cout << "  2. Update agency data\n";
    cout << "  3. Create drivers\n";
    cout << "  4. Update driver data\n";
    cout << "  5. Get agency data\n";
    cout << "  6. Get driver data\n";
    cout << "  9. Exit the program\n";
    cout << "  0. Switch to customer panel\n\n";
    cout << "Please input the number corresponding to the wanted action: ";
    int in = -1;
    while (!(in >= 1 && in <= 6) && in != 9 && in != 0)
    {
        getVal(in);
        if (!(in >= 1 && in <= 6) && in != 9 && in != 0)
            cout << "Invalid input. Please try again: ";
    }
    switch (in)
    {
        case 1:
            createAgency(reg);  break;
        case 2:
            updateAgency(reg);  break;
        case 3:
            createDriver(reg);  break;
        case 4:
            updateDriver(reg);  break;
        case 5:
            getAgencyData(reg); break;
        case 6:
            getDriverData(reg); break;
        case 9:
            // customerPanel(reg); break;
        case 0:
            return 1;
    }
    return 0;
}

void menu(Registry& registry)
{
    string input1, input2, input3;
    cout << "/--------------------------\\\n";
    cout << "| EOOP Preliminary Project |\n";
    cout << "|  Made by: Antoni Jesien  |\n";
    cout << "|  336969 II sem. CompSci  |\n";
    cout << "|    Topic: Taxi Agency    |\n";
    cout << "\\--------------------------/\n";
    cout << "\n\tClick any key to continue...\n"; getchar();
    clrscr();
    while (true)
    {
        int state;
        state = adminPanel(registry);
        if (state == 1)
            return;
    }
}
