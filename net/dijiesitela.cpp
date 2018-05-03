#include<stdlib.h>
#include<stdio.h>
#include<string.h>            
#define MNUM 30//���Ľ����    
#define max 100//���ɵ���߽�
char route[MNUM][MNUM];   //������ƾ���                                  
typedef struct mgraph{
    int A[MNUM][MNUM];    //�ڽӾ���
}mgraph;
void Floyd(mgraph G,int n){
    //��ʼ��-----------------------------------------------------------------------------------------------
	int i,j,k;
	int distance[MNUM][MNUM];//�������
	int path[MNUM][MNUM];//·����ʶ
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		{
			if(G.A[i][j]<max)
				path[i][j]=j;
			else
				path[i][j]=-1;
			distance[i][j]=G.A[i][j];
		}
	//�������·��----------------------------------------------------------------------------------------
	for(k=0;k<n;k++)
		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
				if(distance[i][j]>distance[i][k]+distance[k][j])
				{
					distance[i][j]=distance[i][k]+distance[k][j];//���·���㷨--�Ƚ�
					path[i][j]=path[i][k];
				}
    //��ӡ·�ɱ�----------------------------------------------------------------------------------------
	printf("-------------------------------------------\n");
	for(i=0;i<n;i++)
	{   printf("%s��·�ɱ�:\n",route[i+1]);
	    printf("-------------------------------------------\n");
     	printf("Ŀ������    |   ����    |  ��һ��·����\n");
		for(j=0;j<n;j++)
		{
			if(i!=j){
				k=path[i][j];
				if(k==-1)
					printf("%s����ͨ!\n",route[j+1]);
				else
				{
		printf("   %s             %d              %s\n",route[j+1],distance[i][j] ,route[k+1]);
				}					
			}        
		}
	}
	printf("-------------------------------------------\n");
	//����-------------------------------------------------------------------------------------------------
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
	
	printf("����֮����ڽ׾���\n");
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			printf("%d ",G.A[i][j]);
		}
		printf("\n");
	}
	printf("---------------------------\n");
	printf("��ȥʧЧ�ڵ��ʣ�µĽڵ����ƣ�\n");	
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
    /*����·������ͼ*/
	printf("·�ɽ�������Ϊ:");
	scanf("%d",&n);
    char jj[1];
	gets(jj);
	for(int node = 1;node<=n;node++)
	{   printf("������%d������:",node-1);
		gets(route[node]);	

	}
	printf("�������ڽӾ���\n");
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			scanf("%d",&G.A[i][j]);//�����ڽӾ���
	printf("�ڽ׾���Ϊ��\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%d ",G.A[i][j]);
		}
		printf("\n");
	}
	Floyd(G,n);
    printf("·�ɱ����:\n");
	printf("�����ӽ�㣬����1\n��ɾ���ڵ㣬����2\n");
	scanf("%d",&p);
	while(1)
	{   
		if(p==1)
		{ printf("���������Ľڵ�����:\n");
		  gets(jj);
          gets(route[++n]);
          
		  printf("�����������ڽӾ���Ԫ��\n");
     	for(i=0;i<n;i++)
			scanf("%d",&G.A[i][n-1]);//�����ڽӾ���
		for(j=0;j<n-1;j++)
			scanf("%d",&G.A[n-1][j]);
	printf("�ڽ׾���Ϊ��\n");
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
		{ printf("����ʧЧ�Ľڵ����:\n");
		  scanf("%d",&m);
		  getchar();
		  Floyd(deleted(G,n,m),--n);
		}
        printf("�����ӽ�㣬����1\n��ɾ���ڵ㣬����2\n");
        scanf("%d",&p);
	}
}
