#ifndef _GRAPH_MAKER_H_
#define _GRAPH_MAKER_H_ 1

#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <time.h>
#include "data_maker.h"
#include "rand_maker.h"

const int N = 1e6+5, M = (int)(1e6+5)<<1;

class Edge {
public:
	int v, w, nxt;
	Edge();
	Edge(int a, int b);
	Edge(int a, int b, int c);
	~Edge();
};
Edge::Edge() : v(0), w(0), nxt(0) {}
Edge::Edge(int a, int b) : v(a), w(1), nxt(b) {}
Edge::Edge(int a, int b, int c) : v(a), w(b), nxt(c) {}
Edge::~Edge() {}

class Union {
public:
	int fa[N];
	Union();
	Union(int x);
	~Union();
	int find(int x);
	bool merge(int u, int v);
};
Union::Union() {}
Union::Union(int x) {
	for(int i=1;i<=x;i++) {
		fa[i] = i;
	}
}
Union::~Union() {}
int Union::find(int x) {
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
bool Union::merge(int x, int y) {
	int f1 = find(x), f2 = find(y);
	if(f1 == f2) return false;
	fa[f1] = f2;
	return true;
}

class GraphMaker : public DataMaker{
private:
	int n, m;
	int ne, h[N];
	Edge e[M];
public:
	GraphMaker();
	~GraphMaker();
	
	void add(int u, int v);
	void add(int u, int v, int w);
	
	bool Judge(int n, int m);
	bool Judge(int n, int m, int w1, int w2);
	void GenGraph(int n, int m);
	void GenGraph(int n, int m, int w1, int w2);
//	void DAG(int n, int m);                 // In Progress
//	void DAG(int n, int m, int w1, int w2); // In Progress
	void Tree(int n);
	void Tree(int n, int w1, int w2);
	void PrintNoVal(int n);
	void PrintVal(int n);
};
GraphMaker::GraphMaker() : ne(0) {memset(h, 0, sizeof(h)); memset(e, 0, sizeof(e));}
GraphMaker::~GraphMaker() {}

void GraphMaker::add(int u, int v) {
	e[++ne] = Edge(v, h[u]);
	h[u] = ne;
}
void GraphMaker::add(int u, int v, int w) {
	e[++ne] = Edge(v, w, h[u]);
	h[u] = ne;
}

bool GraphMaker::Judge(int n, int m) {
	if(n < 1 || n > N || m < 1 || m > N) {
		std::fprintf(flog, "Error: This graph is too big to be created. ");
		return false;
	}
	return true;
}
bool GraphMaker::Judge(int n, int m, int w1, int w2) {
	if(n < 1 || n > N || m < 1 || m > N
		|| w1 < -1e9 || w1 > 1e9 || w2 < -1e9 || w2 > 1e9 || w1 > w2) {
		std::fprintf(flog, "Error: This graph is too big to be created. ");
		return false;
	}
	return true;
}
void GraphMaker::GenGraph(int n, int m) {
	if(!Judge(n, m)) return;
	for(int i=1;i<=m;i++) {
		int u = randint(1, n), v = randint(1, n);
		add(u, v);
		add(v, u);
	}
}
void GraphMaker::GenGraph(int n, int m, int w1, int w2) {
	if(!Judge(n, m, w1, w2)) return;
	for(int i=1;i<=m;i++) {
		int u = randint(1, n), v = randint(1, n), w = randint(w1, w2);
		add(u, v, w);
		add(v, u, w);
	}
}
void GraphMaker::Tree(int n) {
	if(!Judge(n, n-1)) return;
	Union a = Union(n);
	int tot = 0;
	while(tot < n - 1) {
		int u = randint(1, n), v = randint(1, n);
		if(a.merge(u, v)) {
			add(u, v);
			++tot;
		}
	}
}
void GraphMaker::Tree(int n, int w1, int w2) {
	if(!Judge(n, n-1, w1, w2)) return;
	Union a = Union(n);
	int tot = 0;
	while(tot < n - 1) {
		int u = randint(1, n), v = randint(1, n), w = randint(w1, w2);
		if(a.merge(u, v)) {
			add(u, v, w);
			++tot;
		}
	}
}
void GraphMaker::PrintNoVal(int n) {
	for(int u=1;u<=n;u++) {
		for(int i=h[u];i;i=e[i].nxt) {
			fprintf(fin, "%d %d\n", u, e[i].v);
		}
	}
}
void GraphMaker::PrintVal(int n) {
	for(int u=1;u<=n;u++) {
		for(int i=h[u];i;i=e[i].nxt) {
			fprintf(fin, "%d %d %d\n", u, e[i].v, e[i].w);
		}
	}
}

#endif
