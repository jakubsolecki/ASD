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
		G[a][b]=G[b][a]=1;
	}
}

int min(int a, int b)
{
	return ((a<b)?a:b);
}

void dfs(int **G, int *d, int *low, int *parents, int *visited, int n, int v, int *T)
{
	d[v]=low[v]=(*T)++;
	visited[v]=1;
	for(int i=0; i<n; i++)
		if(parents[v]!=i&&G[i][v])
		{
			if(!visited[i])
			{
				parents[i]=v;
				dfs(G,d,low,parents,visited,n,i,T);
				low[v]=min(low[v],low[i]);
			}
			else
			low[v]=min(low[v],d[i]);
		}
}

void findBridges(int **G, int n)
{
	int *d = (int*) malloc(n*sizeof(int));
	int *low = (int*) malloc(n*sizeof(int));
	int *parents = (int*) malloc(n*sizeof(int));
	int *visited = (int*) malloc(n*sizeof(int));
	for(int i=0;i<n;i++)
	{
		d[i]=visited[i]=low[i]=0;
		parents[i]=-1;
	}
	int T=1;
	dfs(G,d,low,parents,visited,n,0,&T);
	for(int i=0; i<n; i++)
		if(d[i]==low[i]&&parents[i]>=0)
			printf("Bridge: %d %d\n",i,parents[i]);
	delete[] d;
	delete[] low;
	delete[] parents;
	delete[] visited;
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
	findBridges(G,n);
	delete[] G;
	return 0;
}
