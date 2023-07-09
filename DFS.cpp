#include <iostream>
#include <fstream>
#include <vector>

enum Terrain {
    empty,
    wall,
    goal,
    crumb
};

std::vector<std::vector<char>> maze;
std::vector<std::vector<int>> visited;
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

bool dfs(int row, int col) {
    int& current = visited[row][col];

    if (current == goal) {
        return true;
    }

    if (current == empty) {
        current = crumb;

        if (dfs(row, col - 1)) {
            current = crumb;
            return true;
        }
        if (dfs(row + 1, col)) {
            current = crumb;
            return true;
        }
        if (dfs(row, col + 1)) {
            current = crumb;
            return true;
        }
        if (dfs(row - 1, col)) {
            current = crumb;
            return true;
        }
    }

    return false;
}

int main() {
    get_maze("maze.txt");
    init_visited();

    print_maze();

    if (!dfs(start_row, start_col)) {
        std::cout << "No path to the goal could be found." << std::endl;
    } else {
        add_crumbs();
        print_maze();
    }

    return 0;
}