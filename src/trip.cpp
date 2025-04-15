#include "headers/main.h"

unsigned short Trip::nextId = 1;

Trip::Trip(const Region         start,
           const Region         end,
           const float          prc,
           weak_ptr <Driver>    drv,
           weak_ptr <Customer>  cst,
           vwp <Agency>         agn,
           const string         tpe)
    : id(nextId++), origin(start), destination(end), price(prc), driver(drv), customer(cst), agencies(agn), type(tpe) {};

Trip::~Trip()
{
    driver.reset();
    customer.reset();
    for (auto& ag : agencies)
        ag.reset();
}

int Trip::getId() const { return id; }

void Trip::getInfo() const
{
    cout << "ID: "          << id           << endl;
    cout << "Origin: "      << origin       << endl;
    cout << "Destination: " << destination  << endl;
    cout << "Price: "       << price        << endl;
    cout << "Customer: "    << customer.lock() -> getId() << endl;
    cout << "Driver: "      << driver.lock() -> getName() << endl;
    cout << "Agencies: ";   for (auto &ag : agencies) cout << ag.lock() -> getId() << " ";  cout << endl;
}

weak_ptr <Driver> Trip::getDriver() const { return driver; }

Region Trip::getStart() const { return origin; }

Region Trip::getEnd()   const { return destination; }
