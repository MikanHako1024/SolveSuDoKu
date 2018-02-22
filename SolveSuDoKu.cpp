
/*
SolveSuDoKu
*/


#include <stdio.h>
#include <stdlib.h>

// 大格 高宽
#define H (3)
#define W (3)
// 棋盘 边长
#define LEN (9)

/*
int map[LEN][LEN]={ 
{0, 0, 5,   0, 0, 0,   0, 0, 0}, 
{0, 0, 0,   0, 6, 5,   8, 0, 0}, 
{0, 7, 6,   0, 3, 0,   2, 0, 1}, 
					  
{0, 3, 0,   2, 0, 4,   0, 0, 0}, 
{0, 9, 2,   0, 8, 0,   3, 7, 0}, 
{0, 0, 0,   9, 0, 0,   0, 2, 0}, 
			  
{3, 0, 7,   0, 5, 0,   4, 9, 0}, 
{0, 0, 1,   6, 4, 0,   0, 0, 0}, 
{0, 0, 0,   0, 0, 0,   1, 0, 0} };
*/
int map[LEN][LEN];


int check(int x, int y, int num)
	// 检查 [x][y]格是否可以填入num 
	// num为0时 检查 [x][y]格已有数（即 是否可以填入数） 
	// return： 1：可以 / 0：不可以 
{
	if(num==0)
	{
		if( map[x][y]!=0 )return 0; // 有数 
		else return 1; // 没有数
	}
	
	// 检查有无相同数 num
	if( map[x][y]!=0 )return 0;
		// 已有数字
	
	int tx, ty, X, Y;
	for(tx=0; tx<LEN; tx++)
		if( map[tx][y]==num )
			return 0;
			// 同列有同数
	for(ty=0; ty<LEN; ty++)
		if( map[x][ty]==num )
			return 0;
			// 同行有同数
	
	// 该小格所处大格首位置下标 X Y
	X = x/H *H; // 大格行数 * 大格高度
	Y = y/W *W; // 大格列数 * 大格宽度
	for(int tx=X; tx<X+H; tx++)
		for(int ty=Y; ty<Y+W; ty++)
			if( map[tx][ty]==num )
				return 0;
				// 同大格有同数
	
	return 1;
	// 没有同数
}

int dfs(int x, int y)
{
	if( x>=LEN )return 1;
	if( y>=LEN )return dfs(x+1, 0);
	
	int num;	
	if( check(x, y, 0)==1 )// 没有数
	{
		for(num=1; num<=LEN; num++)
		{
			if( check(x, y, num)==1 )
			{
				map[x][y]=num;
				if( dfs(x, y+1)==1 )return 1;
					// 仅找一种解法 不管多种解法
				map[x][y]=0;
			}
		}
	}
	else 
		return dfs(x, y+1);
		
	return 0;
}


void ScanMap(int *arr, int len)
{
	int z, max=len*len;
	for(z=0; z<max; z++)
		scanf("%d", arr+z);
}

void PrintMap(int *arr, int len)
{
	int z, max=len*len;
	for(z=0; z<max; z++)
	{
		printf("%d ", *(arr+z));
		if( (z+1)%len==0 )printf("\n");
	}
}


void ScanMapF(char *FName, int *arr, int len)
{
	FILE *fp=NULL;
	if( (fp=fopen(FName, "r"))==NULL )
	{
		printf("打开 %s 失败！\n");
		system("pause");
		exit(0); 
	}
	
	int z, max=len*len;
	for(z=0; z<max; z++)
		fscanf(fp, "%d", arr+z);
	
	fclose(fp);
}

void PrintMapF(char *FName, int *arr, int len)
{
	FILE *fp=NULL;
	if( (fp=fopen(FName, "a"))==NULL )
	{
		printf("打开 %s 失败！\n");
		system("pause");
		exit(0); 
	}
	
	int z, max=len*len;
	for(z=0; z<max; z++)
	{
		fprintf(fp, "%d ", *(arr+z));
		if( (z+1)%len==0 )fprintf(fp, "\n");
	}
	
	fclose(fp);
}

void PrintStrF(char *FName, const char *str)
{
	FILE *fp=NULL;
	if( (fp=fopen(FName, "a"))==NULL )
	{
		printf("打开 %s 失败！\n");
		//system("pause");
		exit(0); 
	}
	
	fprintf(fp, "%s", str);
	
	fclose(fp);
}

#define TestMod 0
	// 0 ：输入/拖入模式
	// 1 : 预设模式 

int main(int argc, char *argv[])
{
	if( TestMod==1 )
	{
		printf("Question：\n"); 
		PrintMap(&map[0][0], LEN);
		printf("\nAnswer：\n");
	
		if( dfs(0, 0)==0 )printf("无解\n");
		else PrintMap(&map[0][0], LEN);
	}
	else
	{
		if( argc>1 )
		{
			ScanMapF(argv[1], &map[0][0], LEN);
			printf("Question：\n"); 
			PrintMap(&map[0][0], LEN);
			
			PrintStrF(argv[1], "\nAnswer：\n");
			printf("\nAnswer：\n");
			
			if( dfs(0, 0)==0 )
			{
				PrintStrF(argv[1], "无解\n");
				printf("无解\n");
			}
			else
			{
				PrintMapF(argv[1], &map[0][0], LEN);
				PrintMap(&map[0][0], LEN);
			}
		}
		else
		{
			printf("Question：\n"); 
			ScanMap(&map[0][0], LEN);
			printf("Answer：\n");
			
			if( dfs(0, 0)==0 )printf("无解\n");
			else PrintMap(&map[0][0], LEN);
		}
	}
	
	system("pause");
	return 0;
}

/*
0 0 8 0 0 4 0 6 0
0 2 0 0 0 0 0 0 8
0 0 0 1 0 0 7 0 0 
0 0 2 0 0 6 0 0 5
7 0 0 0 5 0 0 0 3
1 0 0 4 0 0 8 0 0
0 0 3 0 0 9 0 0 0 
6 0 0 0 0 0 0 2 0 
0 5 0 8 0 0 4 0 0 

*/

