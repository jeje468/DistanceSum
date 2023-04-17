#include <bitset>
#include <fstream>
#include <iomanip>
#include <iostream>
#include "DistanceSum.h"

int main()
{
    DistanceSum problem = DistanceSum();
    std::ifstream input_file("input.txt");
    if (input_file.is_open())
    {
        problem.readGrid(input_file);
    }
    else
    {
        std::cout << "Error: could not open input file" << std::endl;
    }
    input_file.close();
    problem.dijkstra(std::cout);
}
