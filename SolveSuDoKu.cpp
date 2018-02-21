
/*
SolveSuDoKu
*/


#include <stdio.h>

// ��� �߿�
#define H (3)
#define W (3)
// ���� �߳�
#define LEN (9)

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
//int solvemap[LEN][LEN];

int check(int x, int y, int num)
	// ��� [x][y]���Ƿ��������num 
	// numΪ0ʱ ��� [x][y]������������ �Ƿ������������ 
	// return�� 1������ / 0�������� 
{
	if(num==0)
	{
		if( map[x][y]!=0 )return 0; // ���� 
		else return 1; // û����
	}
	
	// ���������ͬ�� num
	if( map[x][y]!=0 )return 0;
		// ��������
	
	int tx, ty, X, Y;
	for(tx=0; tx<LEN; tx++)
		if( map[tx][y]==num )
			return 0;
			// ͬ����ͬ��
	for(ty=0; ty<LEN; ty++)
		if( map[x][ty]==num )
			return 0;
			// ͬ����ͬ��
	
	// ��С�����������λ���±� X Y
	X = x/H *H; // ������� * ���߶�
	Y = y/W *W; // ������� * �����
	for(int tx=X; tx<X+H; tx++)
		for(int ty=Y; ty<Y+W; ty++)
			if( map[tx][ty]==num )
				return 0;
				// ͬ�����ͬ��
	
	return 1;
	// û��ͬ��
}

int dfs(int x, int y)
{
	if( x>=LEN )return 1;
	if( y>=LEN )return dfs(x+1, 0);
	
	int num;	
	if( check(x, y, 0)==1 )// û����
	{
		for(num=1; num<=LEN; num++)
		{
			if( check(x, y, num)==1 )
			{
				map[x][y]=num;
				if( dfs(x, y+1)==1 )return 1;
					// ����һ�ֽⷨ ���ܶ��ֽⷨ
				map[x][y]=0;
			}
		}
	}
	else 
		return dfs(x, y+1);
		
	return 0;
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

void ScanMap(int *arr, int len)
{
	int z, max=len*len;
	for(z=0; z<max; z++)
		scanf("%d", arr+z);
}


#define TestMod 0
	// 0 ������ģʽ
	// 1 : Ԥ��ģʽ 

int main(int argc, char *argv[])
{
	if( TestMod==0 )ScanMap(&map[0][0], LEN);
	else PrintMap(&map[0][0], LEN);
	printf("Answer��\n");
	
	if( dfs(0, 0)==0 )printf("�޽�\n");
	else PrintMap(&map[0][0], LEN);
	
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

