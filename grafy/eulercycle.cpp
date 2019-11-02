#include <cstdio>
#include <stack>
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

void EulerCycleDFS(int**, int, int, std::stack<int>*);

void EulerCycle(int **G, int n)
{
	std::stack<int> s;
	EulerCycleDFS(G,n,0,&s);
	while(!s.empty())
	{
		printf("%d ",s.top());
		s.pop();
	}
	printf("\n");
}

void EulerCycleDFS(int **G, int n, int v, std::stack<int> *s)
{
	for(int i=0; i<n; i++)
		if(i!=v && G[i][v])
		{
			G[i][v]=G[v][i]=0;
			EulerCycleDFS(G,n,i,s);
		}
	s->push(v);
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
	EulerCycle(G,n);
	delete[] G;
	return 0;
}
