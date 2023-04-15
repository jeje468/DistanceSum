#include <fstream>
#include <iostream>
#include "DistanceSum.h"

int main()
{
    DistanceSum problem = DistanceSum();
    std::ifstream input_file("E:\\AIMotive\\DistanceSum\\DistanceSum\\x64\\Debug\\input.txt");
    if (input_file.is_open())
    {
        problem.readGrid(input_file);
    }
    else
    {
        std::cout << "Error: could not open input file" << std::endl;
    }
    input_file.close();
    int x = problem.dijkstra();
    //problem.setupGrid(std::cin);
    /*std::cout << problem.getM() << ", " << problem.getN() << std::endl;
    auto grid = problem.getGrid();
    problem.writeGrid(std::cout);*/
    x = 1;
}
