#ifndef INCLUDES_H
#define INCLUDES_H

#include <iostream>
#include <string.h>
#include <vector>
#include <set>
#include <memory>
#include <algorithm>
#include <unordered_map>
#include <utility>
#include <map>
#include <list>
#include <queue>

using namespace std;

template <typename T>
using vsp = vector <shared_ptr <T>>;

template <typename T>
using vwp = vector <weak_ptr <T>>;

using Region    = char;
using Time      = unsigned short int;
using Neighbors = vector<pair<Region, Time>>;

// Custom hash function for region
struct RegionHash
{
    size_t operator()(const Region& region) const {
        return std::hash<char>()(region); }
};

using Graph     = unordered_map<Region, Neighbors, RegionHash>;

template <typename Container, typename T>
bool isIn(const Container& arr, const T& val);

struct pathSegment
{
    Region region;
    int time;
};

#endif
