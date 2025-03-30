#ifndef INCLUDES_H
#define INCLUDES_H

#include <iostream>
#include <string.h>
#include <vector>
#include <set>
#include <memory>
#include <algorithm>

using namespace std;

template <typename T>
using vsp = vector <shared_ptr <T>>;

template <typename T>
using vwp = vector <weak_ptr <T>>;

#endif
