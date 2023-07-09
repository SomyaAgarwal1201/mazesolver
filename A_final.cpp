#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cmath>
#include <bits/stdc++.h>

enum Terrain {
    empty,
    wall,
    goal,
    crumb
};

struct Cell {
    int row;
    int col;
    int f;
    int g;
    int h;
};

std::vector<std::vector<char>> maze;
std::vector<std::vector<int>> visited;
int rows;
int cols;
int start_row;
int start_col;
int goal_row;
int goal_col;

void alloc_maze() {
    maze.resize(rows, std::vector<char>(cols));
}

void alloc_visited() {
    visited.resize(rows, std::vector<int>(cols));
}

void get_maze(const std::string& file_name) {
    char c;
    std::ifstream maze_file(file_name);

    if (maze_file) {
        std::string rows_s, cols_s;
        std::getline(maze_file, rows_s, ',');
        std::getline(maze_file, cols_s);

        rows = std::stoi(rows_s);
        cols = std::stoi(cols_s);

        alloc_maze();

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                maze_file.get(c);

                if (c == '\n') {
                    maze_file.get(c);
                }

                maze[i][j] = c;

                if (c == 's') {
                    start_row = i;
                    start_col = j;
                } else if (c == 'g') {
                    goal_row = i;
                    goal_col = j;
                }
            }
        }
    } else {
        std::cout << "No such file!" << std::endl;
        return;
    }

    maze_file.close();
}

void init_visited() {
    alloc_visited();

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (maze[i][j] == '+') {
                visited[i][j] = wall;
            } else if (maze[i][j] == 'g') {
                visited[i][j] = goal;
            } else {
                visited[i][j] = empty;
            }
        }
    }
}

void print_maze() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (maze[i][j] == 's') {
                std::cout << 's';
            } else if (maze[i][j] == 'g') {
                std::cout << 'g';
            } else if (maze[i][j] == '+') {
                std::cout << '+';
            } else if (visited[i][j] == crumb) {
                std::cout << '.';
            } else if (visited[i][j] == goal) {
                std::cout << 'g';
            } else {
                std::cout << ' ';
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


int heuristic(int row, int col) {
    return std::abs(row - goal_row) + std::abs(col - goal_col);
}

bool isValid(int row, int col) {
    return row >= 0 && row < rows && col >= 0 && col < cols && visited[row][col] != wall;
}

bool isGoal(int row, int col) {
    return row == goal_row && col == goal_col;
}

std::vector<Cell> getNeighbors(const Cell& current) {
    std::vector<Cell> neighbors;
    int row = current.row;
    int col = current.col;

    // Top
    if (isValid(row - 1, col)) {
        neighbors.push_back({row - 1, col});
    }
    // Right
    if (isValid(row, col + 1)) {
        neighbors.push_back({row, col + 1});
    }
    // Bottom
    if (isValid(row + 1, col)) {
        neighbors.push_back({row + 1, col});
    }
    // Left
    if (isValid(row, col - 1)) {
        neighbors.push_back({row, col - 1});
    }

    return neighbors;
}

bool operator<(const Cell& a, const Cell& b) {
    return a.f > b.f;
}

void add_crumbs() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (maze[i][j] != 's' && visited[i][j] == crumb) {
                maze[i][j] = '.';
            }
        }
    }
}

void aStar() {
    std::priority_queue<Cell> pq;
    std::vector<std::vector<bool>> closed(rows, std::vector<bool>(cols, false));
    std::vector<std::vector<Cell>> parent(rows, std::vector<Cell>(cols));
    std::vector<std::vector<int>> g(rows, std::vector<int>(cols, INT_MAX));

    Cell start{start_row, start_col, 0, 0, 0};
    pq.push(start);
    g[start_row][start_col] = 0;

    while (!pq.empty()) {
        Cell current = pq.top();
        pq.pop();
        int row = current.row;
        int col = current.col;

        if (closed[row][col])
            continue;

        visited[row][col] = crumb;
        closed[row][col] = true;

        if (isGoal(row, col))
            break;

        std::vector<Cell> neighbors = getNeighbors(current);
        for (const Cell& neighbor : neighbors) {
            int neighbor_row = neighbor.row;
            int neighbor_col = neighbor.col;
            int cost = 1;

            if (g[row][col] + cost < g[neighbor_row][neighbor_col]) {
                g[neighbor_row][neighbor_col] = g[row][col] + cost;
                int h = heuristic(neighbor_row, neighbor_col);
                int f = g[neighbor_row][neighbor_col] + h;
                parent[neighbor_row][neighbor_col] = {row, col, f, g[neighbor_row][neighbor_col], h};
                pq.push({neighbor_row, neighbor_col, f, g[neighbor_row][neighbor_col], h});
            }
        }
    }

    int current_row = goal_row;
    int current_col = goal_col;

    while (!(current_row == start_row && current_col == start_col)) {
        maze[current_row][current_col] = '.';
        visited[current_row][current_col] = crumb;
        Cell next = parent[current_row][current_col];
        current_row = next.row;
        current_col = next.col;
    }
}

int main() {
    get_maze("maze.txt");
    init_visited();

    print_maze();

    aStar();

    if (visited[goal_row][goal_col] != crumb) {
        std::cout << "No path to the goal could be found." << std::endl;
    } else {
        add_crumbs();
        print_maze();
    }

    return 0;
}
