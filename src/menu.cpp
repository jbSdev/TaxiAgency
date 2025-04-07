#include "headers/main.h"
#include <sstream>

void clrscr()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

inline shared_ptr <Agency> createAgency(Registry& registry)
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

    string input;
    vector <Region> temp;
    Region regions[25];

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
    registry.addAgency      (agency);
    agency -> setRegions    (regions);
    agency -> setStartingFee(startingFee);
    agency -> setRegionFee  (regionFee);
    return agency;
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
    cout << "Let's create the first agency.\n";
    auto agency = createAgency(registry);
    cout << "Agency " << agency -> getId() << " created\n";
}
