#include <cstdio>
#include <stack>
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

void DFS(int **G, int *visited, int n, int v, std::stack<int> *s)
{
	visited[v]=1;
	for(int i=0;i<n;i++)
		if(i!=v&&G[v][i]&&!visited[i])
			DFS(G,visited,n,i,s);
	s->push(v);
}


void DFS2(int **G, int *visited, int *sss, int n, int v, int sssnum)
{
	visited[v]=1;
	sss[v]=sssnum;
	for(int i=0;i<n;i++)
		if(i!=v&&G[i][v]&&!visited[i])
			DFS2(G,visited,sss,n,i,sssnum);
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
	int *sss = (int*) malloc(n*sizeof(int));
	std::stack<int> s;
	for(int i=0; i<n; i++)
		sss[i]=visited[i]=0;
	for(int i=0;i<n;i++)
		if(!visited[i])
			DFS(G,visited,n,i,&s);
	for(int i=0; i<n; i++)
		visited[i]=0;
	int sssnum=1;
	while(!s.empty())
	{
		int i = s.top();
		s.pop();
		if(!visited[i])
		{
			DFS2(G,visited,sss,n,i,sssnum);
			sssnum++;
		}
	}
	for(int i=0; i<n; i++)
		printf("SSS dla %d: %d\n",i,sss[i]);
	delete[] G;
	delete[] visited;
	delete[] sss;
	return 0;
}
