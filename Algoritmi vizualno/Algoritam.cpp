#include "framework.h"
#include "Algoritam.h"
#include <chrono>
#include <thread>
#include <utility>   





void Algoritam::BFS(HWND hWnd)
{
	
	resetMap();
	vector< vector<pair<int, int> >> recPath(32, std::vector<std::pair<int, int>>(32));
	queue<Point> NextQ;
	numOfvisited = 0;
	NextQ.push(start);

	while (!NextQ.empty()) {
		current = NextQ.front();
		NextQ.pop();
		numOfvisited++;
		if (current.x == end.x && current.y == end.y) {
			//reconstruct path
			int x = current.x;
			int y = current.y;
			int tempX;
			int tempY;
			numOfsteps = 0;
			while ((x != start.x) || (y != start.y)) {
				tempX = x;
				tempY = y;
				x = recPath[tempX][tempY].first;
				y = recPath[tempX][tempY].second;
				if (grid[x][y] == VISITED) {
					grid[x][y] = PATH;
				}
				numOfsteps++;
			}
			InvalidateRect(hWnd, NULL, 0);
			UpdateWindow(hWnd);
			return;
		}


		//Check all sides to move
		Point temp;
		//left
		if (current.y - 1 >= 0 && (grid[current.x][current.y -1] == NOTVISITED || grid[current.x][current.y - 1] == END)) {
			temp.x = current.x;
			temp.y = current.y - 1;
			if (grid[temp.x][temp.y] != END) {
				grid[temp.x][temp.y] = QUEUE;
			}
			recPath[temp.x][temp.y].first = current.x;
			recPath[temp.x][temp.y].second = current.y;
			NextQ.push(temp);
		}

		//right
		if (current.y + 1 < 32 && (grid[current.x][current.y + 1] == NOTVISITED || grid[current.x][current.y + 1] == END)) {
			temp.x = current.x;
			temp.y = current.y + 1;
			if (grid[temp.x][temp.y] != END) {
				grid[temp.x][temp.y] = QUEUE;
			}
			recPath[temp.x][temp.y].first = current.x;
			recPath[temp.x][temp.y].second = current.y;
			NextQ.push(temp);
		}

		//up
		if (current.x - 1 >= 0 && (grid[current.x - 1][current.y ] == NOTVISITED || grid[current.x - 1][current.y ] == END)) {
			temp.x = current.x - 1;
			temp.y = current.y;
			if (grid[temp.x][temp.y] != END) {
				grid[temp.x][temp.y] = QUEUE;
			}
			recPath[temp.x][temp.y].first = current.x;
			recPath[temp.x][temp.y].second = current.y;
			NextQ.push(temp);
		}

		//down
		if (current.x + 1 < 32 && (grid[current.x + 1][current.y] == NOTVISITED || grid[current.x + 1][current.y] == END)) {
			temp.x = current.x + 1;
			temp.y = current.y;
			if (grid[temp.x][temp.y] != END) {
				grid[temp.x][temp.y] = QUEUE;
			}
			recPath[temp.x][temp.y].first = current.x;
			recPath[temp.x][temp.y].second = current.y;
			NextQ.push(temp);
		}

		

		if (grid[current.x][current.y] != START) {
			grid[current.x][current.y] = VISITED;
		}
		InvalidateRect(hWnd, NULL, 0);
		UpdateWindow(hWnd);
		//std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}


	
}

void Algoritam::removeStartPos()
{
	for (int i = 0; i < 32; i++) {
		for (int j = 0; j < 32; j++) {
			if (grid[i][j] == START) {
				grid[i][j] = NOTVISITED;
			}
		}
	}
}

void Algoritam::removeEndPos()
{
	for (int i = 0; i < 32; i++) {
		for (int j = 0; j < 32; j++) {
			if (grid[i][j] == END) {
				grid[i][j] = NOTVISITED;
			}
		}
	}
}
//reset algorithm work on map
void Algoritam::resetMap()
{
	for (int i = 0; i < 32; i++) {
		for (int j = 0; j < 32; j++) {
			if (grid[i][j] == VISITED || grid[i][j] == PATH || grid[i][j] == QUEUE) {
				grid[i][j] = NOTVISITED;
			}
		}
	}
}

//reset all except start & end
void Algoritam::resetMapALL()
{
	for (int i = 0; i < 32; i++) {
		for (int j = 0; j < 32; j++) {
			if (grid[i][j] == VISITED || grid[i][j] == PATH || grid[i][j] == QUEUE || grid[i][j] == WALL) {
				grid[i][j] = NOTVISITED;
			}
		}
	}
}

void Algoritam::generateRandomWalls()
{
	for (int i = 0; i < 32; i++) {
		for (int j = 0; j < 32; j++) {
			if (grid[i][j] == NOTVISITED) {
				double val = (double)rand() / RAND_MAX;
				if (val < 0.2) {
					grid[i][j] = WALL;
				}
			}
		}
	}
}
