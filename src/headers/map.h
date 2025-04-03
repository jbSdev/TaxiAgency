#ifndef MAP_H
#define MAP_H

#include "includes.h"
#include "classes.h"

void createMap(Graph& map);

Neighbors getNeighbors(const Graph& map, const Region& region);

map <Region, int> dijkstra(const Graph& graph,
                           const Region& start,
                           map<Region, Region>& previous);

list <pathSegment> getShortestPath(const map<Region, Region>& previous,
                              const Graph& graph,
                              const Region& start,
                              const Region& end);

#endif
