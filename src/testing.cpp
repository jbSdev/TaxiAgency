#include "headers/func.h"
#include "headers/main.h"
#include "headers/menu.h"
#include <memory>

void testing()
{
    clrscr();
    Registry reg;
    Graph map;
    createMap(map);
    auto cst = make_shared <Customer>();
    cout << "Welcome to testing!\n";
    cout << "Here you can test the code for edge-cases and invalid input.\n";
    p2c();

    cout << "\nFirst, let's check what happens if we want to get info about agencies and drivers, when there are none created\n";
    wait(1000);
    cout << "\n  Checking agencies:\n";
    wait(500);
    getAgencyData(reg);
    cout << "\n  Checking drivers:\n";
    wait(500);
    getDriverData(reg);
    cout << "\nThere should be two messages about the lack of objects.\n";
    p2c();

    clrscr();
    cout << "What about requesting a ride when there is no driver that can take it?\n";
    cout << "  You can try inputting incorrect data when asked.\n";
    p2c();
    getRide(reg, cst, map);

    clrscr();
    cout << "Now, let's try to create an agency.\n";
    cout << "Try and input wrong data at first, i.e:\n";
    cout << "  Numbers when asked for ID (char)\n";
    cout << "  Non-alphanumeric characters/too much data/unexisting values when asked for regions\n";
    cout << "  Characters when asked for fees (float)\n";
    cout << "\nThe program should reject the incorrect input for ID and fees, asking the user to input it again.\n";
    cout << "For regions, the program synthesizes input, getting rid of any non-alphanumerical characters. The input 'aB 4C-' becomes 'ABC'\n";
    cout << "If the outcome is empty, the program informs user about the lack of proper data\n";
    cout << "\nLet's try!\n\n";
    createAgency(reg);
    
    clrscr();
    cout << "Now let's do the same for creating the driver\n";
    cout << "  For the name, program accepts anything\n";
    cout << "  For the license number, the program accepts numbers from 0 to 4'294'967'295\n";
    cout << "  For agencies, if the input contains a non-alphanumeric character, or a character representing an nonexisting agency\n";
    cout << "   the program should inform the user about the incorrect input and wait for the new one\n";
    cout << "Let's try!\n\n";
    createDriver(reg);

    clrscr();
    cout << "What about creating the second agency?\n";
    cout << "Try to create a new agency with the same ID as the previous one.\n";
    cout << "The program should inform about an already existing agency with that ID.\n";
    createAgency(reg);

    clrscr();
    cout << "Let's do the same for a second driver, but try to repeat the license number.\n";
    createDriver(reg);
    
    clrscr();
    cout << "Let's request a ride once again. We have a driver working on the regions you've set up for the agency.\n";
    cout << "You've got 2 tries. I suggest you taking the first try for requesting a ride between regions that the driver does not operate in\n";
    cout << " And the second try to make a proper request.\n";
    cout << "\n\tFirst request\n";
    getRide(reg, cst, map);
    cout << "\n\tSecond request\n";
    getRide(reg, cst, map);

    clrscr();
    cout << "Now let's see info about the customer. It should the drive if you've requested it correctly.\n";
    cst -> getInfo();
    p2c();

    cout << "\n\nThat's all for testing!\n";
    p2c();
    return;
}
