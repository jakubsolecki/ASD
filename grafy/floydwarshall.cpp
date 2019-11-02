#include <cstdio>
#include <stack>
#include <cstdlib>

void readGraph(int **G, int n, int m)
{
	int a,b,w;
	for(int i=0;i<m;i++)
	{
		scanf("%d %d %d",&a,&b,&w);
		G[a][b]=G[b][a]=w;
	}
}

struct output
{
	int **R, **P;
};

output FloydWarshall(int **G, int n)
{
	output res;
	res.R = (int**) malloc(n*sizeof(int*));
	res.P = (int**) malloc(n*sizeof(int*));
	for(int i=0;i<n;i++)
	{
		res.R[i]=(int*) malloc(n*sizeof(int));
		res.P[i]=(int*) malloc(n*sizeof(int));
		for(int j=0; j<n; j++)
		{
			res.P[i][j]=-1;
			res.R[i][j]=G[i][j];
		}
	}
	for(int k=0; k<n; k++)
		for(int i=0; i<n; i++)
			for(int j=0; j<n; j++)
				if(res.R[i][k]+res.R[k][j]<res.R[i][j])
				{
					res.R[i][j]=res.R[i][k]+res.R[k][j];
					res.P[i][j]=k;
				}
	return res;
}

void printPath(output *fw, int s, int t)
{
	int v = fw->P[s][t];
	if(v==-1) printf(" ");
	else
	{
		printPath(fw,s,v);
		printf("%d",v);
		printPath(fw,v,t);
	}
}

int main()
{
	int n,m,s,t;
	scanf("%d %d %d %d",&n,&m,&s,&t);
	int **G = (int**) malloc(n*sizeof(int*));
	for(int i=0; i<n;i++)
	{
		G[i] = (int*) malloc(n*sizeof(int));
		for(int j=0;j<n;j++)
			G[i][j]=10000001;
	}
	readGraph(G,n,m);
	output fw = FloydWarshall(G,n);
	if(fw.R[s][t]==10000001)
		printf("No path from %d to %d\n",s,t);
	else
	{
		printf("%d",s);
		printPath(&fw,s,t);
		printf("%d\n",t);
	}
	delete[] fw.R;
	delete[] fw.P;
	delete[] G;
	return 0;
}
