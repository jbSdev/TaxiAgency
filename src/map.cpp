#include "headers/main.h"

void createMap(Graph& map)
{
    /*         MAP
     *
     *  A--1--B--2--C--1--D--1--E
     *  |     |     |     |     |
     *  2     4     3     2     7
     *  |     |     |     |     |
     *  F--1--G--2--H--1--I--1--J
     *  |     |     |     |     |
     *  6     3     2     5     2
     *  |     |     |     |     |
     *  K--1--L--3--M--2--N--1--O
     *  |     |     |     |     |
     *  4     6     4     1     4
     *  |     |     |     |     |
     *  P--2--Q--1--R--2--S--1--T
     *  |     |     |     |     |
     *  3     2     5     3     6
     *  |     |     |     |     |
     *  U--1--V--2--W--1--X--2--Y
     *
     */

    map['A'] = { {'B', 1}, {'F', 2} };
    map['B'] = { {'A', 1}, {'C', 2}, {'G', 4} };
    map['C'] = { {'B', 2}, {'D', 1}, {'H', 3} };
    map['D'] = { {'C', 1}, {'E', 1}, {'I', 2} };
    map['E'] = { {'D', 1}, {'J', 7} };
    map['F'] = { {'A', 2}, {'G', 1}, {'K', 6} };
    map['G'] = { {'B', 4}, {'F', 1}, {'H', 2}, {'L', 3} };
    map['H'] = { {'C', 3}, {'G', 2}, {'I', 1}, {'M', 2} };
    map['I'] = { {'D', 2}, {'H', 1}, {'J', 1}, {'N', 5} };
    map['J'] = { {'E', 7}, {'I', 1}, {'O', 2} };
    map['K'] = { {'F', 6}, {'L', 1}, {'P', 4} };
    map['L'] = { {'G', 3}, {'K', 1}, {'M', 3}, {'Q', 6} };
    map['M'] = { {'H', 2}, {'L', 3}, {'N', 2}, {'R', 4} };
    map['N'] = { {'I', 5}, {'M', 2}, {'O', 1}, {'S', 1} };
    map['O'] = { {'J', 2}, {'N', 1}, {'T', 4} };
    map['P'] = { {'K', 4}, {'Q', 2}, {'U', 3} };
    map['Q'] = { {'L', 6}, {'P', 2}, {'R', 1}, {'V', 2} };
    map['R'] = { {'M', 4}, {'Q', 1}, {'S', 2}, {'W', 5} };
    map['S'] = { {'N', 1}, {'R', 2}, {'T', 1}, {'X', 3} };
    map['T'] = { {'O', 4}, {'S', 1}, {'Y', 6} };
    map['U'] = { {'P', 3}, {'V', 1} };
    map['V'] = { {'Q', 2}, {'U', 1}, {'W', 2} };
    map['W'] = { {'R', 5}, {'V', 2}, {'X', 1} };
    map['X'] = { {'S', 3}, {'W', 1}, {'Y', 2} };
    map['Y'] = { {'T', 6}, {'X', 2} };
}

Neighbors getNeighbors(const Graph& map, const Region& region)
{
    auto it = map.find(region);
    if (it != map.end())
        return it -> second;
    else
        return Neighbors();
}

Graph createSubmap(const Graph& map, shared_ptr<Driver> driver)
{
    Graph submap;
    for (const auto& entry : map)
        if (driver -> operatesInRegion(entry.first))
            submap.insert(entry);

    return submap;
}
