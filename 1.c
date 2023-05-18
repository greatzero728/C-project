#include <stdio.h>

#define NN 505
#define MM 2020
#define inf 0x3f3f3f3f

int q[1010101], qf, qb; // This is queue
int head[NN], nxt[MM], to[MM], E; // These are array for storing the graph
int d[NN]; // d[i] represented the shortest path from src to i
int prv[NN]; // edge(prv[i], i) is inside of shortest path from src to i.

// add edge from vertex u to vertex v. (head-next structure)
void add(int u, int v) {
	nxt[E] = head[u], to[E] = v, head[u] = E++;
}

void init() {
	E = qf = qb = 0;
	for(int i = NN; i--; ) d[i] = inf, head[i] = -1;
}

void solve() {
	init();
	
	int st; scanf("Debut: %d\n", &st);
	int ed; scanf("Fin: %d\n", &ed);
	
	int u, v; char c;
	while(~scanf("%d %c%*c %d", &u, &c, &v)) {
//		if input is u <- v style, then fix it into v -> u by swaping u and v.
		if(c == '<') u = u ^ v, v = u ^ v, u = u ^ v;
		add(u, v);
	}
	
//	bread first search algorithm
	q[qb++] = st, d[st] = 0;
	while(qf < qb) {
		int u = q[qf++];
		if(u == ed) break;
//		search all possible edge from u
		for(int e = head[u]; ~e; e = nxt[e]) {
			int v = to[e];
			if(d[v] > d[u] + 1) {
				d[v] = d[u] + 1, prv[v] = u;
				q[qb++] = v;
			}
		}
	}
	
//	Find the shortest path with prv array
	qb = 0;
	for(int u = ed; ; u = prv[u]) {
		q[qb++] = u;
		if(u == st) break;
	}
	
//	Print the answer
	printf("[");
	for(int i = qb; i--; ) {
		printf("%d", q[i]);
		if(i) printf(", ");
		else puts("]");
	}
}

int main() {
	FILE *fin;
	
	fin = freopen("Donnees/planete1.txt", "r", stdin);
	solve();
	
	fin = freopen("Donnees/planete2.txt", "r", stdin);
	solve();
	
	fin = freopen("Donnees/planete3.txt", "r", stdin);
	solve();
}