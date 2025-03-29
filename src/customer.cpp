#include "headers/classes.h"

unsigned short Customer::nextId = 1;

Customer::Customer()
{
    id              = nextId++;
    total_distance  = 0;
    total_expenses  = 0;
}
