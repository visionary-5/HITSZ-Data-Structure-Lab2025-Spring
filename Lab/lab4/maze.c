#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 100

typedef struct {
    int x, y;
} Point;

typedef struct Node {
    int x, y;
    int g, h, f;
    struct Node *parent;
} Node;

char *directionName[] = {"R", "D", "L", "U"};
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};
char dirSymbol[] = {'R', 'D', 'L', 'U'};

int width, height;
int visited[MAX][MAX];
int minSteps = -1;
char pathOutput[10000];
int pathLen = 0;

// DFS part
int dfs(char **maze, int x, int y, int steps) {
    if (maze[x][y] == '$') {
        if (minSteps == -1 || steps < minSteps)
            minSteps = steps;
        return 1;
    }

    visited[x][y] = 1;

    for (int d = 0; d < 4; d++) {
        int nx = x + dx[d], ny = y + dy[d];
        if (nx >= 0 && nx < width && ny >= 0 && ny < height &&
            !visited[nx][ny] && (maze[nx][ny] == '0' || maze[nx][ny] == '$')) {
            printf("->%s", directionName[d]);
            pathOutput[pathLen++] = dirSymbol[d];
            if (dfs(maze, nx, ny, steps + 1)) return 1;
            printf("->%s", directionName[(d + 2) % 4]); // Backtrack
            pathOutput[pathLen++] = dirSymbol[(d + 2) % 4];
        }
    }
    return 0;
}

// Manhattan distance
int manhattan(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

// A* priority queue compare function
int cmp(const void *a, const void *b) {
    Node *n1 = *(Node **)a;
    Node *n2 = *(Node **)b;
    if (n1->f != n2->f) return n1->f - n2->f;
    if (n1->x != n2->x) return n2->x - n1->x;
    return n2->y - n1->y;
}

// A* part
void findDoor(char **maze, int width, int height, int startX, int startY, int endX, int endY) {
    int visited[MAX][MAX] = {0};
    Node *openSet[MAX * MAX];
    int openSize = 0;

    Node *start = (Node *)malloc(sizeof(Node));
    start->x = startX;
    start->y = startY;
    start->g = 0;
    start->h = manhattan(startX, startY, endX, endY);
    start->f = start->g + start->h;
    start->parent = NULL;
    openSet[openSize++] = start;

    Node *endNode = NULL;

    while (openSize > 0) {
        qsort(openSet, openSize, sizeof(Node *), cmp);
        Node *curr = openSet[0];

        // Remove current from openSet
        for (int i = 1; i < openSize; i++) {
            openSet[i - 1] = openSet[i];
        }
        openSize--;

        printf("->(%d,%d)", curr->x, curr->y);

        if (curr->x == endX && curr->y == endY) {
            endNode = curr;
            break;
        }

        visited[curr->x][curr->y] = 1;

        for (int d = 0; d < 4; d++) {
            int nx = curr->x + dx[d], ny = curr->y + dy[d];
            if (nx >= 0 && nx < width && ny >= 0 && ny < height &&
                !visited[nx][ny] && (maze[nx][ny] == '0' || maze[nx][ny] == '#')) {

                Node *neighbor = (Node *)malloc(sizeof(Node));
                neighbor->x = nx;
                neighbor->y = ny;
                neighbor->g = curr->g + 1;
                neighbor->h = manhattan(nx, ny, endX, endY);
                neighbor->f = neighbor->g + neighbor->h;
                neighbor->parent = curr;

                openSet[openSize++] = neighbor;
                visited[nx][ny] = 1;
            }
        }
    }

    printf("\n");

    // 输出路径
    Point path[MAX * MAX];
    int len = 0;
    while (endNode != NULL) {
        path[len].x = endNode->x;
        path[len].y = endNode->y;
        endNode = endNode->parent;
        len++;
    }

    for (int i = len - 1; i >= 0; i--) {
        printf("->(%d,%d)", path[i].x, path[i].y);
    }
    printf("\n");
}

int main() {
    scanf("%d %d\n", &width, &height);
    char **maze = (char **)malloc(width * sizeof(char *));
    for (int i = 0; i < width; i++) {
        maze[i] = (char *)malloc(height + 1);
        scanf("%s", maze[i]);
    }

    int startX = 0, startY = 0;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (maze[i][j] == '*') {
                startX = i;
                startY = j;
            }
        }
    }

    dfs(maze, startX, startY, 0);
    printf("\n%d\n", minSteps);

    int keyX = 0, keyY = 0, endX = 0, endY = 0;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (maze[i][j] == '$') {
                keyX = i;
                keyY = j;
            }
            if (maze[i][j] == '#') {
                endX = i;
                endY = j;
            }
        }
    }

    findDoor(maze, width, height, keyX, keyY, endX, endY);

    for (int i = 0; i < width; i++) {
        free(maze[i]);
    }
    free(maze);
    return 0;
}
