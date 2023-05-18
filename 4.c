#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define NN 101
#define MM 2020
#define inf 0x3f3f3f3f

#define V 33

// Returns the minimum of two integers.
int min(int a, int b) {
    return (a < b ? a : b);
}

// Returns true if there is a path from source to sink in residual graph.
// Also fills parent[] to store the path.
bool bfs(int rGraph[V][V], int s, int t, int parent[]) {
    bool visited[V];
    memset(visited, 0, sizeof(visited));
    visited[s] = true;
    parent[s] = -1;

    // Create a queue, enqueue source vertex, and mark it as visited.
    int queue[V];
    int front = 0, rear = 0;
    queue[rear++] = s;

    while (front < rear) {
        int u = queue[front++];
        for (int v = 0; v < V; v++) {
            if (visited[v] == false && rGraph[u][v] > 0) {
                visited[v] = true;
                parent[v] = u;
                queue[rear++] = v;
            }
        }
    }

    // If we can reach the sink in BFS starting from source, then return true, else false.
    return (visited[t] == true);
}

// A function to find the maximum flow in a given directed graph using Ford-Fulkerson algorithm with Edmonds-Karp technique.
int ford_fulkerson(int graph[V][V], int source, int sink) {
    int rGraph[V][V];  // Residual graph
    for (int u = 0; u < V; u++)
        for (int v = 0; v < V; v++)
             rGraph[u][v] = graph[u][v];

    int parent[V];  // This array is filled by BFS and to store path

    int max_flow = 0;  // Initialize max flow

    // Augment the flow while there is path from source to sink
    while (bfs(rGraph, source, sink, parent)) {
        // Find minimum residual capacity of the edges along the path filled by BFS. Or we can say find the maximum flow through the path found.
        int path_flow = INT_MAX;
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        // Update residual capacities of the edges and reverse edges along the path
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
        
        // Add path flow to overall flow
        max_flow += path_flow;
    }

    // Return maximum flow
    return max_flow;
}

int N = 14, src = 0, tar = 13;
int d[NN][NN];

void init() {
	for(int i = N; i--; ) {
		for(int j = N; j--; ) d[i][j] = inf;
		d[i][i] = 0;
	}
}

// add edge from vertex u to vertex v which weight is w
void add_edge(int u, int v, int w) {
	if(w < d[u][v]) d[u][v] = w;
}

void input() {
	// add_edge edge from src to [A, B, C, D, E]
	add_edge(src, 1, 70);
	add_edge(src, 2, 30);
	add_edge(src, 3, 40);
	add_edge(src, 4, 55);
	add_edge(src, 5, 15);
	
	// add_edge edge from [F, G, H, I, J, K, L] to tar
	add_edge(6, tar, 5);
	add_edge(7, tar, 21);
	add_edge(8, tar, 16);
	add_edge(9, tar, 45);
	add_edge(10, tar, 50);
	add_edge(11, tar, 20);
	add_edge(12, tar, 7);
	
	// add_edge edge from [A, B, C, D, E] to [F, G, H, I, J, K, L]
	add_edge(1, 7, 30), add_edge(1, 10, 60); // edges from A
	add_edge(2, 6, 15), add_edge(2, 9, 35), add_edge(2, 11, 5); // edges from B
	add_edge(3, 10, 25), add_edge(3, 12, 50); // edges from C
	add_edge(4, 7, 11), add_edge(4, 8, 12), add_edge(4, 9, 17), add_edge(4, 10, 10), add_edge(4, 11, 4); // edges from D
	add_edge(5, 6, 5), add_edge(5, 7, 10), add_edge(5, 8, 2), add_edge(5, 10, 6), add_edge(5, 12, 7); // edges from E
}

void solve() {
	init();
	input();
	
	int graph[V][V];
	memset(graph, 0, sizeof graph);
	
	for(int i = 1; i <= 5; i++) {
		for(int j = 6; j <= 12; j++) {
			if(d[src][i] + d[i][j] + d[j][tar] <= 60) {
				graph[src][i] = 1, graph[i][j] = 1, graph[j][tar] = 1;
			}
		}
	}
	int ans = ford_fulkerson(graph, src, tar);
	printf("%d\n", ans);
}

int main() {
	
	solve();
}