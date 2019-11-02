#include <cstdio>
#include <cstdlib>

struct Edge;

struct Node
{
	int n, nAdj, dist;
	Edge **adj;
	Node *parent;
};

struct Edge
{
	Node *v1, *v2;
	int w;
};void readGraph(Node **G, int n, int m)
{
	int a,b,w;
	for(int i=0;i<m;i++)
	{
		scanf("%d %d %d",&a,&b,&w);
		Edge *e = new Edge;
		e->w = w;
		e->v1 = G[a];
		e->v2 = G[b];
		G[a]->adj[G[a]->nAdj++]=e;
		e = new Edge;
		e->w = w;
		e->v1 = G[b];
		e->v2 = G[a];
		G[b]->adj[G[b]->nAdj++]=e;
	}
}

bool BellmanFord(Node **G, int n)
{
	int count=0;
	for(int i=0; i<n; i++)
		count+=G[i]->nAdj;
	count/=2;
	Edge **edges = new Edge*[count];
	count=0;
	for(int i=0; i<n; i++)
		for(int j=0; j<G[i]->nAdj; j++)
			if(G[i]->adj[j]->v1->n<G[i]->adj[j]->v2->n)
				edges[count++]=G[i]->adj[j];
	for(int i=0; i<n-1; i++)
		for(int j=0; j<count; j++)
			if(edges[j]->v1->dist + edges[j]->w < edges[j]->v2->dist)
			{
				edges[j]->v2->dist = edges[j]->v1->dist + edges[j]->w;
				edges[j]->v2->parent = edges[j]->v1;
			}
	for(int i=0; i<count; i++)
		if(edges[i]->v1->dist + edges[i]->w < edges[i]->v2->dist)
			return false;
	return true;
}

void printPath(Node *dest)
{
	if(dest->parent)
		printPath(dest->parent);
	printf("%d ",dest->n);
}

int main()
{
	int n,m,s,t;
	scanf("%d %d %d %d",&n,&m,&s,&t);
	Node **G = (Node**) malloc(n*sizeof(Node*));
	for(int i=0; i<n; i++)
	{
		G[i]=new Node;
		G[i]->n=i;
		G[i]->adj = (Edge**) malloc(n*sizeof(Edge*));
		G[i]->nAdj = 0;
		G[i]->dist = 100000001;
		G[i]->parent = NULL;
	}
	Node *dest = G[t];
	G[s]->dist=0;
	readGraph(G,n,m);
	if(!BellmanFord(G,n))
	{
		printf("Found cycle which has weight <0!\n");
		delete[] G;
		return 0;
	}
	printPath(dest);
	printf("\n");
	delete[] G;
	return 0;
}
