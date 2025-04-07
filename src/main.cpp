#include "headers/main.h"

int main()
{
    Registry registry;
    menu(registry);
    /*
     * auto agencyA = make_shared<Agency>('A');
     * auto agencyB = make_shared<Agency>('B');
     * auto agencyC = make_shared<Agency>('C');
     * auto agencyD = make_shared<Agency>('D');
     * auto agencyP = make_shared<PremiumAgency>('P');
     * 
     * registry.addAgency(agencyA);
     * registry.addAgency(agencyB);
     * registry.addAgency(agencyC);
     * registry.addAgency(agencyD);
     * registry.addAgency(agencyP);
     * 
     * auto driver1 = make_shared<Driver>("John", 1234);
     * auto driver2 = make_shared<Driver>("Adam", 5678);
     * auto driver3 = make_shared<Driver>("Bob",  84172);
     * auto driver4 = make_shared<Driver>("Marc", 83791);
     * 
     * agencyA -> addDriver(driver1);
     * agencyA -> addDriver(driver3);
     * agencyB -> addDriver(driver2);
     * agencyB -> addDriver(driver3);
     * agencyC -> addDriver(driver2);
     * agencyC -> addDriver(driver3);
     * agencyC -> addDriver(driver4);
     * agencyD -> addDriver(driver1);
     * 
     * agencyP -> addDriver(driver3);
     * 
     * agencyA -> setRegions({'A', 'B', 'C', 'G', 'F', 'K', 'L', 'M', 'H'});
     * agencyB -> setRegions({'C', 'D', 'E', 'H', 'I', 'J', 'M', 'N', 'O'});
     * agencyC -> setRegions({'K', 'L', 'M', 'P', 'Q', 'R', 'U', 'V', 'W'});
     * agencyD -> setRegions({'M', 'N', 'O', 'R', 'S', 'T', 'W', 'X', 'Y'});
     * agencyP -> setRegions({'M', 'N', 'O', 'R', 'S', 'T', 'W', 'X', 'Y'});
     * 
     * agencyA -> setRegionFee(2.0);
     * agencyB -> setRegionFee(3.0);
     * agencyC -> setRegionFee(4.0);
     * agencyD -> setRegionFee(1.0);
     * agencyP -> setRegionFee(1.0);
     * agencyP -> setPremiumFee(1.0);
     * 
     * agencyA -> setStartingFee(5.0);
     * agencyB -> setStartingFee(7.0);
     * agencyC -> setStartingFee(11.0);
     * agencyD -> setStartingFee(8.0);
     * agencyP -> setStartingFee(8.0);
     * 
     * #<{(|
     *  * Region start = 'C';
     *  * Region end   = 'M';
     *  |)}>#
     * 
     * Graph map;
     * createMap(map);
     * 
     * auto customer1 = make_shared <Customer>();
     * auto customer2 = make_shared <Customer>();
     * customer1 -> requestRide('O', 'Y', registry, map);
     * customer1 -> requestPremiumRide('O', 'Y', registry, map);
     * customer2 -> requestRide('B', 'S', registry, map);
     * customer1 -> getInfo();
     * customer2 -> getInfo();
     * #<{(|
     *  * auto customer2 = make_shared <Customer>();
     *  * customer1 -> requestRide(start, end, registry, map);
     *  * customer2 -> requestRide('J', 'M', registry, map);
     *  * customer1 -> requestRide('D', 'Q', registry, map);
     *  * cout << "Customer1 info:\n";
     *  * customer1 -> getInfo();
     *  |)}>#
     */
}
