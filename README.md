The mazesolver is being implemented by the use of three algorithms:

1. DEPTH FIRST SEARCH
   
(a) The code includes necessary header files: 'iostream', 'fstream', and 'vector'.
(b) An enum 'Terrain' is defined to represent different types of terrain in the maze. The enum values are 'empty', 'wall', 'goal', and 'crumb'.
(c) 'maze' is declared as a 2D vector of characters to represent the maze layout.
(d) 'visited' is declared as a 2D vector of integers to keep track of visited cells in the maze.
(e) Variables 'rows' and 'cols' are declared to store the dimensions of the maze.
(f) 'start_row' and 'start_col' are declared to store the starting position of the maze.
(g) The function 'alloc_maze' is defined to allocate memory for the maze vector based on the number of rows and columns.
(h) The function 'alloc_visited' is defined to allocate memory for the 'visited' vector based on the number of rows and columns.
(i) The function 'get_maze' takes a file name as input, reads the maze layout from the file, and stores it in the 'maze' vector. It also sets the 'rows' and 'cols' variables based on the read values.
     If the file doesn't exist, an error message is displayed.
(j) The function 'init_visited' initializes the 'visited' vector based on the 'maze' vector. It sets the terrain type ('wall', 'goal', or 'empty') for each cell.
(k) The function 'print_maze' is defined to print the current state of the maze.
(l) The function 'add_crumbs' updates the 'maze' vector by replacing cells marked as 'crumb' with a . character. The starting position (s) is not replaced.
(m) The 'dfs' function implements the depth-first search algorithm. It takes the current row and column as input and performs the search recursively. It marks visited cells with 'crumb'
    and checks for the goal cell. If the goal is found, it returns 'true'. It explores neighboring cells in a clockwise manner: left, down, right, and up. If any of the neighboring cells can
    reach the goal, it returns true. Otherwise, it returns 'false'.
(n) In the main function, the 'get_maze' function is called to read the maze from the file "maze.txt". Then, the 'init_visited' function is called to initialize the 'visited' vector.
    The initial state of the maze is printed using 'print_maze'.
(o) The 'dfs' function is called with the starting position (start_row and start_col). If a path to the goal is found, the 'add_crumbs' function is called to mark the path with .
    characters, and the final state of the maze is printed. Otherwise, a message indicating that no path could be found is displayed.

2. DIJKSTRA ALGORITHM

(a) The 'distance' vector is added to store the minimum distance from the starting position to each cell in the maze.
(b) The 'alloc_distance' function is defined to allocate memory for the 'distance' vector and initialize all distances to a maximum value.
(c) The 'init_visited' function is modified to call the 'alloc_distance' function and initialize the 'distance' vector.
(d) The 'dijkstra' function is defined to implement Dijkstra's algorithm. It uses a priority queue to store cells based on their distances. It starts with the starting position and explores neighboring cells. If a shorter path to a cell is found, the distance is updated, and the cell is added to the priority queue.
(e) The condition to check if a path to the goal could be found is modified to 'visited[start_row][start_col] != crumb'. If the starting position is marked as a 'crumb', it means a path to the goal exists.
    The rest of the code remains the same, including reading the maze from a file, printing the maze, adding crumbs to the maze, and displaying the final maze state.
(f) In the 'main' function, the 'dijkstra' function is called after initializing the maze and visited cells. This calculates the minimum distances from the starting position to all cells.

3. A* ALGORITHM

(a) The 'heuristic' function is defined to calculate the Manhattan distance heuristic between a given cell and the goal cell.
(b) The 'isValid' function is defined to check if a cell is within the maze boundaries and is not a wall.
(c) The 'isGoal' function is defined to check if a given cell is the goal cell.
(d) The 'getNeighbors' function is defined to get the neighboring cells of a given cell.
(e) The '<' operator is overloaded for the 'Cell' struct to compare cells based on their 'f' values.
(f) The 'aStar' function is defined to implement the A* algorithm. It uses a priority queue to store cells based on their 'f' values. It starts with the starting position and explores neighboring cells. If a shorter path to a cell is found, the 'g' value and 'f' value are updated, and the cell is added to the priority queue. The algorithm continues until it reaches the goal cell.
(g) The 'print_maze' function is modified to print the maze with additional characters: 's' for the starting position, '+' for walls, 'g' for the goal, and '.' for crumbs. The 'visited' vector is used to determine the cell type.
The rest of the code remains the same, including reading the maze from a file, adding crumbs to the maze, and displaying the final maze state.
(g) In the 'main' function, the 'aStar' function is called after initializing the maze and visited cells. This calculates the shortest path from the starting position to the goal using the A* algorithm.
