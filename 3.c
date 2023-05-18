#include <stdio.h>
#include <string.h>

#define NN 1010
#define MM 202020
#define inf 1e9

double cost[NN];
char type[NN][20], s[20];
int n_cost;

// Input type.txt. here if type[i] is "Montagen" or "Marais", then change cost[i] as 1e10.
void input_type() {
	scanf("%d", &n_cost);
	for(int i = 0; i < n_cost; i++) {
		scanf("%s %lf", type + i, cost + i);
		if(!strcmp(type[i], "Montagne")) cost[i] = 1e10;
		if(!strcmp(type[i], "Marais")) cost[i] = 1e10;
	}
}

// wei[i] means the weight of all edges into i
double wei[NN];

// Update wei[i] with type.txt
void input_sommet() {
	int u;
	while(~scanf("%d %s", &u, s)) {
		for(int i = n_cost; i--; ) if(!strcmp(s, type[i])) {
			wei[u] = cost[i]; break;
		}
	}
}

int prv[NN], st, ed; // edge(prv[i], i) is inside of shortest path from src to i.
int head[NN], nxt[MM], to[MM], E; // These are array for storing the graph
double d[NN]; // d[i] represented the shortest path from src to i

void init() {
	for(int i = NN; i--; ) {
		head[i] = -1, d[i] = inf;
	}
}

// add edge from vertex u to vertex v. (head-next structure)
void add(int u, int v) {
	nxt[E] = head[u], to[E] = v, head[u] = E++;
}

int q[1010101], qf, qb; // This is queue=

void solve() {
	scanf("Debut: %d\n", &st);
	scanf("Fin: %d\n", &ed);
	
	init();
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
//		search all possible edge from u
		for(int e = head[u]; ~e; e = nxt[e]) {
			int v = to[e];
			if(d[v] > d[u] + wei[v]) {
				d[v] = d[u] + wei[v], q[qb++] = v;
				prv[v] = u;
			}
		}
	}
	
//	Find the shortest path with prv array
	qf = qb = 0;
	for(int u = ed; ; u = prv[u]) {
		q[qb++] = u;
		if(u == st) break;
	}
	printf("[");
	for(int i = qb; i-- > qf; ) {
		printf("%d", q[i]);
		if(i == qf) puts("]");
		else printf(", ");
	}
	return ;
}

int main() {
	FILE *fin;
	
	fin = freopen("Donnees/type1.txt", "r", stdin);
	input_type();
	fin = freopen("Donnees/typeSommet1.txt", "r", stdin);
	input_sommet();
	fin = freopen("Donnees/terrain1.txt", "r", stdin);
	solve();
	
	fin = freopen("Donnees/type2.txt", "r", stdin);
	input_type();
	fin = freopen("Donnees/typeSommet2.txt", "r", stdin);
	input_sommet();
	fin = freopen("Donnees/terrain2.txt", "r", stdin);
	solve();
}