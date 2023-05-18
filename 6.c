#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NN 33
#define inf 0x3f3f3f3f

// Swap array
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// mix arr[0] ~ arr[n - 1] in random
void random_shuffle(int arr[], int n) {
    srand(time(NULL));
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(&arr[i], &arr[j]);
    }
}

int f[NN], n = 25;
int d[NN][NN], vst[NN]; // d[i][j] represent the weight of directed edge (i, j)
int path[NN], ans_path[NN];

void init() {
	for(int i = NN; i--; ) {
		for(int j = NN; j--; ) d[i][j] = inf;
		d[i][i] = 0;
		f[i] = i;
	}
}

//Finding the candidate path which pass all vertexes
long long nearest_neighbor(int start) {
    random_shuffle(f, n + 1);
    int cur = start;
    for(int i = 0; i <= n; i++) {
        path[i] = cur, vst[cur] = 1;
        int min_dst = inf + 1, nxt = -1;
//		Set edge(u, i) in random.
        for(int j = 0, u ; j <= n; j++) {
        	u = f[j];
        	if(!vst[u] && d[cur][u] < min_dst) {
        		min_dst = d[cur][u], nxt = u;
        	}
        }
        cur = nxt;
    }
    
//	Calculate the weight of this shortest path.
    vst[start] = 0;
    long long total_dist = 0;
    for(int i = 1; i < n; i++) {
        total_dist += d[path[i - 1]][path[i]];
    }
    return total_dist;
}

void solve() {
	init();
	int u, v, w; char c;
	while(~scanf("%d %c%*c %d %d", &u, &c, &v, &w)) {
//		if input is u <- v style, then fix it into v -> u by swaping u and v.
		if(c == '<') u = u ^ v, v = u ^ v, u = u ^ v;
		if(w < d[u][v]) d[u][v] = w;
	}
	
	long long ans = 1e18;
//	Here repeat the randomizing algorithm which finding nearest neighbor for select.
	for(int step = 10000; step--; ) {
//		Set every vertex as src, and find the nearest neighbor from last visited vertex
		for(int i = 0; i <= n; i++) {
			for(int j = 0; j <= n; j++) vst[j] = 0;
			long long dst = nearest_neighbor(i);
			if(dst < ans) {
				ans = dst;
				for(int j = 0; j <= n; j++) ans_path[j] = path[j];
			}
		}
	}
	
	printf("[");
	for(int i = 0; i < n; i++) {
		if(i) printf(", ");
		printf("%d", ans_path[i]);
	}
	puts("]");
}

int main() {
	srand(time(0));
	
	FILE *fin = freopen("Donnees/terrain3.txt", "r", stdin);
	solve();
}