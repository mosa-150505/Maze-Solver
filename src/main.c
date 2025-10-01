#include <stdio.h>
#include <stdlib.h>

/*
    THIS IS JUST A REIMPLEMENTATION OF A CODE WRITTEN BY Leto II Atreides, I'VE JUST FIXED SOME LEAKS 
 */


char** maze;
int** visited;
int rows;
int cols;
int start_row;
int start_col;

enum terrain {
    empty,
    wall,
    goal,
    crumb
};

void maze_allocation() {
    int i;

    maze = malloc(rows * sizeof(char*));

    for (i = 0; i < rows; i++)
        maze[i] = malloc(cols * sizeof(char));
}

void visited_allocation() {
    int i;

    visited = malloc(rows * sizeof(int*));

    for (i = 0; i < rows; i++)
        visited[i] = malloc(cols * sizeof(int));
}

void get_maze(char* file_name) {
    FILE* maze_file = fopen(file_name, "r");
    if (!maze_file) {
        printf("\n\aNo such file !\n");
        exit(1);
    }

    fscanf(maze_file, "%d,%d", &rows, &cols);

    maze_allocation();

    int i, j;
    int c; 

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            do {
                c = fgetc(maze_file);
                if (c == EOF) {
                    printf("Error: unexpected end of file!\n");
                    exit(1);
                }
            } while (c == '\n' || c == '\r');

            maze[i][j] = (char)c;

            if (c == 's') {
                start_row = i;
                start_col = j;
            }
        }
    }

    fclose(maze_file);
}



void init_visited() {
    visited_allocation();

    int i, j;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (maze[i][j] == '+')
                visited[i][j] = wall;

            else if (maze[i][j] == 'g') 
                visited[i][j] = goal;

            else
                visited[i][j] = empty;
        }
    }
}

void init_display() {
    system("figlet DFS Maze Solver");
}

void print_maze() {
    int i, j;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (maze[i][j] == '.')
                printf("\033[31m◆\033[0m");

            else
                printf("%c", maze[i][j]);
        }

        printf("\n");
    }

    printf("\n");
}

void add_crumbs() {
    int i, j;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++)
            if (maze[i][j] != 's' && visited[i][j] == crumb)
                maze[i][j] = '.';
    }
}

int dfs(int row, int col) {
    if (row < 0 || row >= rows || col < 0 || col >= cols)
        return 0;

    if (visited[row][col] == goal)
        return 1;

    if (visited[row][col] == empty) {
        visited[row][col] = crumb; // Trying the new path

        if (dfs(row, col - 1) ||
            dfs(row + 1, col) ||
            dfs(row, col + 1) ||
            dfs(row - 1, col))
            return 1; // Success

        visited[row][col] = empty;
    }

    return 0;
}

void free_maze() {
    for (int i = 0; i < rows; i++) {
        free(maze[i]);
        free(visited[i]);
    }

    free(maze);
    free(visited);
}


int main() {
    init_display();

    get_maze("../data/maze.txt");
    init_visited();

    printf("\nORIGINAL PATH\n");

    print_maze();

    if (!dfs(start_row, start_col))
        printf("\n\aCannot find a path to the goal \n");

    else {
        printf("\n\033[32mSOLVED PATH\033[0m\n");            

        add_crumbs();

        print_maze();
    }

    free_maze();

   return 0; 
}

                




