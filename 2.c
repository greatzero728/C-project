#include <stdio.h>

#define NN 505
#define MM 202020
#define inf 0x3f3f3f3f

int q[1010101], qf, qb; // This is queue
int head[NN], nxt[MM], to[MM], wei[MM], E; // These are array for storing the graph
int d[NN]; // d[i] represented the shortest path from src to i
int prv[NN]; // edge(prv[i], i) is inside of shortest path from src to i.

// add edge from vertex u to vertex v. (head-next structure)
void add(int u, int v, int w) {
	nxt[E] = head[u], to[E] = v, wei[E] = w, head[u] = E++;
}

void init() {
	E = qf = qb = 0;
	for(int i = NN; i--; ) {
		head[i] = -1;
		d[i] = inf;
	}
}

void solve() {
	int st; scanf("Debut: %d\n", &st);
	int ed; scanf("Fin: %d\n", &ed);
	
	init();
	int u, v, w; char c;
	while(~scanf("%d %c%*c %d %d", &u, &c, &v, &w)) {
//		if input is u <- v style, then fix it into v -> u by swaping u and v.
		if(c == '<') u = u ^ v, v = u ^ v, u = u ^ v;
		add(u, v, w);
	}
	
//	bread first search algorithm
	q[qb++] = st, d[st] = 0;
	while(qf < qb) {
		int u = q[qf++];
//		search all possible edge from u
		for(int e = head[u]; ~e; e = nxt[e]) {
			int v = to[e];
			if(d[v] > d[u] + wei[e]) {
				d[v] = d[u] + wei[e], q[qb++] = v;
				prv[v] = u;
			}
		}
	}
	
//	Find the shortest path with prv array
	qb = 0;
	for(int u = ed; ; u = prv[u]) {
		q[qb++] = u;
		if(u == st) break;
	}
	printf("[");
	for(int i = qb; i--; ) {
		printf("%d", q[i]);
		if(i) printf(", ");
		else puts("]");
	}
}

int main() {
	FILE *fin;
	
	fin = freopen("Donnees/planete4.txt", "r", stdin);
	solve();
	
	fin = freopen("Donnees/planete5.txt", "r", stdin);
	solve();
	
	fin = freopen("Donnees/planete6.txt", "r", stdin);
	solve();
}