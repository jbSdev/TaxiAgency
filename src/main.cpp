#include "headers/main.h"
#include "headers/map.h"

int main()
{
    Registry registry;

    auto agencyA = make_shared<Agency>('A');
    auto agencyB = make_shared<Agency>('B');
    auto agencyC = make_shared<Agency>('C');

    registry.addAgency(agencyA);
    registry.addAgency(agencyB);
    registry.addAgency(agencyC);

    auto driver1 = make_shared<Driver>("John", 1234);
    auto driver2 = make_shared<Driver>("Adam", 5678);
    auto driver3 = make_shared<Driver>("Bob", 84172);
    auto driver4 = make_shared<Driver>("Marc", 83791);

    agencyA -> addDriver(driver1);
    agencyA -> addDriver(driver3);
    agencyB -> addDriver(driver1);
    agencyB -> addDriver(driver2);
    agencyC -> addDriver(driver2);
    agencyC -> addDriver(driver3);
    agencyC -> addDriver(driver4);

    driver1 -> setRegions({'A', 'B', 'C'});
    driver2 -> setRegions({'B', 'D'});
    driver3 -> setRegions({'A', 'C'});
    driver4 -> setRegions({'C'});

    vsp <Driver> avaDri = findDrivers('A', 'C', registry);
    for (auto &i : avaDri)
        i -> getInfo();

    Graph map;
    createMap(map);

    for (auto region : map)
         cout << region.first << ' ';

    Graph submap = createSubmap(map, driver2);
    cout << "\nSUBMAP\n";
    for (auto region : submap)
        cout << region.first << ' ';

}
