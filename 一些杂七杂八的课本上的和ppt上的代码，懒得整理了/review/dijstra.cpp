#define MAX 1000
#define INF 100000000
#include<iostream>
typedef struct  graph
{
    char vexs[MAX];
    int vexnum;
    int edgenum;
    int matrix[MAX][MAX];

}Graph, * PGragh;
//*****算法复杂度O(n^2)*****//
//*****可重复调用来求最短路径，局限：不能处理负值边问题******//
void dijstra(Graph G, int vs, int prev[], int dist[])
{   
    int i, j, k;
    int min;
    int tmp;
    int flag[MAX];

    for(i = 0; i<G.vexnum;i++){
        flag[i]=0;//是否找到了最短路径
        prev[i]=-1;//前面的结点
        dist[i]=INF;//距离
    }
    
    //对源点初始化
    flag[vs]=1;
    dist[vs]=0;

    //遍历G.vexnum-1次，每次找出顶点到一个点的最短路径
    for(i=0;i<G.vexnum-1;i++){
        //寻找当前length值最小的点
        min=INF;
        for(j=0;j<G.vexnum;j++){
            if(flag[j]==0&&dist[j]<min){
                min=dist[j];
                k=j;//储存当前的得到了最短路径的结点
            }
            flag[k]=1;
        }
        //更新当前表中flag不为1的结点的dist值
        for(j=0;j<G.vexnum;j++){
            tmp=(G.matrix[k][j]==INF?INF:(min+G.matrix[k][j]));
            if(flag[j]==0&&(tmp<dist[j])){
                dist[j]=tmp;
                prev[j]=k;
            }
        }
    }
    printf("DIJKSTRA(%c):\n",G.vexs[vs]);
    for(int i=0;i<G.vexnum;i++){
        printf("  shortest(%c, %c)=%d\n",G.vexs[vs],G.vexs[i],dist[i]);
    }
}

