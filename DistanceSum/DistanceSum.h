#pragma once
#include <vector>
#include <string>

struct Point {
	int x, y;
};

struct Cell {
	int row, col, dist;
	bool operator<(const Cell& other) const {
		return dist > other.dist;
	}
};

class DistanceSum
{
private:
	int M;
	int N;
	Point startingPoint;
	std::vector<std::vector<char>> grid;
public:
	int getM();
	int getN();
	std::vector<std::vector<char>> getGrid();
	void readGrid(std::istream& input_stream);
	void writeGrid(std::ostream& out);
	bool isPointValid(Point p);
	int dijkstra();
};
