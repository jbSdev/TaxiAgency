#include "headers/main.h"
#include "headers/classes.h"

int main()
{
    Registry registry;

    auto agencyA = make_shared<Agency>('A');
    auto agencyB = make_shared<Agency>('B');
    auto agencyC = make_shared<Agency>('C');
    auto agencyD = make_shared<Agency>('D');

    registry.addAgency(agencyA);
    registry.addAgency(agencyB);
    registry.addAgency(agencyC);

    auto driver1 = make_shared<Driver>("John", 1234);
    auto driver2 = make_shared<Driver>("Adam", 5678);
    auto driver3 = make_shared<Driver>("Bob", 84172);
    auto driver4 = make_shared<Driver>("Marc", 83791);

    agencyA -> addDriver(driver1);
    agencyA -> addDriver(driver3);
    agencyD -> addDriver(driver1);
    agencyB -> addDriver(driver2);
    agencyC -> addDriver(driver2);
    agencyC -> addDriver(driver3);
    agencyC -> addDriver(driver4);

    agencyA -> setRegions({'A', 'B', 'C', 'G', 'F', 'K', 'L', 'M', 'H'});
    agencyB -> setRegions({'C', 'D', 'E', 'H', 'I', 'J', 'M', 'N', 'O'});
    agencyC -> setRegions({'K', 'L', 'M', 'P', 'Q', 'R', 'U', 'V', 'W'});
    agencyD -> setRegions({'M', 'N', 'O', 'R', 'S', 'T', 'W', 'X', 'Y'});

    agencyA -> setRegionFee(2.0);
    agencyB -> setRegionFee(3.0);
    agencyC -> setRegionFee(4.0);
    agencyD -> setRegionFee(1.0);

    Region start = 'C';
    Region end   = 'M';

    Graph map;
    createMap(map);
    
    Customer customer;
    customer.requestRide(start, end, registry, map);
    // driver1 -> listRegions();
}
