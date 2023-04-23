#include <bitset>
#include <iostream>
#include <limits>
#include <queue>
#include "distanceSum.h"

DistanceSum::DistanceSum()
{
	M = 0;
	N = 0;
	grid = std::vector<std::vector<char>>(M, std::vector<char>(N));
}
const std::vector<std::pair<int, int>> DistanceSum::directionCoordinates
{
	{0, 1},
	{1, 0},
	{0, -1},
	{-1, 0}
};

const const std::vector<std::bitset<4>> DistanceSum::directionMasks
{
	std::bitset<4>(0b0100),
	std::bitset<4>(0b0010),
	std::bitset<4>(0b0001),
	std::bitset<4>(0b1000)
};

int DistanceSum::getM()
{
	return M;
}

int DistanceSum::getN()
{
	return N;
}

std::vector<std::vector<char>> DistanceSum::getGrid()
{
	return grid;
}

void DistanceSum::readGrid(std::istream& input_stream)
{
	input_stream >> M >> N;

	grid = std::vector<std::vector<char>>(M, std::vector<char>(N));

	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			input_stream >> grid[i][j];
			if (grid[i][j] == 'T')
			{
				startingNode = { i, j , 0};
			}
		}
	}
}

void DistanceSum::writeGrid(std::ostream& out)
{
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			out << grid[i][j];
		}
		out << std::endl;
	}
}

int charToHex(char c) {
	if (c >= '0' && c <= '9') {
		return c - '0';
	}
	else if (c >= 'A' && c <= 'F') {
		return c - 'A' + 10;
	}
	else {
		return -1;
	}
}

bool DistanceSum::isNodeOpen(char examinedNodeValue, std::bitset<4> dir)
{
	int hex = charToHex(examinedNodeValue);
	std::bitset<4> bits(hex);
	return (dir & bits) != 0;
}

bool DistanceSum::isHexDigit(char c)
{
	return (c > '0' && c <= '9') || (c >= 'A' && c <= 'F');
}

void DistanceSum::dijkstra(std::ostream& out)
{
	std::vector<std::vector<Node>> nodes(M, std::vector<Node>(N));
	std::priority_queue<Node> pq;

	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[i].size(); j++)
		{
			if (i == startingNode.row && j == startingNode.col)
				nodes[i][j] = { i, j, 0, -1, -1 };
			else
				nodes[i][j] = { i, j, std::numeric_limits<int>::max() - 1, -1, -1 };
			pq.push(nodes[i][j]);
		}
	}

	while (!pq.empty())
	{
		Node curr = pq.top();
		pq.pop();
		if (isHexDigit(grid[curr.row][curr.col]))continue;
		for (size_t i = 0; i < directionCoordinates.size(); i++) 
		{
			int r = curr.row + directionCoordinates[i].first, c = curr.col + directionCoordinates[i].second;
			if (r < 0 || r >= M || c < 0 || c >= N || grid[r][c] == 'X') continue;
			if (grid[r][c] == '-' || (isHexDigit(grid[r][c]) && isNodeOpen(grid[r][c], directionMasks[i])))
			{
				if (curr.dist + 1 < nodes[r][c].dist) {
					nodes[r][c].dist = curr.dist + 1;
					nodes[r][c].prevRow = curr.row;
					nodes[r][c].prevCol = curr.col;
					pq.push(nodes[r][c]);
				}
			}
		}
	}

	int sum = 0;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			if (isHexDigit(grid[i][j])) {nodes[i][j].dist - 1;
				sum += nodes[i][j].dist == std::numeric_limits<int>::max() - 1 ? 0 : nodes[i][j].dist - 1;
			}
		}
	}

	out << sum;
}




