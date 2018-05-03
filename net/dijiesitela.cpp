#include<stdlib.h>
#include<stdio.h>
#include<string.h>            
#define MNUM 30//最大的结点数    
#define max 100//不可到达边界
char route[MNUM][MNUM];   //结点名称矩阵                                  
typedef struct mgraph{
    int A[MNUM][MNUM];    //邻接矩阵
}mgraph;
void Floyd(mgraph G,int n){
    //初始化-----------------------------------------------------------------------------------------------
	int i,j,k;
	int distance[MNUM][MNUM];//距离矩阵
	int path[MNUM][MNUM];//路径标识
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		{
			if(G.A[i][j]<max)
				path[i][j]=j;
			else
				path[i][j]=-1;
			distance[i][j]=G.A[i][j];
		}
	//计算最短路径----------------------------------------------------------------------------------------
	for(k=0;k<n;k++)
		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
				if(distance[i][j]>distance[i][k]+distance[k][j])
				{
					distance[i][j]=distance[i][k]+distance[k][j];//最短路径算法--比较
					path[i][j]=path[i][k];
				}
    //打印路由表----------------------------------------------------------------------------------------
	printf("-------------------------------------------\n");
	for(i=0;i<n;i++)
	{   printf("%s的路由表:\n",route[i+1]);
	    printf("-------------------------------------------\n");
     	printf("目的网络    |   距离    |  下一跳路由器\n");
		for(j=0;j<n;j++)
		{
			if(i!=j){
				k=path[i][j];
				if(k==-1)
					printf("%s不连通!\n",route[j+1]);
				else
				{
		printf("   %s             %d              %s\n",route[j+1],distance[i][j] ,route[k+1]);
				}					
			}        
		}
	}
	printf("-------------------------------------------\n");
	//结束-------------------------------------------------------------------------------------------------
}
mgraph deleted(mgraph G,int n,int dp){	
	for(int i=0;i<n;i++)
	{
		for(int j=dp;j<n;j++)
		{
			G.A[i][j] = G.A[i][j+1];
		}
	}
	for(int j=0;j<n;j++)
	{
		for(int i=dp;i<n;i++)
		{
			G.A[i][j] = G.A[i+1][j];
		}
	}
	for(int k=dp+1;k<n;k++)
	{
		strcpy(route[k],route[k+1]);
	}
	n--;
	
	printf("更新之后的邻阶矩阵：\n");
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			printf("%d ",G.A[i][j]);
		}
		printf("\n");
	}
	printf("---------------------------\n");
	printf("除去失效节点后剩下的节点名称：\n");	
	for(int k=0;k<=n;k++)
	{
		printf("%s\n",route[k]);
	}
	printf("---------------------------\n");
	return G;
}
void main()
{	int n,i,j,m;
    int p=3;
	mgraph G;
    /*输入路由拓扑图*/
	printf("路由结点的数量为:");
	scanf("%d",&n);
    char jj[1];
	gets(jj);
	for(int node = 1;node<=n;node++)
	{   printf("输入结点%d的名称:",node-1);
		gets(route[node]);	

	}
	printf("请输入邻接矩阵\n");
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			scanf("%d",&G.A[i][j]);//读入邻接矩阵
	printf("邻阶矩阵为：\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%d ",G.A[i][j]);
		}
		printf("\n");
	}
	Floyd(G,n);
    printf("路由表更新:\n");
	printf("若增加结点，输入1\n若删除节点，输入2\n");
	scanf("%d",&p);
	while(1)
	{   
		if(p==1)
		{ printf("输入新增的节点名称:\n");
		  gets(jj);
          gets(route[++n]);
          
		  printf("请输入新增邻接矩阵元素\n");
     	for(i=0;i<n;i++)
			scanf("%d",&G.A[i][n-1]);//读入邻接矩阵
		for(j=0;j<n-1;j++)
			scanf("%d",&G.A[n-1][j]);
	printf("邻阶矩阵为：\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%d ",G.A[i][j]);
		}
		printf("\n");
	}

          Floyd(G,n);
		}


		if(p==2)
		{ printf("输入失效的节点序号:\n");
		  scanf("%d",&m);
		  getchar();
		  Floyd(deleted(G,n,m),--n);
		}
        printf("若增加结点，输入1\n若删除节点，输入2\n");
        scanf("%d",&p);
	}
}
