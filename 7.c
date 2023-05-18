#include <stdio.h>

#define NN 33

int n = 25;
int w[NN], c[NN]; // w is weight, c is nutritional value.
int select[NN]; // answer

void solve() {
	for(int i = 0; i < n; i++) scanf("%*d %d %d", w + i, c + i);
	
//	state dynamic algorithm
	int ans = -1, S;
	for(int s = 1 << n; s--; ) {
		int W = 0, C = 0;
		for(int i = n; i--; ) if((1 << i) & s) {
			W += w[i], C += c[i];
		}
//		This means the state s satisfying the constraint.
//		Maximum weight is not large than 40 kg
		if(W <= 40 && C > ans) ans = C, S = s;
	}
	
	int nn = 0;
	for(int i = 0; i < n; i++) if((1 << i) & S) {
		select[nn++] = i;
	}
	
	printf("[");
	for(int i = 0; i < nn; i++) {
		if(i) printf(", ");
		printf("%d", select[i]);
	}
	puts("]");
}

int main() {
	FILE *fin;
	
	fin = freopen("Donnees/base.txt", "r", stdin);
	solve();
	
	return 0;
}