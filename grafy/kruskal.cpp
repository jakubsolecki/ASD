#include <cstdio>
#include <cstdlib>
#include <algorithm>

struct Edge;

struct Node
{
	int n, nAdj, rank;
	Edge **adj;
	Node *parent, *parentFau;
};

struct Edge
{
	Node *v1, *v2;
	int w;
};

struct myCompare{
	bool operator()(const Edge *a, const Edge *b) const
	{
		return a->w<b->w;
	}
};

Node* find(Node *n)
{
	if(n->parentFau!=n) n->parentFau=find(n->parentFau);
	return n->parentFau;
}

void unionF(Node *a, Node *b)
{
	a=find(a);
	b=find(b);
	if(a->rank > b->rank) b->parentFau = a;
	else
	{
		a->parentFau = b;
		if(a->rank==b->rank) b->rank++;
	}
}

void readGraph(Node **G, int n, int m)
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

void Kruskal(Node **G, int n)
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
	std::sort(edges,(edges+count),myCompare());
	for(int i=0; i<count; i++)
		if(find(edges[i]->v1)!=find(edges[i]->v2))
		{
			unionF(edges[i]->v1,edges[i]->v2);
			edges[i]->v1->parent=edges[i]->v2;
		}
	delete edges;
}

int main()
{
	int n,m;
	scanf("%d %d",&n,&m);
	Node **G = (Node**) malloc(n*sizeof(Node*));
	for(int i=0; i<n; i++)
	{
		G[i]=new Node;
		G[i]->n=i;
		G[i]->adj = (Edge**) malloc(n*sizeof(Edge*));
		G[i]->nAdj = G[i]->rank = 0;
		G[i]->parentFau = G[i];
		G[i]->parent = NULL;
	}
	readGraph(G,n,m);
	Kruskal(G,n);
	for(int i=0; i<n; i++)
		printf("Vertex %d: parent=%d\n",i,G[i]->parent?G[i]->parent->n:-1);
	delete[] G;
	return 0;
}
