#include "headers/classes.h"
#include <memory>

int main()
{
    auto agencyA = make_shared<Agency>('A');
    auto agencyB = make_shared<Agency>('B');
    auto agencyC = make_shared<Agency>('C');

    auto driver1 = make_shared<Driver>("John", 1234);
    auto driver2 = make_shared<Driver>("Adam", 5678);

    agencyA -> addDriver(driver1);
    /*
     * agencyB -> addDriver(driver1);
     * agencyB -> addDriver(driver2);
     * agencyC -> addDriver(driver2);
     */

    driver1 -> getInfo();
    // driver2 -> getInfo();
}
