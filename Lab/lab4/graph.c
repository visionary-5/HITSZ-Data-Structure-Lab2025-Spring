#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define max_dis 100000

typedef char vextype[20];

typedef struct {
    int N, E;//N是顶点数，E是边数
    int** matrix;//储存邻接矩阵
    vextype* vertex;//存储节点的名字
} Graph;

Graph createGraph(int n);
int isConnected(Graph g);
void nodeDegree(Graph g, int* node_degree);
double clusteringCoefficient(Graph g);
int Diameter(Graph g);
int Radius(Graph g);
int dijkstra(Graph g, int start, int end, int* path);
void printPath(int d, int* diameter_path, Graph g);

// DFS辅助函数
void dfs_helper(Graph g, int node, int* visited) {
    visited[node] = 1;
    for (int i = 0; i < g.N; i++) {
        if (g.matrix[node][i] != max_dis && g.matrix[node][i] != 0 && !visited[i]) {
            dfs_helper(g, i, visited);
        }
    }
}

/**
 * 创建一个节点数为n的图
 * @param n 节点个数
 * @return 返回这个图
 */
Graph createGraph(int n) {
    int i, j;
    Graph g;
    g.N = n;
    g.matrix = (int**)malloc(sizeof(int*) * g.N);
    for (i = 0; i < n; i++) {
        g.matrix[i] = (int*)malloc(sizeof(int) * g.N);
    }
    for (i = 0; i < g.N; i++) {
        for (j = 0; j < g.N; j++) {
            g.matrix[i][j] = max_dis;
        }
    }
    for (i = 0; i < g.N; i++) {
        g.matrix[i][i] = 0;
    }
    g.vertex = (vextype*)malloc(sizeof(vextype) * g.N);
    return g;
}


/**
 * 根据距离d和路径数组path输出路径，这样就不需要路径的节点数也能正确输出路径
 * @param d 路径长度
 * @param diameter_path 储存路径的数组
 * @param g 图
 */
void printPath(int d, int *diameter_path, Graph g)
{
    int k = 0;
    int path_length = 0;
    printf("Path: ");
    do {
        printf("%s->", g.vertex[diameter_path[k]]);
        path_length += g.matrix[diameter_path[k]][diameter_path[k + 1]];
        k++;
    } while (path_length < d);
    printf("%s\n", g.vertex[diameter_path[k]]);
}


/**
 * 判断图是否连通
 * @param g 图
 * @return 连通返回1，否则返回0
 */
int isConnected(Graph g) {
    int* visited = (int*)malloc(sizeof(int) * g.N);
    for (int i = 0; i < g.N; i++) {
        visited[i] = 0;
    }
    
    // 从节点0开始DFS
    dfs_helper(g, 0, visited);
    
    // 检查是否所有节点都被访问
    for (int i = 0; i < g.N; i++) {
        if (!visited[i]) {
            free(visited);
            return 0; // 不连通
        }
    }
    
    free(visited);
    return 1; // 连通
}


/**
 * 计算每个点的度
 * @param g 图
 * @param node_degree 将每个点的度写到这个数组中
 */
void nodeDegree(Graph g, int *node_degree) {
    for (int i = 0; i < g.N; i++) {
        node_degree[i] = 0;
        for (int j = 0; j < g.N; j++) {
            if (g.matrix[i][j] != max_dis && g.matrix[i][j] != 0) {
                node_degree[i]++;
            }
        }
    }
}

/**
 * 计算图的聚类系数
 * @param g 图
 * @return 返回聚类系数
 */
double clusteringCoefficient(Graph g) {
    double totalCoefficient = 0.0;
    
    for (int i = 0; i < g.N; i++) {
        // 找到节点i的所有邻居
        int* neighbors = (int*)malloc(sizeof(int) * g.N);
        int neighborCount = 0;
        
        for (int j = 0; j < g.N; j++) {
            if (g.matrix[i][j] != max_dis && g.matrix[i][j] != 0) {
                neighbors[neighborCount++] = j;
            }
        }
        
        // 如果邻居数量小于2，聚类系数为0
        if (neighborCount < 2) {
            free(neighbors);
            continue;
        }
        
        // 计算邻居之间的实际边数
        int actualEdges = 0;
        for (int j = 0; j < neighborCount; j++) {
            for (int k = j + 1; k < neighborCount; k++) {
                if (g.matrix[neighbors[j]][neighbors[k]] != max_dis && 
                    g.matrix[neighbors[j]][neighbors[k]] != 0) {
                    actualEdges++;
                }
            }
        }
        
        // 计算可能的最大边数
        int possibleEdges = neighborCount * (neighborCount - 1) / 2;
        
        // 计算这个节点的聚类系数
        double nodeCoefficient = (double)actualEdges / possibleEdges;
        totalCoefficient += nodeCoefficient;
        
        free(neighbors);
    }
    
    // 返回平均聚类系数
    return totalCoefficient / g.N;
}


/**
 * 使用dijkstra算法计算单源最短路径
 * @param g 图
 * @param start 起点
 * @param end 终点
 * @param path 从start到end的路径, [start,...,end]
 * @return 路径长度
 */
int dijkstra(Graph g, int start, int end, int *path)
{
    int* dist = (int*)malloc(sizeof(int) * g.N);
    int* prev = (int*)malloc(sizeof(int) * g.N);
    int* visited = (int*)malloc(sizeof(int) * g.N);
    
    // 初始化
    for (int i = 0; i < g.N; i++) {
        dist[i] = max_dis;
        prev[i] = -1;
        visited[i] = 0;
    }
    dist[start] = 0;
    
    // Dijkstra算法主循环
    for (int count = 0; count < g.N; count++) {
        // 找到未访问的距离最小的节点
        int minDist = max_dis;
        int u = -1;
        for (int i = 0; i < g.N; i++) {
            if (!visited[i] && dist[i] < minDist) {
                minDist = dist[i];
                u = i;
            }
        }
        
        // 如果没有找到更近的节点，或者已经找到终点，则退出
        if (u == -1) break;
        
        visited[u] = 1;
        
        // 更新u的所有邻居的距离
        for (int v = 0; v < g.N; v++) {
            if (!visited[v] && g.matrix[u][v] != max_dis) {
                int newDist = dist[u] + g.matrix[u][v];
                if (newDist < dist[v]) {
                    dist[v] = newDist;
                    prev[v] = u;
                }
            }
        }
    }
    
    // 构建路径
    if (dist[end] == max_dis) {
        // 不存在路径
        free(dist);
        free(prev);
        free(visited);
        return -1;
    }
    
    // 从终点回溯到起点，构建路径
    int pathLen = 0;
    int current = end;
    int* tempPath = (int*)malloc(sizeof(int) * g.N);
    
    while (current != -1) {
        tempPath[pathLen++] = current;
        current = prev[current];
    }
    
    // 反转路径（从起点到终点）
    for (int i = 0; i < pathLen; i++) {
        path[i] = tempPath[pathLen - 1 - i];
    }
    
    int result = dist[end];
    
    free(dist);
    free(prev);
    free(visited);
    free(tempPath);
    
    return result;
}


/**
 * 计算图的直径。提示：Floyd算法
 * @param g 图
 * @return 直径的长度
 */
int Diameter(Graph g) {
    // 复制邻接矩阵
    int** dist = (int**)malloc(sizeof(int*) * g.N);
    for (int i = 0; i < g.N; i++) {
        dist[i] = (int*)malloc(sizeof(int) * g.N);
        for (int j = 0; j < g.N; j++) {
            dist[i][j] = g.matrix[i][j];
        }
    }
    
    // Floyd-Warshall算法
    for (int k = 0; k < g.N; k++) {
        for (int i = 0; i < g.N; i++) {
            for (int j = 0; j < g.N; j++) {
                if (dist[i][k] != max_dis && dist[k][j] != max_dis && 
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    
    // 找出最大距离，即直径
    int diameter = 0;
    for (int i = 0; i < g.N; i++) {
        for (int j = 0; j < g.N; j++) {
            if (i != j && dist[i][j] != max_dis && dist[i][j] > diameter) {
                diameter = dist[i][j];
            }
        }
    }
    
    // 释放内存
    for (int i = 0; i < g.N; i++) {
        free(dist[i]);
    }
    free(dist);
    
    return diameter;
}


/**
 * 计算图的半径
 * @param g 图
 * @return 半径长度
 */
int Radius(Graph g) {
    // 复制邻接矩阵
    int** dist = (int**)malloc(sizeof(int*) * g.N);
    for (int i = 0; i < g.N; i++) {
        dist[i] = (int*)malloc(sizeof(int) * g.N);
        for (int j = 0; j < g.N; j++) {
            dist[i][j] = g.matrix[i][j];
        }
    }
    
    // Floyd-Warshall算法
    for (int k = 0; k < g.N; k++) {
        for (int i = 0; i < g.N; i++) {
            for (int j = 0; j < g.N; j++) {
                if (dist[i][k] != max_dis && dist[k][j] != max_dis && 
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    
    // 计算每个节点的离心率，并找出最小值
    int radius = max_dis;
    for (int i = 0; i < g.N; i++) {
        int eccentricity = 0;
        for (int j = 0; j < g.N; j++) {
            if (i != j && dist[i][j] != max_dis && dist[i][j] > eccentricity) {
                eccentricity = dist[i][j];
            }
        }
        if (eccentricity < radius && eccentricity > 0) {
            radius = eccentricity;
        }
    }
    
    // 释放内存
    for (int i = 0; i < g.N; i++) {
        free(dist[i]);
    }
    free(dist);
    
    return radius;
}


int main() {
    int node_num;
    int edge_num;

    scanf("%d %d", &node_num, &edge_num);

    Graph g = createGraph(node_num);
    for(int i = 0; i < node_num; i++) {
        sprintf(g.vertex[i], "%d", i);
    }

    for (int i = 0; i < edge_num; i++) {
        int start_idx, end_idx, weight;
        scanf("%d %d %d", &start_idx, &end_idx, &weight);
        g.matrix[start_idx][end_idx] = weight;
        g.matrix[end_idx][start_idx] = weight;
    }
    printf("connected: %d\n", isConnected(g));

    int *degree = (int *)malloc(sizeof(int) * g.N);
    nodeDegree(g, degree);
    printf("degree distribution:\n");
    for(int i=0; i<g.N; i++)
    {
        printf("node%s:%d,", g.vertex[i], degree[i]);
    }
    printf("\n");
    double c = clusteringCoefficient(g);
    printf("clustering coefficient:%f\n", c);

    if (isConnected(g))
    {
        int* short_path = (int*)malloc(sizeof(int) * g.N);
        int dis = dijkstra(g, 1, 3, short_path);
        printf("the minimum fare between 1 and 3: %d\n", dis);
        printPath(dis, short_path, g);
        free(short_path);
        int d = Diameter(g);
        printf("diameter:%d\n", d);

        int r = Radius(g);
        printf("radius:%d\n", r);
    }
    
    // 释放内存
    for (int i = 0; i < g.N; i++) {
        free(g.matrix[i]);
    }
    free(g.matrix);
    free(g.vertex);
    free(degree);

    return 0;
}