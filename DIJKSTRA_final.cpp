#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>

enum Terrain {
    empty,
    wall,
    goal,
    crumb
};

std::vector<std::vector<char>> maze;
std::vector<std::vector<int>> visited;
std::vector<std::vector<int>> distance;
int rows;
int cols;
int start_row;
int start_col;

void alloc_maze() {
    maze.resize(rows, std::vector<char>(cols));
}

void alloc_visited() {
    visited.resize(rows, std::vector<int>(cols));
}

void alloc_distance() {
    distance.resize(rows, std::vector<int>(cols, std::numeric_limits<int>::max()));
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
    alloc_distance();

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

    distance[start_row][start_col] = 0;
}

void print_maze() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << maze[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
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

void dijkstra() {
    std::priority_queue<std::pair<int, std::pair<int, int>>, std::vector<std::pair<int, std::pair<int, int>>>, std::greater<std::pair<int, std::pair<int, int>>>> pq;
    pq.push(std::make_pair(0, std::make_pair(start_row, start_col)));

    while (!pq.empty()) {
        int dist = pq.top().first;
        int row = pq.top().second.first;
        int col = pq.top().second.second;
        pq.pop();

        if (visited[row][col] != empty) {
            continue;
        }

        visited[row][col] = crumb;

        if (maze[row][col] == 'g') {
            visited[row][col] = goal;
        }

        if (row > 0 && maze[row - 1][col] != '+' && dist + 1 < distance[row - 1][col]) {
            distance[row - 1][col] = dist + 1;
            pq.push(std::make_pair(dist + 1, std::make_pair(row - 1, col)));
        }
        if (row < rows - 1 && maze[row + 1][col] != '+' && dist + 1 < distance[row + 1][col]) {
            distance[row + 1][col] = dist + 1;
            pq.push(std::make_pair(dist + 1, std::make_pair(row + 1, col)));
        }
        if (col > 0 && maze[row][col - 1] != '+' && dist + 1 < distance[row][col - 1]) {
            distance[row][col - 1] = dist + 1;
            pq.push(std::make_pair(dist + 1, std::make_pair(row, col - 1)));
        }
        if (col < cols - 1 && maze[row][col + 1] != '+' && dist + 1 < distance[row][col + 1]) {
            distance[row][col + 1] = dist + 1;
            pq.push(std::make_pair(dist + 1, std::make_pair(row, col + 1)));
        }
    }
}

int main() {
    get_maze("maze.txt");
    init_visited();

    dijkstra();

    print_maze();

    if (visited[start_row][start_col] != crumb) {
        std::cout << "No path to the goal could be found." << std::endl;
    } else {
        add_crumbs();
        print_maze();
    }

    return 0;
}