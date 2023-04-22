#pragma once
#include <bitset>
#include <vector>

struct Node {
	int row, col, dist, prevRow, prevCol;
	bool operator<(const Node& other) const {
		return dist > other.dist;
	}
};

class DistanceSum
{
private:
	int M;
	int N;
	Node startingNode;
	std::vector<std::vector<char>> grid;
public:
	DistanceSum();
	static const std::vector<std::pair<int, int>> directionCoordinates;
	static const std::vector<std::bitset<4>> directionMasks;
	int getM();
	int getN();
	std::vector<std::vector<char>> getGrid();
	void readGrid(std::istream& input_stream = std::cin);
	void writeGrid(std::ostream& out);
	bool isNodeOpen(char examinedNodeValue, std::bitset<4> dir);
	bool isHexDigit(char c);
	void dijkstra(std::ostream& out = std::cout);
};
