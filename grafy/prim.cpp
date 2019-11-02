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
};

struct Heap
{
	public:
		Heap(Node **G,int n)
		{
			nodes = G;
			size = n;
			positions = (int*) malloc(n*sizeof(int));
			for(int i=0;i<n;i++)
				positions[G[i]->n]=i;
			for(int i=parent(n-1);i>=0;i--)
			{
				heapify(i);
			}
		}
		~Heap()
		{
			delete[] positions;
		}
		Node* extractMin()
		{	
			Node *ret = nodes[0];
			size--;
			positions[nodes[0]->n]=size;
			positions[nodes[size]->n]=0;
			nodes[0]=nodes[size];
			nodes[size]=ret;
			if(size>0) heapify(size-1);
			return ret;
		}
		void print()
		{
			for(int j=0;j<size;j++)
				printf("%d: dist=%d\n",nodes[j]->n,nodes[j]->dist);
		}
		void decreaseKey(int n, int key)
		{
			int pos=positions[n];
			if(pos==-1) return;
			nodes[pos]->dist=key;
			while(pos>0&&nodes[parent(pos)]>nodes[pos])
			{
				int t = positions[pos];
				positions[pos]=positions[parent(pos)];
				positions[parent(pos)]=t;
				Node *tmp=nodes[pos];
				nodes[pos]=nodes[parent(pos)];
				nodes[parent(pos)]=tmp;
				pos=parent(pos);
			}
		}
		bool empty() { return size==0; }
	private:
		int size;
		Node **nodes;
		int left(int i) { return 2*i+1; }
		int right(int i) { return 2*i+2; }
		int parent(int i) { return i/2; }
		int *positions;
		void heapify(int i)
		{
			int max_ind = i;
			if(left(i)<size && nodes[left(i)]->dist < nodes[max_ind]->dist)
				max_ind=left(i);
			if(right(i)<size && nodes[right(i)]->dist < nodes[max_ind]->dist)
				max_ind=right(i);
			if(max_ind!=i)
			{
				Node *tmp = nodes[i];
				nodes[i] = nodes[max_ind];
				nodes[max_ind] = tmp;
				heapify(max_ind);
				int t = positions[i];
				positions[i]=positions[max_ind];
				positions[max_ind]=t;
			}
		}
};

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

void Prim(Node **G, int n)
{
	Heap H(G,n);
	while(!H.empty())
	{
		Node *v = H.extractMin();
		for(int i=0; i<v->nAdj; i++)
			if(v->adj[i]->v2->dist > v->adj[i]->w)
			{
				H.decreaseKey(v->adj[i]->v2->n, v->adj[i]->w);
				v->adj[i]->v2->parent=v;
			}
	}
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
		G[i]->nAdj = 0;
		G[i]->dist = 100000001;
		G[i]->parent = NULL;
	}
	G[0]->dist=0;
	readGraph(G,n,m);
	Prim(G,n);
	for(int i=0; i<n; i++)
		printf("Vertex %d: parent=%d\n",G[i]->n,(G[i]->parent)?G[i]->parent->n:-1);
	delete[] G;
	return 0;
}
