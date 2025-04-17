#include "headers/main.h"

int main()
{
    clrscr();
    Registry registry;
    auto customer1 = make_shared<Customer>();
    auto customer2 = make_shared<Customer>();
    auto customer3 = make_shared<Customer>();
    registry.addCustomer(customer1);
    registry.addCustomer(customer2);
    registry.addCustomer(customer3);

    cout << "/--------------------------\\\n";
    cout << "| EOOP Preliminary Project |\n";
    cout << "|  Made by: Antoni Jesien  |\n";
    cout << "|  336969 II sem. CompSci  |\n";
    cout << "|    Topic: Taxi Agency    |\n";
    cout << "\\--------------------------/\n";

    cout << "\nWhat do you want to go to:\n";
    cout << "  1. Main application\n";
    cout << "  2. Testing\n";
    int input = 0;
    while (input != 1 && input != 2)
    {
        getVal(input);
        if (input != 1 && input != 2)
            cout << "Incorrect input. Try again: ";
    }
    if (input == 2)
    {
        testing();
        clrscr();
        cout << "Do you want to check out the main program, or exit?\n";
        cout << "  1. Main application\n";
        cout << "  2. Exit\n";
        input = 0;
        while (input != 1 && input != 2)
        {
            getVal(input);
            if (input != 1 && input != 2)
                cout << "Incorrect input. Try again: ";
        }
        if (input == 2)
        {
            cout << "Goodbye!\n";
            return 0;
        }
    }

    Graph map;
    createMap(map);

    menu(registry, map);

    cout << "Thank you for your time!\n";
    cout << "Goodbye\n";
}
