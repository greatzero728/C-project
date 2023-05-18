#include <stdio.h>

#define NN 15
#define MM (1 << 15)
#define inf 1e7

int n = 15, d[NN][NN]; // the shortest path from u to v.
int dp[MM][NN]; // dp[s][u] : the minimum weighted path end with vertex u and state s.
int prv[MM][NN]; // prv[s][u] : means edge(prv[s][u], u) is in the minimum weighted path end with vertex u and state s.
int ans_path[20], path[20];

void init() {
	for(int i = NN; i--; ) {
		for(int j = NN; j--; ) d[i][j] = inf;
		d[i][i] = 0;
	}
	for(int s = MM; s--; ) {
		for(int i = NN; i--; ) dp[s][i] = inf;
	}
	for(int i = NN; i--; ) dp[1 << i][i] = 0;
}

void solve() {
	init();
	int u, v, w; char c;
	while(~scanf("%d %c%*c %d %d", &u, &c, &v, &w)) {
		if(c == '<') u = u ^ v, v = u ^ v, u = u ^ v;
		if(w < d[u][v]) d[u][v] = w;
	}
	
//	Flod Warshall algorithm O(n ^ 3)
	for(int w = n; w--; ) for(int u = n; u--; ) for(int v = n; v--; ) {
		if(d[u][w] + d[w][v] < d[u][v]) d[u][v] = d[u][w] + d[w][v];
	}
	
//	State dynamic algorithm
	for(int s = 1; s < MM; s++) {
		for(int u = NN; u--; ) if(dp[s][u] < inf) {
			for(int v = NN; v--; ) if(!(s & (1 << v))) {
				int c = s ^ (1 << v);
				if(dp[c][v] > dp[s][u] + d[u][v]) {
					dp[c][v] = dp[s][u] + d[u][v];
					prv[c][v] = u;
				}
			}
		}
	}
	
//	Finding the correct path with pre array
	int ans = 1e9;
	for(int ed = 0; ed < n; ed++) {
		int s = MM - 1, u = ed, sum = 0;
		path[0] = u;
		for(int i = 1; i < n; i++) {
			int prv_u = prv[s][u];
			sum += d[prv_u][u];
			s ^= 1 << u, u = prv_u;
			path[i] = u;
		}
		if(sum < ans) {
			ans = sum;
			for(int i = 0; i < n; i++) ans_path[i] = path[i];
		}
	}
	printf("[");
	for(int i = n; i--; ) printf("%d, ", ans_path[i]);
	printf("%d]\n", ans_path[n - 1]);
}

int main() {
	FILE *fin;
	
	fin = freopen("Donnees/bonus.txt", "r", stdin);
	solve();
	
	return 0;
}