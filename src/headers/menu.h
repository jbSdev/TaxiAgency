#ifndef MENU_H
#define MENU_H

#include "map.h"
#include "classes.h"

void clrscr();
void menu(Registry&, Graph& map);
void testing();

template <typename T>
void getVal(T& input);
vector <unsigned char> getCharLine();

void createAgency(Registry& reg);
void createDriver(Registry& reg);
void getAgencyData(Registry& reg);
void getDriverData(Registry& reg);
void getRide(Registry& reg, shared_ptr <Customer>& customer, Graph& map);

#endif
