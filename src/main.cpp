#include "headers/main.h"

int main()
{
    Registry registry;
    auto customer1 = make_shared<Customer>();
    auto customer2 = make_shared<Customer>();
    auto customer3 = make_shared<Customer>();
    registry.addCustomer(customer1);
    registry.addCustomer(customer2);
    registry.addCustomer(customer3);

    Graph map;
    createMap(map);

    menu(registry, map);

    cout << "Thank you for your time!\n";
    cout << "Goodbye\n";
}
