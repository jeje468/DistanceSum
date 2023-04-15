#include <iostream>
#include <limits>
#include <queue>
#include "distanceSum.h"

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
				startingPoint = { i, j };
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

bool DistanceSum::isPointValid(Point p) {
	return p.x >= 0 && p.x < M&& p.y >= 0 && p.y < N&& grid[p.x][p.y] != 'X';
}

int DistanceSum::dijkstra()
{
	std::priority_queue<Cell> pq;
	pq.push({ startingPoint.x, startingPoint.y, 0 });
	std::vector<std::vector<int>> distances(M, std::vector<int>(N, INT_MAX));
	distances[startingPoint.x][startingPoint.y] = 0;
	std::vector<std::pair<int, int>> dirs = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

	while (!pq.empty()) {
		Cell curr = pq.top();
		pq.pop();
		int row = curr.row, col = curr.col, dist = curr.dist;
		if (dist > distances[row][col]) continue;
		for (auto dir : dirs) {
			int r = row + dir.first, c = col + dir.second;
			if (r < 0 || r >= M || c < 0 || c >= N || grid[r][c] == 'X') continue;
			int new_dist = dist + 1;
			if (new_dist < distances[r][c]) {
				distances[r][c] = new_dist;
				pq.push({ r, c, new_dist });
			}
		}
	}

	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			if (grid[i][j] != 'T' && grid[i][j] != 'X' && grid[i][j] != '-') {
				std::cout << "Minimum distance to reach C(" << i << "," << j << "): " << distances[i][j] << std::endl;
			}
		}
	}
	return 1;
}



