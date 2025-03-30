#ifndef MAP_H
#define MAP_H

#include "classes.h"

using Region    = char;
using Time      = unsigned short int;
using Neighbors = vector<pair<Region, Time>>;

// Custom hash function for region
struct RegionHash
{
    size_t operator()(const Region& region) const {
        return std::hash<char>()(region);
    }
};

using Graph     = unordered_map<Region, Neighbors, RegionHash>;

void createMap(Graph& map);

Neighbors getNeighbors(const Graph& map, const Region& region);
Graph createSubmap(const Graph& map, shared_ptr<Driver> driver);

#endif
