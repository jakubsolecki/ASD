#include <cstdio>
#include <stack>
#include <queue>
#include <cstdlib>

void readGraph(int **G, int n, int m)
{
	int a,b;
	for(int i=0;i<m;i++)
	{
		scanf("%d %d",&a,&b);
		G[a][b]=1;
	}
}

void DFS(int **G, int *visited, int n, int v, std::queue<int> *q)
{
	visited[v]=1;
	for(int i=0;i<n;i++)
		if(i!=v&&G[v][i]&&!visited[i])
			DFS(G,visited,n,i,q);
	q->push(v);
}

int main()
{
	int n,m;
	scanf("%d %d",&n,&m);
	int **G = (int**) malloc(n*sizeof(int*));
	for(int i=0; i<n;i++)
	{
		G[i] = (int*) malloc(n*sizeof(int));
		for(int j=0;j<n;j++)
			G[i][j]=0;
	}
	readGraph(G,n,m);
	int *visited = (int*) malloc(n*sizeof(int));
	std::queue<int> q;
	for(int i=0; i<n; i++)
		visited[i]=0;
	for(int i=0;i<n;i++)
		if(!visited[i])
			DFS(G,visited,n,i,&q);
	while(!q.empty())
	{
		printf("%d ",q.front());
		q.pop();
	}
	printf("\n");
	delete[] G;
	delete[] visited;
	return 0;
}
