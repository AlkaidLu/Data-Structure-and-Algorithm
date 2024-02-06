//#define n 100
typedef struct  graph
{
    char vexs[MAX];
    int vexnum;
    int edgenum;
    int matrix[MAX][MAX];

}Graph, * PGragh;

void Floyd(int D[][n], int adj[][n], int path[][n])
{   int max=32767, i, j, k;
    for(i=0; i<n; i++)
        for(j=0; j<n; j++)
          {   if(adj[i][j]!=max) path[i][j]=i;
            else path[i][j]=-1;
            D[i][j]=adj[i][j];
        }
    for(k=0; k<n; k++)
        for(i=0; i<n; i++)
            for(j=0; j<n; j++)
                if(D[i][j]>(D[i][k]+D[k][j]))
                {   D[i][j]=D[i][k]+D[k][j]; path[i][j]=path[k][j]; }
}

typedef struct path
{
    int length;
    int pre;
};
