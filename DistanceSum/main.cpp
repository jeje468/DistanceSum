#include <bitset>
#include <fstream>
#include <iomanip>
#include <iostream>
#include "DistanceSum.h"

int main()
{
    DistanceSum problem = DistanceSum();
    problem.readGrid();
    problem.dijkstra();

    return 0;
}
