// Samsung Go Tournament Form C (g++-4.8.3)

/*
[AI �ڵ� �ۼ� ���]

1. char info[]�� �迭 �ȿ�               "TeamName:�ڽ��� ����,Department:�ڽ��� �Ҽ�"               ������ �ۼ��մϴ�.
( ���� ) Teamname:�� Department:�� �� ���� �մϴ�.
"�ڽ��� ����", "�ڽ��� �Ҽ�"�� �����ؾ� �մϴ�.

2. �Ʒ��� myturn() �Լ� �ȿ� �ڽŸ��� AI �ڵ带 �ۼ��մϴ�.

3. AI ������ �׽�Ʈ �Ͻ� ���� "���� �˰����ȸ ��"�� ����մϴ�.

4. ���� �˰��� ��ȸ ���� �����ϱ⿡�� �ٵϵ��� ���� ��, �ڽ��� "����" �� �� �˰����� �߰��Ͽ� �׽�Ʈ �մϴ�.



[���� �� �Լ�]
myturn(int cnt) : �ڽ��� AI �ڵ带 �ۼ��ϴ� ���� �Լ� �Դϴ�.
int cnt (myturn()�Լ��� �Ķ����) : ���� �� �� �־��ϴ��� ���ϴ� ����, cnt�� 1�̸� ���� ���� ��  �� ����  �δ� ��Ȳ(�� ��), cnt�� 2�̸� �� ���� ���� �δ� ��Ȳ(�� ��)
int  x[0], y[0] : �ڽ��� �� ù �� ° ���� x��ǥ , y��ǥ�� ����Ǿ�� �մϴ�.
int  x[1], y[1] : �ڽ��� �� �� �� ° ���� x��ǥ , y��ǥ�� ����Ǿ�� �մϴ�.
void domymove(int x[], int y[], cnt) : �� ������ ��ǥ�� �����ؼ� ���


//int board[BOARD_SIZE][BOARD_SIZE]; �ٵ��� �����Ȳ ��� �־� �ٷλ�� ������. ��, ���������ͷ� ���� �������
// ������ ���� ��ġ�� �ٵϵ��� ������ �ǰ��� ó��.

boolean ifFree(int x, int y) : ���� [x,y]��ǥ�� �ٵϵ��� �ִ��� Ȯ���ϴ� �Լ� (������ true, ������ false)
int showBoard(int x, int y) : [x, y] ��ǥ�� ���� ���� �����ϴ��� �����ִ� �Լ� (1 = �ڽ��� ��, 2 = ����� ��, 3 = ��ŷ)


<-------AI�� �ۼ��Ͻ� ��, ���� �̸��� �Լ� �� ���� ����� �������� �ʽ��ϴ�----->
*/

#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include "Connect6Algo.h"



// "�����ڵ�[C]"  -> �ڽ��� ���� (����)
// "AI�μ�[C]"  -> �ڽ��� �Ҽ� (����)
// ����� ���������� �ݵ�� �������� ����!
char info[] = { "TeamName:���񽺴�,Department:�������б� ������" };
typedef struct pair {
	int x0;
	int x1;
	int y0;
	int y1;
}xyPair;
typedef struct elem {
	int x;
	int y;
}xy;

struct vec {
	int x;
	int y;
	int freq;
	int way;
};

xyPair twoBuilder(xy center);
xyPair dfs(xy center, int until, bool recur);
xyPair vecqueSorter(vec q[], int totalmine, int maxfreq);

xy blackFirst()//�浹 ù �� �Լ�
{
	int points[8][2] = { { 3,3 },{ 3,9 },{ 3,15 },{ 9,3 },{ 9,15 },{ 15,3 },{ 15,9 },{ 15,15 } };
	xy tmp;
	int index = 0;
	if (isFree(9, 9))//��� ������ ����
	{
		tmp.x = 9;
		tmp.y = 9;
		return tmp;
	}
	else//����� �� ��������
	{
		do {
			index = rand() % 8;
			tmp.x = points[index][0];
			tmp.y = points[index][1];
		} while (!isFree(tmp.x, tmp.y));
		return tmp;
	}
	
}
bool isBlackT2(int board[][20])//�浹�� �ι�° ������ ���� �Լ�
{
	int sum = 0;
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (board[i][j] == 1)
			{
				sum += 1;
			}
		}
	}
	if (sum == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

xyPair dfs(xy center, int until, bool recur)//center ���� 8���� Ž�� until�� ���� �ٿ��� ���� �� �ִ��� ã�ƺ��� �����ϸ� �� ���� �� ��ǥ ���� �Լ�
{
	int x = center.x;
	int y = center.y;
	xyPair rst;
	bool flag = true;
	//�»�밢
	for (int i = 1; i <= until; i++)
	{
		if (!isFree(x - i, y - i))
		{
			flag = false;
			break;
		}
	}
	if (flag)
	{
		rst.x0 = x - 1;
		rst.y0 = y - 1;
		rst.x1 = x - 2;
		rst.y1 = y - 2;
		return rst;
	}
	flag = true;
	//���밢
	for (int i = 1; i <= until; i++)
	{
		if (!isFree(x + i, y - i))
		{
			flag = false;
			break;
		}
	}
	if (flag)
	{
		rst.x0 = x + 1;
		rst.y0 = y - 1;
		rst.x1 = x + 2;
		rst.y1 = y - 2;
		return rst;
	}
	flag = true;
	//���ϴ밢
	for (int i = 1; i <= until; i++)
	{
		if (!isFree(x - i, y + i))
		{
			flag = false;
			break;
		}
	}
	if (flag)
	{
		rst.x0 = x - 1;
		rst.y0 = y + 1;
		rst.x1 = x - 2;
		rst.y1 = y + 2;
		return rst;
	}
	flag = true;
	//���ϴ밢
	for (int i = 1; i <= until; i++)
	{
		if (!isFree(x + i, y + i))
		{
			flag = false;
			break;
		}
	}
	if (flag)
	{
		rst.x0 = x + 1;
		rst.y0 = y + 1;
		rst.x1 = x + 2;
		rst.y1 = y + 2;
		return rst;
	}
	flag = true;
	//�����
	for (int i = 1; i <= until; i++)
	{
		if (!isFree(x, y - i))
		{
			flag = false;
			break;
		}
	}
	if (flag)
	{
		rst.x0 = x;
		rst.y0 = y - 1;
		rst.x1 = x;
		rst.y1 = y - 2;
		return rst;
	}
	flag = true;
	//�ϼ���
	for (int i = 1; i <= until; i++)
	{
		if (!isFree(x, y + i))
		{
			flag = false;
			break;
		}
	}
	if (flag)
	{
		rst.x0 = x;
		rst.y0 = y + 1;
		rst.x1 = x;
		rst.y1 = y + 2;
		return rst;
	}
	flag = true;
	//�¼���
	for (int i = 1; i <= until; i++)
	{
		if (!isFree(x - i, y))
		{
			flag = false;
			break;
		}
	}
	if (flag)
	{
		rst.x0 = x - 1;
		rst.y0 = y;
		rst.x1 = x - 2;
		rst.y1 = y;
		return rst;
	}
	flag = true;
	//�����
	for (int i = 1; i <= until; i++)
	{
		if (!isFree(x + i, y))
		{
			flag = false;
			break;
		}
	}
	if (flag)
	{
		rst.x0 = x + 1;
		rst.y0 = y;
		rst.x1 = x + 2;
		rst.y1 = y;
		return rst;
	}
	flag = true;
	//���� ������ΰ�� ���. �ڱ� �� �ֺ� 8���� �� �� �ΰ��� ���ɷ� ���������� ������ �������� ����� �Ǿ��ִ� ����϶� ����� ��� ���� ���� twoBuilder�� ������. twoBuilder ���ο��� �ٽ� dfs ���ȣ���� ���ɼ��� ����ϹǷ� �������� �ʾҴ�.
	if (recur)
	{
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (showBoard(i, j) == 2)
				{
					xy tmp;
					tmp.x = i;
					tmp.y = j;
					return twoBuilder(tmp);
				}
			}
		}
	}
	else
	{
		rst.x0 = -1;
		rst.y0 = -1;
		rst.x1 = -1;
		rst.y1 = -1;
		return rst;
	}



}
xyPair twoBuilder(xy center)//��� �� �ϳ� �ֺ� ������ �ΰ��� �״� �Լ� 1. ������ �Ǻ��� �õ��� 2.������ ���� 8���� dfs ����
{
	int x = center.x;
	int y = center.y;
	xyPair rst;
	//���� ���� ������ �밢 �Ǻ�
	if ((isFree(x + 1, y - 2) && isFree(x + 2, y - 3)) && (isFree(x - 2, y + 1) && isFree(x - 3, y + 2)))//9-12�� �밢
	{
		if (isFree(x, y - 1) && isFree(x - 1, y))
		{
			rst.x0 = x;
			rst.y0 = y - 1;
			rst.x1 = x - 1;
			rst.y1 = y;
			return rst;
		}
	}
	if ((isFree(x - 1, y - 2) && isFree(x - 2, y - 3)) && (isFree(x + 2, y + 1) && isFree(x + 3, y + 2)))//3-12�� �밢
	{
		if (isFree(x, y - 1) && isFree(x + 1, y))
		{
			rst.x0 = x;
			rst.y0 = y - 1;
			rst.x1 = x + 1;
			rst.y1 = y;
			return rst;
		}

	}
	if ((isFree(x - 2, y - 1) && isFree(x - 3, y - 2)) && (isFree(x + 1, y + 2) && isFree(x + 2, y + 3)))//9-6�� �밢
	{
		if (isFree(x, y + 1) && isFree(x - 1, y))
		{
			rst.x0 = x;
			rst.y0 = y + 1;
			rst.x1 = x - 1;
			rst.y1 = y;
			return rst;
		}
	}

	if ((isFree(x + 2, y - 1) && isFree(x + 3, y - 2)) && (isFree(x - 1, y + 2) && isFree(x - 2, y + 3)))//3-6�� �밢
	{
		if (isFree(x + 1, y) && isFree(x, y + 1))
		{
			rst.x0 = x + 1;
			rst.y0 = y;
			rst.x1 = x;
			rst.y1 = y + 1;
			return rst;
		}
	}
	//8���� ���� �켱 Ž�� �˰���
	
	{
		return dfs(center, 5, false);
	}
}
xy singleChecker(int pia)//�Ǿƽĺ� 1,2�� �����̳� ��� �� �ϳ��� �����´�.
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (showBoard(i, j) == pia)
			{
				xy tmp;
				tmp.x = i;
				tmp.y = j;
				return tmp;
			}

		}
	}
}

xyPair vbMaker(int board[][20])//����ġ ���� ����
{

	int vb[20][20][2] = { 0, };//3���� �ε��� 0 ���� �ִ� ����ġ, 1���� �׶��� ���ߵ� ����
							   //�»�밢0
							   //���밢1
							   //�����2
							   //�¼���3
							   //�����4
							   //�ϼ���5
							   //���ϴ밢6
							   //���ϴ밢7

							   //���� �̾�� �� ���� ������ �� ����
	int maxfreq = 0;//������� ���� �� ����
	int maxway = -1;//���� ����
	int maxi = -1;//�� x��ġ
	int maxj = -1;//�� y��ġ
	int totalmine = 0;
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (board[i][j] == 1)
			{
				totalmine += 1;
				int direction[8] = { 0, };
				//�»�밢
				for (int k = 1; k <= 5; k++)
				{
					if (board[i - k][j - k] == 1)
					{
						direction[0] += 1;
					}
					else
					{
						break;
					}
				}
				//���밢
				for (int k = 1; k <= 5; k++)
				{
					if (board[i + k][j - k] == 1)
					{
						direction[1] += 1;
					}
					else
					{
						break;
					}
				}
				//���ϴ밢
				for (int k = 1; k <= 5; k++)
				{
					if (board[i - k][j + k] == 1)
					{
						direction[6] += 1;
					}
					else
					{
						break;
					}
				}
				//���ϴ밢
				for (int k = 1; k <= 5; k++)
				{
					if (board[i + k][j + k] == 1)
					{
						direction[7] += 1;
					}
					else
					{
						break;
					}
				}
				//�����
				for (int k = 1; k <= 5; k++)
				{
					if (board[i][j - k] == 1)
					{
						direction[2] += 1;
					}
					else
					{
						break;
					}
				}
				//�ϼ���
				for (int k = 1; k <= 5; k++)
				{
					if (board[i][j + k] == 1)
					{
						direction[5] += 1;
					}
					else
					{
						break;
					}
				}
				//�¼���
				for (int k = 1; k <= 5; k++)
				{
					if (board[i - k][j] == 1)
					{
						direction[3] += 1;
					}
					else
					{
						break;
					}
				}
				//�����
				for (int k = 1; k <= 5; k++)
				{
					if (board[i + k][j] == 1)
					{
						direction[4] += 1;
					}
					else
					{
						break;
					}
				}
				int dirmaxvalue = 0;//���� �ִ�ġ direction ã��
				int dirmax = -1;//�׶��� ����

				for (int i = 0; i < 8; i++)
				{
					if (dirmaxvalue < direction[i])
					{
						dirmaxvalue = direction[i];
						dirmax = 7 - i;
					}
				}

				if (vb[i][j][0] < dirmaxvalue)//���� ����ġ ���忡 ����� ���� ū ������
				{
					vb[i][j][0] = dirmaxvalue;//���� ū ������ ����
					vb[i][j][1] = dirmax;//�׶� ����
				}
			}
		}
	}
	int tmindex = 0;
	vec queue[361];
	for (int i = 0; i < 20; i++)//����ġ ���� �ִ밪 ã��
	{
		for (int j = 0; j < 20; j++)
		{
			if (vb[i][j][0] > 0)
			{
				queue[tmindex].freq = vb[i][j][0];
				queue[tmindex].way = vb[i][j][1];
				queue[tmindex].x = i;
				queue[tmindex].y = j;
				tmindex += 1;

				if (vb[i][j][0] > maxfreq)
				{
					maxfreq = vb[i][j][0];
					maxway = vb[i][j][1];
					maxi = i;
					maxj = j;
				}
			}
		}
	}
	//�ִ밪 ���ͷ� �ΰ� ������ �ȵǸ� ���� �����ؼ� �ϳ��� �غ��� �ȵǸ� dfs ����.
	int x = maxi;
	int y = maxj;
	xyPair rst;
	//�ִ밪 ���� ���� �� �� �̾� ��ȯ
	bool flag = true;
	switch (maxway)
	{
	case 0:	//�»�밢0
		flag = true;
		for (int i = 1; i <= 6 - maxfreq; i++)
		{
			if (!isFree(x - i, y - i))
			{
				flag = false;
				break;
			}
		}
		if (flag)
		{
			rst.x0 = x - 1;
			rst.y0 = y - 1;
			rst.x1 = x - 2;
			rst.y1 = y - 2;
			return rst;
		}
		flag = true;
		break;
	case 1: //���밢1
		flag = true;
		for (int i = 1; i <= 6 - maxfreq; i++)
		{
			if (!isFree(x + i, y - i))
			{
				flag = false;
				break;
			}
		}
		if (flag)
		{
			rst.x0 = x + 1;
			rst.y0 = y - 1;
			rst.x1 = x + 2;
			rst.y1 = y - 2;
			return rst;
		}
		flag = true;
		break;
	case 2://�����2
		flag = true;
		for (int i = 1; i <= 6 - maxfreq; i++)
		{
			if (!isFree(x, y - i))
			{
				flag = false;
				break;
			}
		}
		if (flag)
		{
			rst.x0 = x;
			rst.y0 = y - 1;
			rst.x1 = x;
			rst.y1 = y - 2;
			return rst;
		}
		flag = true;
		break;
	case 3://�¼���3
		flag = true;
		for (int i = 1; i <= 6 - maxfreq; i++)
		{
			if (!isFree(x - i, y))
			{
				flag = false;
				break;
			}
		}
		if (flag)
		{
			rst.x0 = x - 1;
			rst.y0 = y;
			rst.x1 = x - 2;
			rst.y1 = y;
			return rst;
		}
		flag = true;
		break;
	case 4://�����4
		flag = true;
		for (int i = 1; i <= 6 - maxfreq; i++)
		{
			if (!isFree(x + i, y))
			{
				flag = false;
				break;
			}
		}
		if (flag)
		{
			rst.x0 = x + 1;
			rst.y0 = y;
			rst.x1 = x + 2;
			rst.y1 = y;
			return rst;
		}
		flag = true;
		break;
	case 5://�ϼ���5
		flag = true;
		for (int i = 1; i <= 6 - maxfreq; i++)
		{
			if (!isFree(x, y + i))
			{
				flag = false;
				break;
			}
		}
		if (flag)
		{
			rst.x0 = x;
			rst.y0 = y + 1;
			rst.x1 = x;
			rst.y1 = y + 2;
			return rst;
		}
		flag = true;
		break;
	case 6://���ϴ밢6
		flag = true;
		for (int i = 1; i <= 6 - maxfreq; i++)
		{
			if (!isFree(x - i, y + i))
			{
				flag = false;
				break;
			}
		}
		if (flag)
		{
			rst.x0 = x - 1;
			rst.y0 = y + 1;
			rst.x1 = x - 2;
			rst.y1 = y + 2;
			return rst;
		}
		flag = true;
		break;
	case 7://���ϴ밢7
		flag = true;
		for (int i = 1; i <= 6 - maxfreq; i++)
		{
			if (!isFree(x + i, y + i))
			{
				flag = false;
				break;
			}
		}
		if (flag)
		{
			rst.x0 = x + 1;
			rst.y0 = y + 1;
			rst.x1 = x + 2;
			rst.y1 = y + 2;
			return rst;
		}
		flag = true;
		break;
	}
	//���� ���� ���� �ִ� �� ������ �ȵǴ°Ŵ�. �������� �����ؼ� ���� ����ġ ū �� ���� ���� ����
	if (flag)
	{
		rst = vecqueSorter(queue, totalmine, maxfreq);
		return rst;
	}
}
xyPair vecqueSorter(vec queue[], int totalmine, int maxfreq)
{
	for (int mf = maxfreq; mf > 0; mf--)//���� ����ġ ū �� ���� ���� ����
	{
		for (int i = 0; i < totalmine; i++)
		{
			if (queue[i].freq == mf)
			{
				int x = queue[i].x;
				int y = queue[i].y;
				xyPair rst;
				bool flag = true;
				switch (queue[i].way)
				{
				case 0:	//�»�밢0
					flag = true;
					for (int i = 1; i <= 6 - mf; i++)
					{
						if (!isFree(x - i, y - i))
						{
							flag = false;
							break;
						}
					}
					if (flag)
					{
						rst.x0 = x - 1;
						rst.y0 = y - 1;
						rst.x1 = x - 2;
						rst.y1 = y - 2;
						return rst;
					}
					break;
				case 1: //���밢1
					flag = true;
					for (int i = 1; i <= 6 - mf; i++)
					{
						if (!isFree(x + i, y - i))
						{
							flag = false;
							break;
						}
					}
					if (flag)
					{
						rst.x0 = x + 1;
						rst.y0 = y - 1;
						rst.x1 = x + 2;
						rst.y1 = y - 2;
						return rst;
					}
					break;
				case 2://�����2
					flag = true;
					for (int i = 1; i <= 6 - mf; i++)
					{
						if (!isFree(x, y - i))
						{
							flag = false;
							break;
						}
					}
					if (flag)
					{
						rst.x0 = x;
						rst.y0 = y - 1;
						rst.x1 = x;
						rst.y1 = y - 2;
						return rst;
					}
					break;
				case 3://�¼���3
					flag = true;
					for (int i = 1; i <= 6 - mf; i++)
					{
						if (!isFree(x - i, y))
						{
							flag = false;
							break;
						}
					}
					if (flag)
					{
						rst.x0 = x - 1;
						rst.y0 = y;
						rst.x1 = x - 2;
						rst.y1 = y;
						return rst;
					}
					break;
				case 4://�����4
					flag = true;
					for (int i = 1; i <= 6 - mf; i++)
					{
						if (!isFree(x + i, y))
						{
							flag = false;
							break;
						}
					}
					if (flag)
					{
						rst.x0 = x + 1;
						rst.y0 = y;
						rst.x1 = x + 2;
						rst.y1 = y;
						return rst;
					}
					break;
				case 5://�ϼ���5
					flag = true;
					for (int i = 1; i <= 6 - mf; i++)
					{
						if (!isFree(x, y + i))
						{
							flag = false;
							break;
						}
					}
					if (flag)
					{
						rst.x0 = x;
						rst.y0 = y + 1;
						rst.x1 = x;
						rst.y1 = y + 2;
						return rst;
					}
					break;
				case 6://���ϴ밢6
					flag = true;
					for (int i = 1; i <= 6 - mf; i++)
					{
						if (!isFree(x - i, y + i))
						{
							flag = false;
							break;
						}
					}
					if (flag)
					{
						rst.x0 = x - 1;
						rst.y0 = y + 1;
						rst.x1 = x - 2;
						rst.y1 = y + 2;
						return rst;
					}
					break;
				case 7://���ϴ밢7
					flag = true;
					for (int i = 1; i <= 6 - mf; i++)
					{
						if (!isFree(x + i, y + i))
						{
							flag = false;
							break;
						}
					}
					if (flag)
					{
						rst.x0 = x + 1;
						rst.y0 = y + 1;
						rst.x1 = x + 2;
						rst.y1 = y + 2;
						return rst;
					}
					break;
				}
			}
		}
	}
	//��� ������ ���� ���� ���� ���� ��� ������ dfs ����
	for (int mf = maxfreq; mf > 0; mf--)
	{
		for (int i = 0; i < totalmine; i++)
		{
			xy center;
			center.x = queue[i].x;
			center.y = queue[i].y;
			return dfs(center, 6 - mf, false);
		}
	}
}
xyPair lastPunch(xyPair dest)//������ ����. �̰žȵǸ� ����
{
	for (int i = 5; i > 1; i--)
	{
		for (int j = 0; j < 20; j++)
		{
			for (int k = 0; k < 20; k++)
			{
				if (showBoard(j, k) == 1)
				{
					xy tmp;
					tmp.x = j;
					tmp.y = k;
					dest = dfs(tmp, i, false);
					if (dest.x0 != -1)
					{
						return dest;
					}
				}
			}
		}
	}
	return dest;
}

void myturn(int board[][20], int gcnt, int cnt) {
	int x[2], y[2];
	srand((unsigned)time(NULL));
	//�Ǵ� ���� A,D_4,5_H,V,LDG,RDG
	int A_4_H = 0;
	int A_4_V = 0;
	int A_4_LDG = 0;
	int A_4_RDG = 0;
	int A_5_H = 0;
	int A_5_V = 0;
	int A_5_LDG = 0;
	int A_5_RDG = 0;
	
	int D_4_H = 0;
	int D_4_V = 0;
	int D_4_LDG = 0;
	int D_4_RDG = 0;
	int D_5_H = 0;
	int D_5_V = 0;
	int D_5_LDG = 0;
	int D_5_RDG = 0;
	
	int temp[4]; // x[0], y[0], x[1], y[1]
	/*for�� �˰��� �ּ� ���� : who - num - direction - A/D*/

	for (int i = 0; i < 16; i++) { // ��� - 4�� - ����
		for (int j = 0; j < 19; j++) {
			if (showBoard(i, j) == 2 && showBoard(i + 1, j) == 2 && showBoard(i + 2, j) == 2 && showBoard(i + 3, j) == 2) {
				if (isFree(i - 1, j) && isFree(i + 4, j)) {
					temp[0] = i - 1;
					temp[1] = j;
					temp[2] = i + 4;
					temp[3] = j;

					D_4_H = 1;
					break;
				}
				else if (isFree(i - 1, j) && !isFree(i + 4, j)) { // �����ʸ� �����ִ� ���
					temp[0] = i - 1;
					temp[1] = j;
					
				}
				else if (!isFree(i - 1, j) && isFree(i + 4, j)) { // ���ʸ� �����ִ� ���
					temp[0] = i + 4;
					temp[1] = j;
					xyPair dest = vbMaker(board);
					if (dest.x0 != -1)//dfs ȸ�� ���� fail safe -1 �۵�
					{
						x[0] = dest.x0;
						x[1] = dest.x1;
						y[0] = dest.y0;
						y[1] = dest.y1;
					}
					else//fail safe catch�϶� 1.���� �ֺ� ���� �������� ���� 5���� 2���� �������� ����� ����-����:rst.x0==-1���� �Ź� Ȯ��
					{
						xyPair fin = lastPunch(dest);
						if (fin.x0 != -1)
						{
							x[0] = fin.x0;
							x[1] = fin.x1;
							y[0] = fin.y0;
							y[1] = fin.y1;
						}
						else
						{

							for (int i = 0; i < cnt; i++) {
								do {
									x[i] = rand() % width;
									y[i] = rand() % height;
									if (terminateAI) return;
								} while (!isFree(x[i], y[i]));

								if (x[1] == x[0] && y[1] == y[0]) i--;
							}
						}

					}
					temp[2] = x[1];
					temp[3] = y[1];
					D_4_H = 1;
					break;
				}
			}
			else if (showBoard(i, j) == 2 && showBoard(i + 1, j) == 0 && showBoard(i + 2, j) == 2 && showBoard(i + 3, j) == 2 && showBoard(i + 4, j) == 2) {
				temp[0] = i + 1;
				temp[1] = j;
				xyPair dest = vbMaker(board);
				if (dest.x0 != -1)//dfs ȸ�� ���� fail safe -1 �۵�
				{
					x[0] = dest.x0;
					x[1] = dest.x1;
					y[0] = dest.y0;
					y[1] = dest.y1;
				}
				else//fail safe catch�϶� 1.���� �ֺ� ���� �������� ���� 5���� 2���� �������� ����� ����-����:rst.x0==-1���� �Ź� Ȯ��
				{
					xyPair fin = lastPunch(dest);
					if (fin.x0 != -1)
					{
						x[0] = fin.x0;
						x[1] = fin.x1;
						y[0] = fin.y0;
						y[1] = fin.y1;
					}
					else
					{

						for (int i = 0; i < cnt; i++) {
							do {
								x[i] = rand() % width;
								y[i] = rand() % height;
								if (terminateAI) return;
							} while (!isFree(x[i], y[i]));

							if (x[1] == x[0] && y[1] == y[0]) i--;
						}
					}

				}
				temp[2] = x[1];
				temp[3] = y[1];
				D_4_H = 1;
				break;
			
			}

			else if (showBoard(i, j) == 2 && showBoard(i + 1, j) == 2 && showBoard(i + 2, j) == 0 && showBoard(i + 3, j) == 2 && showBoard(i + 4, j) == 2) {
				temp[0] = i + 2;
				temp[1] = j;
				xyPair dest = vbMaker(board);
				if (dest.x0 != -1)//dfs ȸ�� ���� fail safe -1 �۵�
				{
					x[0] = dest.x0;
					x[1] = dest.x1;
					y[0] = dest.y0;
					y[1] = dest.y1;
				}
				else//fail safe catch�϶� 1.���� �ֺ� ���� �������� ���� 5���� 2���� �������� ����� ����-����:rst.x0==-1���� �Ź� Ȯ��
				{
					xyPair fin = lastPunch(dest);
					if (fin.x0 != -1)
					{
						x[0] = fin.x0;
						x[1] = fin.x1;
						y[0] = fin.y0;
						y[1] = fin.y1;
					}
					else
					{

						for (int i = 0; i < cnt; i++) {
							do {
								x[i] = rand() % width;
								y[i] = rand() % height;
								if (terminateAI) return;
							} while (!isFree(x[i], y[i]));

							if (x[1] == x[0] && y[1] == y[0]) i--;
						}
					}

				}
				temp[2] = x[1];
				temp[3] = y[1];
				D_4_H = 1;
				break;
			}
			else if (showBoard(i, j) == 2 && showBoard(i + 1, j) == 2 && showBoard(i + 2, j) == 2 && showBoard(i + 3, j) == 0 && showBoard(i + 4, j) == 2) {
				temp[0] = i + 3;
				temp[1] = j;
				xyPair dest = vbMaker(board);
				if (dest.x0 != -1)//dfs ȸ�� ���� fail safe -1 �۵�
				{
					x[0] = dest.x0;
					x[1] = dest.x1;
					y[0] = dest.y0;
					y[1] = dest.y1;
				}
				else//fail safe catch�϶� 1.���� �ֺ� ���� �������� ���� 5���� 2���� �������� ����� ����-����:rst.x0==-1���� �Ź� Ȯ��
				{
					xyPair fin = lastPunch(dest);
					if (fin.x0 != -1)
					{
						x[0] = fin.x0;
						x[1] = fin.x1;
						y[0] = fin.y0;
						y[1] = fin.y1;
					}
					else
					{

						for (int i = 0; i < cnt; i++) {
							do {
								x[i] = rand() % width;
								y[i] = rand() % height;
								if (terminateAI) return;
							} while (!isFree(x[i], y[i]));

							if (x[1] == x[0] && y[1] == y[0]) i--;
						}
					}

				}
				temp[2] = x[1];
				temp[3] = y[1];
				D_4_H = 1;
				break;
			}
		}
	}

	for (int i = 0; i < 19; i++) { // ��� - 4�� - ����
		for (int j = 0; j < 16; j++) {
			if (showBoard(i, j) == 2 && showBoard(i, j + 1) == 2 && showBoard(i, j + 2) == 2 && showBoard(i, j + 3) == 2) {
				if (isFree(i, j - 1) && isFree(i, j + 4)) {
					temp[0] = i;
					temp[1] = j - 1;
					temp[2] = i;
					temp[3] = j + 4;

					D_4_V = 1;
					break;
				}
				else if (!isFree(i, j + 4) && isFree(i, j - 1)) { // �Ʒ��ʸ� �����ִ� ���
					temp[0] = i;
					temp[1] = j - 1;
					xyPair dest = vbMaker(board);
					if (dest.x0 != -1)//dfs ȸ�� ���� fail safe -1 �۵�
					{
						x[0] = dest.x0;
						x[1] = dest.x1;
						y[0] = dest.y0;
						y[1] = dest.y1;
					}
					else//fail safe catch�϶� 1.���� �ֺ� ���� �������� ���� 5���� 2���� �������� ����� ����-����:rst.x0==-1���� �Ź� Ȯ��
					{
						xyPair fin = lastPunch(dest);
						if (fin.x0 != -1)
						{
							x[0] = fin.x0;
							x[1] = fin.x1;
							y[0] = fin.y0;
							y[1] = fin.y1;
						}
						else
						{

							for (int i = 0; i < cnt; i++) {
								do {
									x[i] = rand() % width;
									y[i] = rand() % height;
									if (terminateAI) return;
								} while (!isFree(x[i], y[i]));

								if (x[1] == x[0] && y[1] == y[0]) i--;
							}
						}

					}
					temp[2] = x[1];
					temp[3] = y[1];
					D_4_V = 1;
					break;
				}
				else if (isFree(i, j + 4) && !isFree(i, j - 1)) { // ���ʸ� �����ִ� ���
					temp[0] = i;
					temp[1] = j + 4;
					xyPair dest = vbMaker(board);
					if (dest.x0 != -1)//dfs ȸ�� ���� fail safe -1 �۵�
					{
						x[0] = dest.x0;
						x[1] = dest.x1;
						y[0] = dest.y0;
						y[1] = dest.y1;
					}
					else//fail safe catch�϶� 1.���� �ֺ� ���� �������� ���� 5���� 2���� �������� ����� ����-����:rst.x0==-1���� �Ź� Ȯ��
					{
						xyPair fin = lastPunch(dest);
						if (fin.x0 != -1)
						{
							x[0] = fin.x0;
							x[1] = fin.x1;
							y[0] = fin.y0;
							y[1] = fin.y1;
						}
						else
						{

							for (int i = 0; i < cnt; i++) {
								do {
									x[i] = rand() % width;
									y[i] = rand() % height;
									if (terminateAI) return;
								} while (!isFree(x[i], y[i]));

								if (x[1] == x[0] && y[1] == y[0]) i--;
							}
						}

					}
					temp[2] = x[1];
					temp[3] = y[1];
					D_4_V = 1;
					break;
				}
			}
			else if (showBoard(i, j) == 2 && showBoard(i, j + 1) == 0 && showBoard(i, j + 2) == 2 && showBoard(i, j + 3) == 2 && showBoard(i, j + 4) == 2) {
				temp[0] = i;
				temp[1] = j + 1;
				xyPair dest = vbMaker(board);
				if (dest.x0 != -1)//dfs ȸ�� ���� fail safe -1 �۵�
				{
					x[0] = dest.x0;
					x[1] = dest.x1;
					y[0] = dest.y0;
					y[1] = dest.y1;
				}
				else//fail safe catch�϶� 1.���� �ֺ� ���� �������� ���� 5���� 2���� �������� ����� ����-����:rst.x0==-1���� �Ź� Ȯ��
				{
					xyPair fin = lastPunch(dest);
					if (fin.x0 != -1)
					{
						x[0] = fin.x0;
						x[1] = fin.x1;
						y[0] = fin.y0;
						y[1] = fin.y1;
					}
					else
					{

						for (int i = 0; i < cnt; i++) {
							do {
								x[i] = rand() % width;
								y[i] = rand() % height;
								if (terminateAI) return;
							} while (!isFree(x[i], y[i]));

							if (x[1] == x[0] && y[1] == y[0]) i--;
						}
					}

				}
				temp[2] = x[1];
				temp[3] = y[1];
				D_4_V = 1;
				break;
			}
			else if (showBoard(i, j) == 2 && showBoard(i, j + 1) == 2 && showBoard(i, j + 2) == 0 && showBoard(i, j + 3) == 2 && showBoard(i, j + 4) == 2) {
				temp[0] = i;
				temp[1] = j + 2;
				xyPair dest = vbMaker(board);
				if (dest.x0 != -1)//dfs ȸ�� ���� fail safe -1 �۵�
				{
					x[0] = dest.x0;
					x[1] = dest.x1;
					y[0] = dest.y0;
					y[1] = dest.y1;
				}
				else//fail safe catch�϶� 1.���� �ֺ� ���� �������� ���� 5���� 2���� �������� ����� ����-����:rst.x0==-1���� �Ź� Ȯ��
				{
					xyPair fin = lastPunch(dest);
					if (fin.x0 != -1)
					{
						x[0] = fin.x0;
						x[1] = fin.x1;
						y[0] = fin.y0;
						y[1] = fin.y1;
					}
					else
					{

						for (int i = 0; i < cnt; i++) {
							do {
								x[i] = rand() % width;
								y[i] = rand() % height;
								if (terminateAI) return;
							} while (!isFree(x[i], y[i]));

							if (x[1] == x[0] && y[1] == y[0]) i--;
						}
					}

				}
				temp[2] = x[1];
				temp[3] = y[1];
				D_4_V = 1;
				break;
			}
			else if (showBoard(i, j) == 2 && showBoard(i, j + 1) == 2 && showBoard(i, j + 2) == 2 && showBoard(i, j + 3) == 0 && showBoard(i, j + 4) == 2) {
				temp[0] = i;
				temp[1] = j + 3;
				xyPair dest = vbMaker(board);
				if (dest.x0 != -1)//dfs ȸ�� ���� fail safe -1 �۵�
				{
					x[0] = dest.x0;
					x[1] = dest.x1;
					y[0] = dest.y0;
					y[1] = dest.y1;
				}
				else//fail safe catch�϶� 1.���� �ֺ� ���� �������� ���� 5���� 2���� �������� ����� ����-����:rst.x0==-1���� �Ź� Ȯ��
				{
					xyPair fin = lastPunch(dest);
					if (fin.x0 != -1)
					{
						x[0] = fin.x0;
						x[1] = fin.x1;
						y[0] = fin.y0;
						y[1] = fin.y1;
					}
					else
					{

						for (int i = 0; i < cnt; i++) {
							do {
								x[i] = rand() % width;
								y[i] = rand() % height;
								if (terminateAI) return;
							} while (!isFree(x[i], y[i]));

							if (x[1] == x[0] && y[1] == y[0]) i--;
						}
					}

				}
				temp[2] = x[1];
				temp[3] = y[1];
				D_4_V = 1;
				break;
			}
		}
	}

	for (int i = 0; i < 16; i++) { // ��� - 4�� - ���� �밢
		for (int j = 0; j < 16; j++) {
			if (showBoard(i, j) == 2 && showBoard(i + 1, j + 1) == 2 && showBoard(i + 2, j + 2) == 2 && showBoard(i + 3, j + 3) == 2) {
				if (isFree(i - 1, j - 1) && isFree(i + 4, j + 4)) { // ���� �� �� ���� ���
					temp[0] = i - 1;
					temp[1] = j - 1;
					temp[2] = i + 4;
					temp[3] = j + 4;

					D_4_LDG = 1;
					break;
				}
				else if (!isFree(i - 1, j - 1) && isFree(i + 4, j + 4)) { // ���� �����ִ� ���
					temp[0] = i + 4;
					temp[1] = j + 4;
					xyPair dest = vbMaker(board);
					if (dest.x0 != -1)//dfs ȸ�� ���� fail safe -1 �۵�
					{
						x[0] = dest.x0;
						x[1] = dest.x1;
						y[0] = dest.y0;
						y[1] = dest.y1;
					}
					else//fail safe catch�϶� 1.���� �ֺ� ���� �������� ���� 5���� 2���� �������� ����� ����-����:rst.x0==-1���� �Ź� Ȯ��
					{
						xyPair fin = lastPunch(dest);
						if (fin.x0 != -1)
						{
							x[0] = fin.x0;
							x[1] = fin.x1;
							y[0] = fin.y0;
							y[1] = fin.y1;
						}
						else
						{

							for (int i = 0; i < cnt; i++) {
								do {
									x[i] = rand() % width;
									y[i] = rand() % height;
									if (terminateAI) return;
								} while (!isFree(x[i], y[i]));

								if (x[1] == x[0] && y[1] == y[0]) i--;
							}
						}

					}
					temp[2] = x[1];
					temp[3] = y[1];
					D_4_LDG = 1;
					break;
				}
				else if (isFree(i - 1, j - 1) && !isFree(i + 4, j + 4)) { // ���ʸ� �����ִ� ���
					temp[0] = i - 1;
					temp[1] = j - 1;
					xyPair dest = vbMaker(board);
					if (dest.x0 != -1)//dfs ȸ�� ���� fail safe -1 �۵�
					{
						x[0] = dest.x0;
						x[1] = dest.x1;
						y[0] = dest.y0;
						y[1] = dest.y1;
					}
					else//fail safe catch�϶� 1.���� �ֺ� ���� �������� ���� 5���� 2���� �������� ����� ����-����:rst.x0==-1���� �Ź� Ȯ��
					{
						xyPair fin = lastPunch(dest);
						if (fin.x0 != -1)
						{
							x[0] = fin.x0;
							x[1] = fin.x1;
							y[0] = fin.y0;
							y[1] = fin.y1;
						}
						else
						{

							for (int i = 0; i < cnt; i++) {
								do {
									x[i] = rand() % width;
									y[i] = rand() % height;
									if (terminateAI) return;
								} while (!isFree(x[i], y[i]));

								if (x[1] == x[0] && y[1] == y[0]) i--;
							}
						}

					}
					temp[2] = x[1];
					temp[3] = y[1];
					D_4_LDG = 1;
					break;
				}
			}

			else if (showBoard(i, j) == 2 && showBoard(i + 1, j + 1) == 0 && showBoard(i + 2, j + 2) == 2 && showBoard(i + 3, j + 3) == 2 && showBoard(i + 4, j + 4) == 2) {
				temp[0] = i + 1;
				temp[1] = j + 1;
				xyPair dest = vbMaker(board);
				if (dest.x0 != -1)//dfs ȸ�� ���� fail safe -1 �۵�
				{
					x[0] = dest.x0;
					x[1] = dest.x1;
					y[0] = dest.y0;
					y[1] = dest.y1;
				}
				else//fail safe catch�϶� 1.���� �ֺ� ���� �������� ���� 5���� 2���� �������� ����� ����-����:rst.x0==-1���� �Ź� Ȯ��
				{
					xyPair fin = lastPunch(dest);
					if (fin.x0 != -1)
					{
						x[0] = fin.x0;
						x[1] = fin.x1;
						y[0] = fin.y0;
						y[1] = fin.y1;
					}
					else
					{

						for (int i = 0; i < cnt; i++) {
							do {
								x[i] = rand() % width;
								y[i] = rand() % height;
								if (terminateAI) return;
							} while (!isFree(x[i], y[i]));

							if (x[1] == x[0] && y[1] == y[0]) i--;
						}
					}

				}
				temp[2] = x[1];
				temp[3] = y[1];
				D_4_LDG = 1;
				break;
			}

			else if (showBoard(i, j) == 2 && showBoard(i + 1, j + 1) == 2 && showBoard(i + 2, j + 2) == 0 && showBoard(i + 3, j + 3) == 2 && showBoard(i + 4, j + 4) == 2) {
				temp[0] = i + 2;
				temp[1] = j + 2;
				xyPair dest = vbMaker(board);
				if (dest.x0 != -1)//dfs ȸ�� ���� fail safe -1 �۵�
				{
					x[0] = dest.x0;
					x[1] = dest.x1;
					y[0] = dest.y0;
					y[1] = dest.y1;
				}
				else//fail safe catch�϶� 1.���� �ֺ� ���� �������� ���� 5���� 2���� �������� ����� ����-����:rst.x0==-1���� �Ź� Ȯ��
				{
					xyPair fin = lastPunch(dest);
					if (fin.x0 != -1)
					{
						x[0] = fin.x0;
						x[1] = fin.x1;
						y[0] = fin.y0;
						y[1] = fin.y1;
					}
					else
					{

						for (int i = 0; i < cnt; i++) {
							do {
								x[i] = rand() % width;
								y[i] = rand() % height;
								if (terminateAI) return;
							} while (!isFree(x[i], y[i]));

							if (x[1] == x[0] && y[1] == y[0]) i--;
						}
					}

				}
				temp[2] = x[1];
				temp[3] = y[1];
				D_4_LDG = 1;
				break;
			}

			else if (showBoard(i, j) == 2 && showBoard(i + 1, j + 1) == 2 && showBoard(i + 2, j + 2) == 2 && showBoard(i + 3, j + 3) == 0 && showBoard(i + 4, j + 4) == 2) {
				temp[0] = i + 3;
				temp[1] = j + 3;
				xyPair dest = vbMaker(board);
				if (dest.x0 != -1)//dfs ȸ�� ���� fail safe -1 �۵�
				{
					x[0] = dest.x0;
					x[1] = dest.x1;
					y[0] = dest.y0;
					y[1] = dest.y1;
				}
				else//fail safe catch�϶� 1.���� �ֺ� ���� �������� ���� 5���� 2���� �������� ����� ����-����:rst.x0==-1���� �Ź� Ȯ��
				{
					xyPair fin = lastPunch(dest);
					if (fin.x0 != -1)
					{
						x[0] = fin.x0;
						x[1] = fin.x1;
						y[0] = fin.y0;
						y[1] = fin.y1;
					}
					else
					{

						for (int i = 0; i < cnt; i++) {
							do {
								x[i] = rand() % width;
								y[i] = rand() % height;
								if (terminateAI) return;
							} while (!isFree(x[i], y[i]));

							if (x[1] == x[0] && y[1] == y[0]) i--;
						}
					}

				}
				temp[2] = x[1];
				temp[3] = y[1];
				D_4_LDG = 1;
				break;
			}
		}
	}

	for (int i = 0; i < 16; i++) { // ��� - 4�� - ������ �밢
		for (int j = 3; j < 19; j++) {
			if (showBoard(i, j) == 2 && showBoard(i + 1, j - 1) == 2 && showBoard(i + 2, j - 2) == 2 && showBoard(i + 3, j - 3) == 2) {
				if (isFree(i - 1, j + 1) && isFree(i + 4, j - 4)) { // ���� �� �� ���� ���
					temp[0] = i - 1;
					temp[1] = j + 1;
					temp[2] = i + 4;
					temp[3] = j - 4;

					D_4_RDG = 1;
					break;
				}
				else if (!isFree(i - 1, j + 1) && isFree(i + 4, j - 4)) { // �Ʒ��ʸ� �����ִ� ���
					temp[0] = i + 4;
					temp[1] = j - 4;
					xyPair dest = vbMaker(board);
					if (dest.x0 != -1)//dfs ȸ�� ���� fail safe -1 �۵�
					{
						x[0] = dest.x0;
						x[1] = dest.x1;
						y[0] = dest.y0;
						y[1] = dest.y1;
					}
					else//fail safe catch�϶� 1.���� �ֺ� ���� �������� ���� 5���� 2���� �������� ����� ����-����:rst.x0==-1���� �Ź� Ȯ��
					{
						xyPair fin = lastPunch(dest);
						if (fin.x0 != -1)
						{
							x[0] = fin.x0;
							x[1] = fin.x1;
							y[0] = fin.y0;
							y[1] = fin.y1;
						}
						else
						{

							for (int i = 0; i < cnt; i++) {
								do {
									x[i] = rand() % width;
									y[i] = rand() % height;
									if (terminateAI) return;
								} while (!isFree(x[i], y[i]));

								if (x[1] == x[0] && y[1] == y[0]) i--;
							}
						}

					}
					temp[2] = x[1];
					temp[3] = y[1];
					D_4_RDG = 1;
					break;
				}
				else if (isFree(i - 1, j + 1) && !isFree(i + 4, j - 4)) { // ���ʸ� �����ִ� ���
					temp[0] = i - 1;
					temp[1] = j + 1;
					xyPair dest = vbMaker(board);
					if (dest.x0 != -1)//dfs ȸ�� ���� fail safe -1 �۵�
					{
						x[0] = dest.x0;
						x[1] = dest.x1;
						y[0] = dest.y0;
						y[1] = dest.y1;
					}
					else//fail safe catch�϶� 1.���� �ֺ� ���� �������� ���� 5���� 2���� �������� ����� ����-����:rst.x0==-1���� �Ź� Ȯ��
					{
						xyPair fin = lastPunch(dest);
						if (fin.x0 != -1)
						{
							x[0] = fin.x0;
							x[1] = fin.x1;
							y[0] = fin.y0;
							y[1] = fin.y1;
						}
						else
						{

							for (int i = 0; i < cnt; i++) {
								do {
									x[i] = rand() % width;
									y[i] = rand() % height;
									if (terminateAI) return;
								} while (!isFree(x[i], y[i]));

								if (x[1] == x[0] && y[1] == y[0]) i--;
							}
						}

					}
					temp[2] = x[1];
					temp[3] = y[1];
					D_4_RDG = 1;
					break;
				}
			}

			else if (showBoard(i, j) == 2 && showBoard(i + 1, j - 1) == 0 && showBoard(i + 2, j - 2) == 2 && showBoard(i + 3, j - 3) == 2 && showBoard(i + 4, j - 4) == 2) {
				temp[0] = i + 1;
				temp[1] = j - 1;
				xyPair dest = vbMaker(board);
				if (dest.x0 != -1)//dfs ȸ�� ���� fail safe -1 �۵�
				{
					x[0] = dest.x0;
					x[1] = dest.x1;
					y[0] = dest.y0;
					y[1] = dest.y1;
				}
				else//fail safe catch�϶� 1.���� �ֺ� ���� �������� ���� 5���� 2���� �������� ����� ����-����:rst.x0==-1���� �Ź� Ȯ��
				{
					xyPair fin = lastPunch(dest);
					if (fin.x0 != -1)
					{
						x[0] = fin.x0;
						x[1] = fin.x1;
						y[0] = fin.y0;
						y[1] = fin.y1;
					}
					else
					{

						for (int i = 0; i < cnt; i++) {
							do {
								x[i] = rand() % width;
								y[i] = rand() % height;
								if (terminateAI) return;
							} while (!isFree(x[i], y[i]));

							if (x[1] == x[0] && y[1] == y[0]) i--;
						}
					}

				}
				temp[2] = x[1];
				temp[3] = y[1];
				D_4_RDG = 1;
				break;
			}

			else if (showBoard(i, j) == 2 && showBoard(i + 1, j - 1) == 2 && showBoard(i + 2, j - 2) == 0 && showBoard(i + 3, j - 3) == 2 && showBoard(i + 4, j - 4) == 2) {
				temp[0] = i + 2;
				temp[1] = j - 2;
				xyPair dest = vbMaker(board);
				if (dest.x0 != -1)//dfs ȸ�� ���� fail safe -1 �۵�
				{
					x[0] = dest.x0;
					x[1] = dest.x1;
					y[0] = dest.y0;
					y[1] = dest.y1;
				}
				else//fail safe catch�϶� 1.���� �ֺ� ���� �������� ���� 5���� 2���� �������� ����� ����-����:rst.x0==-1���� �Ź� Ȯ��
				{
					xyPair fin = lastPunch(dest);
					if (fin.x0 != -1)
					{
						x[0] = fin.x0;
						x[1] = fin.x1;
						y[0] = fin.y0;
						y[1] = fin.y1;
					}
					else
					{

						for (int i = 0; i < cnt; i++) {
							do {
								x[i] = rand() % width;
								y[i] = rand() % height;
								if (terminateAI) return;
							} while (!isFree(x[i], y[i]));

							if (x[1] == x[0] && y[1] == y[0]) i--;
						}
					}

				}
				temp[2] = x[1];
				temp[3] = y[1];
				D_4_RDG = 1;
				break;
			}

			else if (showBoard(i, j) == 2 && showBoard(i + 1, j - 1) == 2 && showBoard(i + 2, j - 2) == 2 && showBoard(i + 3, j - 3) == 0 && showBoard(i + 4, j - 4) == 2) {
				temp[0] = i + 3;
				temp[1] = j - 3;
				xyPair dest = vbMaker(board);
				if (dest.x0 != -1)//dfs ȸ�� ���� fail safe -1 �۵�
				{
					x[0] = dest.x0;
					x[1] = dest.x1;
					y[0] = dest.y0;
					y[1] = dest.y1;
				}
				else//fail safe catch�϶� 1.���� �ֺ� ���� �������� ���� 5���� 2���� �������� ����� ����-����:rst.x0==-1���� �Ź� Ȯ��
				{
					xyPair fin = lastPunch(dest);
					if (fin.x0 != -1)
					{
						x[0] = fin.x0;
						x[1] = fin.x1;
						y[0] = fin.y0;
						y[1] = fin.y1;
					}
					else
					{

						for (int i = 0; i < cnt; i++) {
							do {
								x[i] = rand() % width;
								y[i] = rand() % height;
								if (terminateAI) return;
							} while (!isFree(x[i], y[i]));

							if (x[1] == x[0] && y[1] == y[0]) i--;
						}
					}

				}
				temp[2] = x[1];
				temp[3] = y[1];
				D_4_RDG = 1;
				break;
			}
		}
	}






	for (int i = 0; i < 15; i++) { // ��� - 5�� - ����
		for (int j = 0; j < 19; j++) {
			if (showBoard(i, j) == 2 && showBoard(i + 1, j) == 2 && showBoard(i + 2, j) == 2 && showBoard(i + 3, j) == 2 && showBoard(i + 4, j) == 2) {
				if (isFree(i - 1, j) && isFree(i + 5, j)) {
					temp[0] = i - 1;
					temp[1] = j;
					temp[2] = i + 5;
					temp[3] = j;

					D_5_H = 1;
					break;
				}
				else if (isFree(i - 1, j) && !isFree(i + 5, j)) { // �����ʸ� �����ִ� ���
					temp[0] = i - 1;
					temp[1] = j;
					xyPair dest = vbMaker(board);
					if (dest.x0 != -1)//dfs ȸ�� ���� fail safe -1 �۵�
					{
						x[0] = dest.x0;
						x[1] = dest.x1;
						y[0] = dest.y0;
						y[1] = dest.y1;
					}
					else//fail safe catch�϶� 1.���� �ֺ� ���� �������� ���� 5���� 2���� �������� ����� ����-����:rst.x0==-1���� �Ź� Ȯ��
					{
						xyPair fin = lastPunch(dest);
						if (fin.x0 != -1)
						{
							x[0] = fin.x0;
							x[1] = fin.x1;
							y[0] = fin.y0;
							y[1] = fin.y1;
						}
						else
						{

							for (int i = 0; i < cnt; i++) {
								do {
									x[i] = rand() % width;
									y[i] = rand() % height;
									if (terminateAI) return;
								} while (!isFree(x[i], y[i]));

								if (x[1] == x[0] && y[1] == y[0]) i--;
							}
						}

					}
					temp[2] = x[1];
					temp[3] = y[1];
					D_5_H = 1;
					break;
				}
				else if (!isFree(i - 1, j) && isFree(i + 5, j)) { // ���ʸ� �����ִ� ���
					temp[0] = i + 5;
					temp[1] = j;
					xyPair dest = vbMaker(board);
					if (dest.x0 != -1)//dfs ȸ�� ���� fail safe -1 �۵�
					{
						x[0] = dest.x0;
						x[1] = dest.x1;
						y[0] = dest.y0;
						y[1] = dest.y1;
					}
					else//fail safe catch�϶� 1.���� �ֺ� ���� �������� ���� 5���� 2���� �������� ����� ����-����:rst.x0==-1���� �Ź� Ȯ��
					{
						xyPair fin = lastPunch(dest);
						if (fin.x0 != -1)
						{
							x[0] = fin.x0;
							x[1] = fin.x1;
							y[0] = fin.y0;
							y[1] = fin.y1;
						}
						else
						{

							for (int i = 0; i < cnt; i++) {
								do {
									x[i] = rand() % width;
									y[i] = rand() % height;
									if (terminateAI) return;
								} while (!isFree(x[i], y[i]));

								if (x[1] == x[0] && y[1] == y[0]) i--;
							}
						}

					}
					temp[2] = x[1];
					temp[3] = y[1];
					D_5_H = 1;
					break;
				}
			}
		}
	}

	for (int i = 0; i < 19; i++) { // ��� - 5�� - ����
		for (int j = 0; j < 15; j++) {
			if (showBoard(i, j) == 2 && showBoard(i, j + 1) == 2 && showBoard(i, j + 2) == 2 && showBoard(i, j + 3) == 2 && showBoard(i, j + 4) == 2) {
				if (isFree(i, j - 1) && isFree(i, j + 5)) {
					temp[0] = i;
					temp[1] = j - 1;
					temp[2] = i;
					temp[3] = j + 5;

					D_5_V = 1;
					break;
				}
				else if (isFree(i, j - 1) && !isFree(i, j + 5)) { // ���ʸ� �����ִ� ���
					temp[0] = i;
					temp[1] = j - 1;
					xyPair dest = vbMaker(board);
					if (dest.x0 != -1)//dfs ȸ�� ���� fail safe -1 �۵�
					{
						x[0] = dest.x0;
						x[1] = dest.x1;
						y[0] = dest.y0;
						y[1] = dest.y1;
					}
					else//fail safe catch�϶� 1.���� �ֺ� ���� �������� ���� 5���� 2���� �������� ����� ����-����:rst.x0==-1���� �Ź� Ȯ��
					{
						xyPair fin = lastPunch(dest);
						if (fin.x0 != -1)
						{
							x[0] = fin.x0;
							x[1] = fin.x1;
							y[0] = fin.y0;
							y[1] = fin.y1;
						}
						else
						{

							for (int i = 0; i < cnt; i++) {
								do {
									x[i] = rand() % width;
									y[i] = rand() % height;
									if (terminateAI) return;
								} while (!isFree(x[i], y[i]));

								if (x[1] == x[0] && y[1] == y[0]) i--;
							}
						}

					}
					temp[2] = x[1];
					temp[3] = y[1];
					D_5_V = 1;
					break;
				}
				else if (!isFree(i, j - 1) && isFree(i, j + 5)) { // �Ʒ��ʸ� �����ִ� ���
					temp[0] = i;
					temp[1] = j + 5;
					xyPair dest = vbMaker(board);
					if (dest.x0 != -1)//dfs ȸ�� ���� fail safe -1 �۵�
					{
						x[0] = dest.x0;
						x[1] = dest.x1;
						y[0] = dest.y0;
						y[1] = dest.y1;
					}
					else//fail safe catch�϶� 1.���� �ֺ� ���� �������� ���� 5���� 2���� �������� ����� ����-����:rst.x0==-1���� �Ź� Ȯ��
					{
						xyPair fin = lastPunch(dest);
						if (fin.x0 != -1)
						{
							x[0] = fin.x0;
							x[1] = fin.x1;
							y[0] = fin.y0;
							y[1] = fin.y1;
						}
						else
						{

							for (int i = 0; i < cnt; i++) {
								do {
									x[i] = rand() % width;
									y[i] = rand() % height;
									if (terminateAI) return;
								} while (!isFree(x[i], y[i]));

								if (x[1] == x[0] && y[1] == y[0]) i--;
							}
						}

					}
					temp[2] = x[1];
					temp[3] = y[1];
					D_5_V = 1;
					break;
				}
			}
		}
	}


	for (int i = 0; i < 15; i++) { // ��� - 5�� - ���� �밢
		for (int j = 0; j < 15; j++) {
			if (showBoard(i, j) == 2 && showBoard(i + 1, j + 1) == 2 && showBoard(i + 2, j + 2) == 2 && showBoard(i + 3, j + 3) == 2 && showBoard(i + 4, j + 4) == 2) {
				if (isFree(i - 1, j - 1) && isFree(i + 5, j + 5)) {
					temp[0] = i - 1;
					temp[1] = j - 1;
					temp[2] = i + 5;
					temp[3] = j + 5;

					D_5_LDG = 1;
					break;
				}
				else if (!isFree(i - 1, j - 1) && isFree(i + 5, j + 5)) { // ���ʸ� �����ִ� ���
					temp[0] = i + 5;
					temp[1] = j + 5;
					xyPair dest = vbMaker(board);
					if (dest.x0 != -1)//dfs ȸ�� ���� fail safe -1 �۵�
					{
						x[0] = dest.x0;
						x[1] = dest.x1;
						y[0] = dest.y0;
						y[1] = dest.y1;
					}
					else//fail safe catch�϶� 1.���� �ֺ� ���� �������� ���� 5���� 2���� �������� ����� ����-����:rst.x0==-1���� �Ź� Ȯ��
					{
						xyPair fin = lastPunch(dest);
						if (fin.x0 != -1)
						{
							x[0] = fin.x0;
							x[1] = fin.x1;
							y[0] = fin.y0;
							y[1] = fin.y1;
						}
						else
						{

							for (int i = 0; i < cnt; i++) {
								do {
									x[i] = rand() % width;
									y[i] = rand() % height;
									if (terminateAI) return;
								} while (!isFree(x[i], y[i]));

								if (x[1] == x[0] && y[1] == y[0]) i--;
							}
						}

					}
					temp[2] = x[1];
					temp[3] = y[1];
					D_5_LDG = 1;
					break;
				}
				else if (isFree(i - 1, j - 1) && !isFree(i + 5, j + 5)) { // �Ʒ��ʸ� �����ִ� ���
					temp[0] = i - 1;
					temp[1] = j - 1;
					xyPair dest = vbMaker(board);
					if (dest.x0 != -1)//dfs ȸ�� ���� fail safe -1 �۵�
					{
						x[0] = dest.x0;
						x[1] = dest.x1;
						y[0] = dest.y0;
						y[1] = dest.y1;
					}
					else//fail safe catch�϶� 1.���� �ֺ� ���� �������� ���� 5���� 2���� �������� ����� ����-����:rst.x0==-1���� �Ź� Ȯ��
					{
						xyPair fin = lastPunch(dest);
						if (fin.x0 != -1)
						{
							x[0] = fin.x0;
							x[1] = fin.x1;
							y[0] = fin.y0;
							y[1] = fin.y1;
						}
						else
						{

							for (int i = 0; i < cnt; i++) {
								do {
									x[i] = rand() % width;
									y[i] = rand() % height;
									if (terminateAI) return;
								} while (!isFree(x[i], y[i]));

								if (x[1] == x[0] && y[1] == y[0]) i--;
							}
						}

					}
					temp[2] = x[1];
					temp[3] = y[1];
					D_5_LDG = 1;
					break;
				}
			}
		}
	}

	for (int i = 0; i < 15; i++) { // ��� - 5�� - ������ �밢
		for (int j = 4; j < 19; j++) {
			if (showBoard(i, j) == 2 && showBoard(i + 1, j - 1) == 2 && showBoard(i + 2, j - 2) == 2 && showBoard(i + 3, j - 3) == 2 && showBoard(i + 4, j - 4) == 2) {
				if (isFree(i - 1, j + 1) && isFree(i + 5, j - 5)) {
					temp[0] = i - 1;
					temp[1] = j + 1;
					temp[2] = i + 5;
					temp[3] = j - 5;

					D_5_RDG = 1;
					break;
				}
				else if (!isFree(i - 1, j + 1) && isFree(i + 5, j - 5)) { // �Ʒ��ʸ� �����ִ� ���
					temp[0] = i + 5;
					temp[1] = j - 5;
					xyPair dest = vbMaker(board);
					if (dest.x0 != -1)//dfs ȸ�� ���� fail safe -1 �۵�
					{
						x[0] = dest.x0;
						x[1] = dest.x1;
						y[0] = dest.y0;
						y[1] = dest.y1;
					}
					else//fail safe catch�϶� 1.���� �ֺ� ���� �������� ���� 5���� 2���� �������� ����� ����-����:rst.x0==-1���� �Ź� Ȯ��
					{
						xyPair fin = lastPunch(dest);
						if (fin.x0 != -1)
						{
							x[0] = fin.x0;
							x[1] = fin.x1;
							y[0] = fin.y0;
							y[1] = fin.y1;
						}
						else
						{

							for (int i = 0; i < cnt; i++) {
								do {
									x[i] = rand() % width;
									y[i] = rand() % height;
									if (terminateAI) return;
								} while (!isFree(x[i], y[i]));

								if (x[1] == x[0] && y[1] == y[0]) i--;
							}
						}

					}
					temp[2] = x[1];
					temp[3] = y[1];
					D_5_LDG = 1;
					break;
				}
				else if (isFree(i - 1, j + 1) && !isFree(i + 5, j - 5)) { // ���ʸ� �����ִ� ���
					temp[0] = i - 1;
					temp[1] = j + 1;
					xyPair dest = vbMaker(board);
					if (dest.x0 != -1)//dfs ȸ�� ���� fail safe -1 �۵�
					{
						x[0] = dest.x0;
						x[1] = dest.x1;
						y[0] = dest.y0;
						y[1] = dest.y1;
					}
					else//fail safe catch�϶� 1.���� �ֺ� ���� �������� ���� 5���� 2���� �������� ����� ����-����:rst.x0==-1���� �Ź� Ȯ��
					{
						xyPair fin = lastPunch(dest);
						if (fin.x0 != -1)
						{
							x[0] = fin.x0;
							x[1] = fin.x1;
							y[0] = fin.y0;
							y[1] = fin.y1;
						}
						else
						{

							for (int i = 0; i < cnt; i++) {
								do {
									x[i] = rand() % width;
									y[i] = rand() % height;
									if (terminateAI) return;
								} while (!isFree(x[i], y[i]));

								if (x[1] == x[0] && y[1] == y[0]) i--;
							}
						}

					}
					temp[2] = x[1];
					temp[3] = y[1];
					D_5_LDG = 1;
					break;
				}
			}
		}
	}



	// ���� - 4�� - ����
	for (int i = 0; i < 16; i++) { // ���� - 4�� - ����
		for (int j = 0; j < 19; j++) {
			if ((showBoard(i, j) == 1 && showBoard(i + 1, j) == 1 && showBoard(i + 2, j) == 1 && showBoard(i + 3, j) == 1)) {
				if (isFree(i - 1, j) && isFree(i - 2, j)) {  // ���� �ΰ��� ��� ���� ���
					temp[0] = i - 1;
					temp[1] = j;
					temp[2] = i - 2;
					temp[3] = j;
					A_4_H = 1;
					break;
				}

				else if (isFree(i + 4, j) && isFree(i + 5, j)) { // ������ �ΰ��� ��� ���� ���
					temp[0] = i + 4;
					temp[1] = j;
					temp[2] = i + 5;
					temp[3] = j;
					A_4_H = 1;
					break;
				}

				else if (isFree(i - 1, j) && isFree(i + 4, j)) { // �� ���� ��� ���� ���
					temp[0] = i - 1;
					temp[1] = j;
					temp[2] = i + 4;
					temp[3] = j;
					A_4_H = 1;
					break;
				}
			}
			else if (showBoard(i, j) == 1 && showBoard(i + 1, j) == 0 && showBoard(i + 2, j) == 1 && showBoard(i + 3, j) == 1 && showBoard(i + 4, j) == 1) { // �߰� ��� �ִ� ��� 1
				    temp[0] = i + 1;
					temp[1] = j;
					if(isFree(i - 1, j)){  // ��� �ΰ� ������ ��� ���� ���
						temp[2] = i - 1;
						temp[3] = j;
						A_4_H = 1;
						break;
					}
					else if(isFree(i + 5, j)) { // ��� �ΰ� �������� ��� ���� ���
						temp[2] = i + 5;
						temp[3] = j;
						A_4_H = 1;
						break;
					}
			}

			else if (showBoard(i, j) == 1 && showBoard(i + 1, j) == 1 && showBoard(i + 2, j) == 0 && showBoard(i + 3, j) == 1 && showBoard(i + 4, j) == 1) { // �߰� ��� �ִ� ��� 2
				temp[0] = i + 2;
				temp[1] = j;
				if (isFree(i - 1, j)) {  // ��� �ΰ� ������ ��� ���� ���
					temp[2] = i - 1;
					temp[3] = j;
					A_4_H = 1;
					break;
				}
				else if (isFree(i + 5, j)) { // ��� �ΰ� �������� ��� ���� ���
					temp[2] = i + 5;
					temp[3] = j;
					A_4_H = 1;
					break;
				}
			}

			else if (showBoard(i, j) == 1 && showBoard(i + 1, j) == 1 && showBoard(i + 2, j) == 1 && showBoard(i + 3, j) == 0 && showBoard(i + 4, j) == 1) { // �߰� ��� �ִ� ��� 2
				temp[0] = i + 3;
				temp[1] = j;
				if (isFree(i - 1, j)) {  // ��� �ΰ� ������ ��� ���� ���
					temp[2] = i - 1;
					temp[3] = j;
					A_4_H = 1;
					break;
				}
				else if (isFree(i + 5, j)) { // ��� �ΰ� �������� ��� ���� ���
					temp[2] = i + 5;
					temp[3] = j;
					A_4_H = 1;
					break;
				}
			}
			else if (showBoard(i, j) == 1 && showBoard(i + 1, j) == 0 && showBoard(i + 2, j) == 0 && showBoard(i + 3, j) == 1 && showBoard(i + 4, j) == 1 && showBoard(i + 5, j) == 1) { // �߰� 2ĭ ��� �ִ� ��� 2
				temp[0] = i + 1;
				temp[1] = j;
				temp[2] = i + 2;
				temp[3] = j;
				A_4_H = 1;
				break;
			}
			else if (showBoard(i, j) == 1 && showBoard(i + 1, j) == 0 && showBoard(i + 2, j) == 1 && showBoard(i + 3, j) == 0 && showBoard(i + 4, j) == 1 && showBoard(i + 5, j) == 1) { // �߰� 2ĭ ��� �ִ� ��� 2
				temp[0] = i + 1;
				temp[1] = j;
				temp[2] = i + 3;
				temp[3] = j;
				A_4_H = 1;
				break;
			}
			else if (showBoard(i, j) == 1 && showBoard(i + 1, j) == 0 && showBoard(i + 2, j) == 1 && showBoard(i + 3, j) == 1 && showBoard(i + 4, j) == 0 && showBoard(i + 5, j) == 1) { // �߰� 2ĭ ��� �ִ� ��� 2
				temp[0] = i + 1;
				temp[1] = j;
				temp[2] = i + 4;
				temp[3] = j;
				A_4_H = 1;
				break;
			}
			else if (showBoard(i, j) == 1 && showBoard(i + 1, j) == 1 && showBoard(i + 2, j) == 0 && showBoard(i + 3, j) == 0 && showBoard(i + 4, j) == 1 && showBoard(i + 5, j) == 1) { // �߰� 2ĭ ��� �ִ� ��� 2
				temp[0] = i + 2;
				temp[1] = j;
				temp[2] = i + 3;
				temp[3] = j;
				A_4_H = 1;
				break;
			}
			else if (showBoard(i, j) == 1 && showBoard(i + 1, j) == 1 && showBoard(i + 2, j) == 0 && showBoard(i + 3, j) == 1 && showBoard(i + 4, j) == 0 && showBoard(i + 5, j) == 1) { // �߰� 2ĭ ��� �ִ� ��� 2
				temp[0] = i + 2;
				temp[1] = j;
				temp[2] = i + 4;
				temp[3] = j;
				A_4_H = 1;
				break;
			}

			else if (showBoard(i, j) == 1 && showBoard(i + 1, j) == 1 && showBoard(i + 2, j) == 1 && showBoard(i + 3, j) == 0 && showBoard(i + 4, j) == 0 && showBoard(i + 5, j) == 1) { // �߰� 2ĭ ��� �ִ� ��� 2
				temp[0] = i + 3;
				temp[1] = j;
				temp[2] = i + 4;
				temp[3] = j;
				A_4_H = 1;
				break;
			}

		}
	}
	// ���� - 4�� - ����
	for (int i = 0; i < 19; i++) { // ���� - 4�� - ����
		for (int j = 0; j < 16; j++) {
			if ((showBoard(i, j) == 1 && showBoard(i , j + 1) == 1 && showBoard(i , j + 2) == 1 && showBoard(i , j + 3) == 1)) {
				if (isFree(i, j - 1) && isFree(i, j - 2)) {  // ���� �ΰ��� ��� ���� ���
					temp[0] = i;
					temp[1] = j - 1;
					temp[2] = i;
					temp[3] = j - 2;
					A_4_V = 1;
					break;
				}

				else if (isFree(i , j + 4) && isFree(i + 5, j + 5)) { // ������ �ΰ��� ��� ���� ���
					temp[0] = i;
					temp[1] = j + 4;
					temp[2] = i;
					temp[3] = j + 5;
					A_4_V = 1;
					break;
				}

				else if (isFree(i , j - 1) && isFree(i , j + 4)) { // �� ���� ��� ���� ���
					temp[0] = i;
					temp[1] = j - 1;
					temp[2] = i;
					temp[3] = j + 4;
					A_4_V = 1;
					break;
				}
			}
			else if (showBoard(i, j) == 1 && showBoard(i, j + 1) == 0 && showBoard(i, j + 2) == 1 && showBoard(i, j + 3) == 1 && showBoard(i, j + 4) == 1) { // �߰� ��� �ִ� ��� 1
				temp[0] = i;
				temp[1] = j + 1;
				if (isFree(i, j - 1)) {  // ��� �ΰ� ������ ��� ���� ���
					temp[2] = i;
					temp[3] = j - 1;
					A_4_V = 1;
					break;
				}
				else if (isFree(i, j + 5)) { // ��� �ΰ� �Ʒ����� ��� ���� ���
					temp[2] = i;
					temp[3] = j + 5;
					A_4_V = 1;
					break;
				}
			}

			else if (showBoard(i, j) == 1 && showBoard(i, j + 1) == 1 && showBoard(i, j + 2) == 0 && showBoard(i, j + 3) == 1 && showBoard(i, j + 4) == 1) { // �߰� ��� �ִ� ��� 2
				temp[0] = i;
				temp[1] = j + 2;
				if (isFree(i, j - 1)) {  // ��� �ΰ� ������ ��� ���� ���
					temp[2] = i;
					temp[3] = j - 1;
					A_4_V = 1;
					break;
				}
				else if (isFree(i, j + 5)) { // ��� �ΰ� �Ʒ����� ��� ���� ���
					temp[2] = i;
					temp[3] = j + 5;
					A_4_V = 1;
					break;
				}
			}

			else if (showBoard(i, j) == 1 && showBoard(i, j + 1) == 1 && showBoard(i, j + 2) == 1 && showBoard(i, j + 3) == 0 && showBoard(i, j + 4) == 1) { // �߰� ��� �ִ� ��� 3
				temp[0] = i;
				temp[1] = j + 3;
				if (isFree(i, j - 1)) {  // ��� �ΰ� ������ ��� ���� ���
					temp[2] = i;
					temp[3] = j - 1;
					A_4_V = 1;
					break;
				}
				else if (isFree(i, j + 5)) { // ��� �ΰ� �Ʒ����� ��� ���� ���
					temp[2] = i;
					temp[3] = j + 5;
					A_4_V = 1;
					break;
				}
			}
		
			
			else if (showBoard(i, j) == 1 && showBoard(i, j + 1) == 0 && showBoard(i, j + 2) == 0 && showBoard(i, j + 3) == 1 && showBoard(i, j + 4) == 1 && showBoard(i, j + 5) == 1) { // �߰� 2ĭ ��� �ִ� ��� 2
				temp[0] = i;
				temp[1] = j + 1;
				temp[2] = i;
				temp[3] = j + 2;
				A_4_V = 1;
				break;
			}
			else if (showBoard(i, j) == 1 && showBoard(i, j + 1) == 0 && showBoard(i, j + 2) == 1 && showBoard(i, j + 3) == 0 && showBoard(i, j + 4) == 1 && showBoard(i, j + 5) == 1) { // �߰� 2ĭ ��� �ִ� ��� 3
				temp[0] = i;
				temp[1] = j + 1;
				temp[2] = i;
				temp[3] = j + 3;
				A_4_V = 1;
				break;
			}
			else if (showBoard(i, j) == 1 && showBoard(i, j + 1) == 0 && showBoard(i, j + 2) == 1 && showBoard(i, j + 3) == 1 && showBoard(i, j + 4) == 0 && showBoard(i, j + 5) == 1) { // �߰� 2ĭ ��� �ִ� ��� 4
				temp[0] = i;
				temp[1] = j + 1;
				temp[2] = i;
				temp[3] = j + 4;
				A_4_V = 1;
				break;
			}
			else if (showBoard(i, j) == 1 && showBoard(i, j + 1) == 1 && showBoard(i, j + 2) == 0 && showBoard(i, j + 3) == 0 && showBoard(i, j + 4) == 1 && showBoard(i, j + 5) == 1) { // �߰� ��� �ִ� ��� 5
				temp[0] = i;
				temp[1] = j + 2;
				temp[2] = i;
				temp[3] = j + 3;
				A_4_V = 1;
				break;
			}
			else if (showBoard(i, j) == 1 && showBoard(i, j + 1) == 1 && showBoard(i, j + 2) == 0 && showBoard(i, j + 3) == 1 && showBoard(i, j + 4) == 0 && showBoard(i, j + 5) == 1) { // �߰� ��� �ִ� ��� 6
				temp[0] = i;
				temp[1] = j + 2;
				temp[2] = i;
				temp[3] = j + 4;
				A_4_V = 1;
				break;
			}

			else if (showBoard(i, j) == 1 && showBoard(i, j + 1) == 1 && showBoard(i, j + 2) == 1 && showBoard(i, j + 3) == 0 && showBoard(i, j + 4) == 0 && showBoard(i, j + 5) == 1) { // �߰� 2ĭ ��� �ִ� ��� 1
				temp[0] = i;
				temp[1] = j + 3;
				temp[2] = i;
				temp[3] = j + 4;
				A_4_V = 1;
				break;
			}
		}
	}
	// ���� - 4�� - ���� �밢��
	for (int i = 0; i < 16; i++) { // ���� - 4�� - ����
		for (int j = 0; j < 16; j++) {
			if ((showBoard(i, j) == 1 && showBoard(i + 1, j + 1) == 1 && showBoard(i + 2, j + 2) == 1 && showBoard(i + 3, j + 3) == 1)) {
				if (isFree(i - 1, j - 1) && isFree(i - 2, j - 2)) {  // ���� �ΰ��� ��� ���� ���
					temp[0] = i - 1;
					temp[1] = j - 1;
					temp[2] = i - 2;
					temp[3] = j - 2;
					A_4_LDG = 1;
					break;
				}

				else if (isFree(i + 4, j + 4) && isFree(i + 5, j + 5)) { // ������ �ΰ��� ��� ���� ���
					temp[0] = i + 4;
					temp[1] = j + 4;
					temp[2] = i + 5;
					temp[3] = j + 5;
					A_4_LDG = 1;
					break;
				}

				else if (isFree(i - 1, j - 1) && isFree(i + 4, j + 4) == 1) { // �� ���� ��� ���� ���
					temp[0] = i - 1;
					temp[1] = j - 1;
					temp[2] = i + 4;
					temp[3] = j + 4;
					A_4_LDG = 1;
					break;
				}
			}
			else if ((showBoard(i, j) == 1 && showBoard(i + 1, j + 1) == 0 && showBoard(i + 2, j + 2) == 1 && showBoard(i + 3, j + 3) == 1) && showBoard(i + 4, j + 4) == 1) { // �߰� ��� �ִ� ��� 1
				temp[0] = i + 1;
				temp[1] = j + 1;
				if (isFree(i - 1, j - 1)) {  // ��� �ΰ� ������ ��� ���� ���
					temp[2] = i - 1;
					temp[3] = j - 1;
					A_4_LDG = 1;
					break;
				}
				else if (isFree(i + 5, j + 5)) { // ��� �ΰ� �������� ��� ���� ���
					temp[2] = i + 5;
					temp[3] = j + 5;
					A_4_LDG = 1;
					break;
				}
			}

			else if (showBoard(i, j) == 1 && showBoard(i + 1, j + 1) == 1 && showBoard(i + 2, j + 2) == 0 && showBoard(i + 3, j + 3) == 1 && showBoard(i + 4, j + 4) == 1) { // �߰� ��� �ִ� ��� 1
				temp[0] = i + 2;
				temp[1] = j + 2;
				if (isFree(i - 1, j - 1)) {  // ��� �ΰ� ������ ��� ���� ���
					temp[2] = i - 1;
					temp[3] = j - 1;
					A_4_LDG = 1;
					break;
				}
				else if (isFree(i + 5, j + 5)) { // ��� �ΰ� �������� ��� ���� ���
					temp[2] = i + 5;
					temp[3] = j + 5;
					A_4_LDG = 1;
					break;
				}
			}

			else if (showBoard(i, j) == 1 && showBoard(i + 1, j + 1) == 1 && showBoard(i + 2, j + 2) == 1 && showBoard(i + 3, j + 3) == 0 && showBoard(i + 4, j + 4) == 1) { // �߰� ��� �ִ� ��� 1
				temp[0] = i + 3;
				temp[1] = j + 3;
				if (isFree(i - 1, j - 1)) {  // ��� �ΰ� ������ ��� ���� ���
					temp[2] = i - 1;
					temp[3] = j - 1;
					A_4_LDG = 1;
					break;
				}
				else if (isFree(i + 5, j + 5)) { // ��� �ΰ� �������� ��� ���� ���
					temp[2] = i + 5;
					temp[3] = j + 5;
					A_4_LDG = 1;
					break;
				}
			}
			else if (showBoard(i, j) == 1 && showBoard(i + 1, j + 1) == 0 && showBoard(i + 2, j + 2) == 0 && showBoard(i + 3, j + 3) == 1 && showBoard(i + 4, j + 4) == 1 && showBoard(i + 5, j + 5) == 1) { // �߰� 2ĭ ��� �ִ� ��� 2
				temp[0] = i + 1;
				temp[1] = j + 1;
				temp[2] = i + 2;
				temp[3] = j + 2;
				A_4_LDG = 1;
				break;
			}
			else if (showBoard(i, j) == 1 && showBoard(i + 1, j + 1) == 0 && showBoard(i + 2, j + 2) == 1 && showBoard(i + 3, j + 3) == 0 && showBoard(i + 4, j + 4) == 1 && showBoard(i + 5, j + 5) == 1) { // �߰� 2ĭ ��� �ִ� ��� 2
				temp[0] = i + 1;
				temp[1] = j + 1;
				temp[2] = i + 3;
				temp[3] = j + 3;
				A_4_LDG = 1;
				break;
			}
			else if (showBoard(i, j) == 1 && showBoard(i + 1, j + 1) == 0 && showBoard(i + 2, j + 2) == 1 && showBoard(i + 3, j + 3) == 1 && showBoard(i + 4, j + 4) == 0 && showBoard(i + 5, j + 5) == 1) { // �߰� 2ĭ ��� �ִ� ��� 2
				temp[0] = i + 1;
				temp[1] = j + 1;
				temp[2] = i + 4;
				temp[3] = j + 4;
				A_4_LDG = 1;
				break;
			}
			else if (showBoard(i, j) == 1 && showBoard(i + 1, j + 1) == 1 && showBoard(i + 2, j + 2) == 0 && showBoard(i + 3, j + 3) == 0 && showBoard(i + 4, j + 4) == 1 && showBoard(i + 5, j + 5) == 1) { // �߰� 2ĭ ��� �ִ� ��� 2
				temp[0] = i + 2;
				temp[1] = j + 2;
				temp[2] = i + 3;
				temp[3] = j + 3;
				A_4_LDG = 1;
				break;
			}
			else if (showBoard(i, j) == 1 && showBoard(i + 1, j + 1) == 1 && showBoard(i + 2, j + 2) == 0 && showBoard(i + 3, j + 3) == 1 && showBoard(i + 4, j + 4) == 0 && showBoard(i + 5, j + 5) == 1) { // �߰� 2ĭ ��� �ִ� ��� 2
				temp[0] = i + 2;
				temp[1] = j + 2;
				temp[2] = i + 4;
				temp[3] = j + 4;
				A_4_LDG = 1;
				break;
			}

			else if (showBoard(i, j) == 1 && showBoard(i + 1, j + 1) == 1 && showBoard(i + 2, j + 2) == 1 && showBoard(i + 3, j + 3) == 0 && showBoard(i + 4, j + 4) == 0 && showBoard(i + 5, j + 5) == 1) { // �߰� 2ĭ ��� �ִ� ��� 2
				temp[0] = i + 3;
				temp[1] = j + 3;
				temp[2] = i + 4;
				temp[3] = j + 4;
				A_4_LDG = 1;
				break;
			}

		}
	}

	// ���� - 4�� - ������ �밢��

	for (int i = 0; i < 16; i++) { // ���� - 4�� - ����
		for (int j = 3; j < 19; j++) {
			if ((showBoard(i, j) == 1 && showBoard(i + 1, j - 1) == 1 && showBoard(i + 2, j - 2) == 1 && showBoard(i + 3, j - 3) == 1)) {
				if (isFree(i - 1, j + 1) && isFree(i - 2, j + 2)) {  // ���� �ΰ��� ��� ���� ���
					temp[0] = i - 1;
					temp[1] = j + 1;
					temp[2] = i - 2;
					temp[3] = j + 2;
					A_4_RDG = 1;
					break;
				}

				else if (isFree(i + 4, j - 4) && isFree(i + 5, j - 5)) { // ������ �ΰ��� ��� ���� ���
					temp[0] = i + 4;
					temp[1] = j - 4;
					temp[2] = i + 5;
					temp[3] = j - 5;
					A_4_RDG = 1;
					break;
				}

				else if (isFree(i - 1, j + 1) && isFree(i + 4, j - 4) == 1) { // �� ���� ��� ���� ���
					temp[0] = i - 1;
					temp[1] = j + 1;
					temp[2] = i + 4;
					temp[3] = j - 4;
					A_4_RDG = 1;
					break;
				}
			}
			else if (showBoard(i, j) == 1 && showBoard(i + 1, j - 1) == 0 && showBoard(i + 2, j - 2) == 1 && showBoard(i + 3, j - 3) == 1 && showBoard(i + 4, j - 4) == 1) { // �߰� ��� �ִ� ��� 1
				temp[0] = i + 1;
				temp[1] = j - 1;
				if (isFree(i - 1, j + 1)) {  // ��� �ΰ� ������ ��� ���� ���
					temp[2] = i - 1;
					temp[3] = j + 1;
					A_4_RDG = 1;
					break;
				}
				else if (isFree(i + 5, j - 5)) { // ��� �ΰ� �������� ��� ���� ���
					temp[2] = i + 5;
					temp[3] = j - 5;
					A_4_RDG = 1;
					break;
				}
			}

			else if (showBoard(i, j) == 1 && showBoard(i + 1, j - 1) == 1 && showBoard(i + 2, j - 2) == 0 && showBoard(i + 3, j - 3) == 1 && showBoard(i + 4, j - 4) == 1) { // �߰� ��� �ִ� ��� 1
				temp[0] = i + 2;
				temp[1] = j - 2;
				if (isFree(i - 1, j + 1)) {  // ��� �ΰ� ������ ��� ���� ���
					temp[2] = i - 1;
					temp[3] = j + 1;
					A_4_RDG = 1;
					break;
				}
				else if (isFree(i + 5, j - 5)) { // ��� �ΰ� �������� ��� ���� ���
					temp[2] = i + 5;
					temp[3] = j - 5;
					A_4_RDG = 1;
					break;
				}
			}

			else if (showBoard(i, j) == 1 && showBoard(i + 1, j - 1) == 1 && showBoard(i + 2, j - 2) == 1 && showBoard(i + 3, j - 3) == 0 && showBoard(i + 4, j - 4) == 1) { // �߰� ��� �ִ� ��� 1
				temp[0] = i + 3;
				temp[1] = j - 3;
				if (isFree(i - 1, j + 1)) {  // ��� �ΰ� ������ ��� ���� ���
					temp[2] = i - 1;
					temp[3] = j + 1;
					A_4_RDG = 1;
					break;
				}
				else if (isFree(i + 5, j - 5)) { // ��� �ΰ� �������� ��� ���� ���
					temp[2] = i + 5;
					temp[3] = j - 5;
					A_4_RDG = 1;
					break;
				}
			}
			else if (showBoard(i, j) == 1 && showBoard(i + 1, j - 1) == 0 && showBoard(i + 2, j - 2) == 0 && showBoard(i + 3, j - 3) == 1 && showBoard(i + 4, j - 4) == 1 && showBoard(i + 5, j - 5) == 1) { // �߰� 2ĭ ��� �ִ� ��� 2
				temp[0] = i + 1;
				temp[1] = j - 1;
				temp[2] = i + 2;
				temp[3] = j - 2;
				A_4_RDG = 1;
				break;
			}
			else if (showBoard(i, j) == 1 && showBoard(i + 1, j - 1) == 0 && showBoard(i + 2, j - 2) == 1 && showBoard(i + 3, j - 3) == 0 && showBoard(i + 4, j - 4) == 1 && showBoard(i + 5, j - 5) == 1) { // �߰� 2ĭ ��� �ִ� ��� 2
				temp[0] = i + 1;
				temp[1] = j - 1;
				temp[2] = i + 3;
				temp[3] = j - 3;
				A_4_RDG = 1;
				break;
			}
			else if (showBoard(i, j) == 1 && showBoard(i + 1, j - 1) == 0 && showBoard(i + 2, j - 2) == 1 && showBoard(i + 3, j - 3) == 1 && showBoard(i + 4, j - 4) == 0 && showBoard(i + 5, j - 5) == 1) { // �߰� 2ĭ ��� �ִ� ��� 2
				temp[0] = i + 1;
				temp[1] = j - 1;
				temp[2] = i + 4;
				temp[3] = j - 4;
				A_4_RDG = 1;
				break;
			}
			else if (showBoard(i, j) == 1 && showBoard(i + 1, j - 1) == 1 && showBoard(i + 2, j - 2) == 0 && showBoard(i + 3, j - 3) == 0 && showBoard(i + 4, j - 4) == 1 && showBoard(i + 5, j - 5) == 1) { // �߰� 2ĭ ��� �ִ� ��� 2
				temp[0] = i + 2;
				temp[1] = j - 2;
				temp[2] = i + 3;
				temp[3] = j - 3;
				A_4_RDG = 1;
				break;
			}
			else if (showBoard(i, j) == 1 && showBoard(i + 1, j - 1) == 1 && showBoard(i + 2, j - 2) == 0 && showBoard(i + 3, j - 3) == 1 && showBoard(i + 4, j - 4) == 0 && showBoard(i + 5, j - 5) == 1) { // �߰� 2ĭ ��� �ִ� ��� 2
				temp[0] = i + 2;
				temp[1] = j - 2;
				temp[2] = i + 4;
				temp[3] = j - 4;
				A_4_RDG = 1;
				break;
			}

			else if (showBoard(i, j) == 1 && showBoard(i + 1, j - 1) == 1 && showBoard(i + 2, j - 2) == 1 && showBoard(i + 3, j - 3) == 0 && showBoard(i + 4, j - 4) == 0 && showBoard(i + 5, j - 5) == 1) { // �߰� 2ĭ ��� �ִ� ��� 2
				temp[0] = i + 3;
				temp[1] = j - 3;
				temp[2] = i + 4;
				temp[3] = j - 4;
				A_4_RDG = 1;
				break;
			}
		}
	}


	// �Ǵ� ������ üũ
	if (D_4_H == 1) { // ��� 4�� ����
		x[0] = temp[0];
		y[0] = temp[1];
		x[1] = temp[2];
		y[1] = temp[3];
	}

	else if (D_4_V == 1) { // ��� 4�� ����
		x[0] = temp[0];
		y[0] = temp[1];
		x[1] = temp[2];
		y[1] = temp[3];
	}

	else if (D_4_LDG == 1) { // ��� 4�� ���� �밢 
		x[0] = temp[0];
		y[0] = temp[1];
		x[1] = temp[2];
		y[1] = temp[3];
	}

	else if (D_4_RDG == 1) { // ��� 4�� ������ �밢 
		x[0] = temp[0];
		y[0] = temp[1];
		x[1] = temp[2];
		y[1] = temp[3];
	}

	else if (D_5_H == 1) { // ��� 5�� ���� 
		x[0] = temp[0];
		y[0] = temp[1];
		x[1] = temp[2];
		y[1] = temp[3];
	}

	else if (D_5_V == 1) { // ��� 5�� ����
		x[0] = temp[0];
		y[0] = temp[1];
		x[1] = temp[2];
		y[1] = temp[3];
	}

	else if (D_5_LDG == 1) { // ��� 5�� ���� �밢
		x[0] = temp[0];
		y[0] = temp[1];
		x[1] = temp[2];
		y[1] = temp[3];
	}

	else if (D_5_RDG == 1) { // ��� 5�� ������ �밢
		x[0] = temp[0];
		y[0] = temp[1];
		x[1] = temp[2];
		y[1] = temp[3];
	}

	else if (A_4_H == 1) {
		x[0] = temp[0];
		y[0] = temp[1];
		x[1] = temp[2];
		y[1] = temp[3];
	}

	else if(A_4_V == 1){
		x[0] = temp[0];
		y[0] = temp[1];
		x[1] = temp[2];
		y[1] = temp[3];
	}

	else if (A_4_LDG == 1) {
		x[0] = temp[0];
		y[0] = temp[1];
		x[1] = temp[2];
		y[1] = temp[3];
	}

	else if (A_4_RDG == 1) {
		x[0] = temp[0];
		y[0] = temp[1];
		x[1] = temp[2];
		y[1] = temp[3];
	}

	else if (A_5_H == 1) {
		x[0] = temp[0];
		y[0] = temp[1];
		x[1] = temp[2];
		y[1] = temp[3];
	}

	else if (A_5_V == 1) {
		x[0] = temp[0];
		y[0] = temp[1];
		x[1] = temp[2];
		y[1] = temp[3];
	}

	else if (A_5_LDG == 1) {
		x[0] = temp[0];
		y[0] = temp[1];
		x[1] = temp[2];
		y[1] = temp[3];
	}

	else if (A_5_RDG == 1) {
		x[0] = temp[0];
		y[0] = temp[1];
		x[1] = temp[2];
		y[1] = temp[3];
	}

	else {
		if (cnt == 1 && gcnt == 1)//������ �������� ������ ���� �˰���
		{
			xy tmp = blackFirst();
			x[0] = tmp.x;
			y[0] = tmp.y;
		}
		else if (cnt == 2 && gcnt == 1)//������ �������� �İ��� ó�� �ΰ� ���� �˰���
		{

			xy tmp = singleChecker(2);//���� ���� �浹�� ��ġ�� ã�ƿ´�
			xyPair dest = twoBuilder(tmp);//�浹 ���� �ֺ� ��� �ΰ� ���� ��� �˻�

			x[0] = dest.x0;
			x[1] = dest.x1;
			y[0] = dest.y0;
			y[1] = dest.y1;

		}
		else if (isBlackT2(board))//���� �ι�° ���� �˰���. �ڽ��� ��ġ�� ã�Ƽ� dfs Ȱ���Ѵ�.
		{
			xy tmp = singleChecker(1);//�� �浹 �ϳ� ã�ƿ´�
			xyPair dest = dfs(tmp, 5, true);//�浹 ���� �ֺ� �ΰ� ���� ��� �˻�. �ϳ� �����ϱ� ������ �ټ��� �̾ �� ���ִ��� 8���⺰�� Ž���Ѵ�.

			x[0] = dest.x0;
			x[1] = dest.x1;
			y[0] = dest.y0;
			y[1] = dest.y1;
		}
		else if (cnt == 2 && gcnt > 1)//���� ù��° ���� ���� �� ���� �ι�° ���� ������ 1. ������ ã�Ƽ� 8���� ���� Ȯ���� �׹��� ���ΰ� ������ �ʾ����� �̾ ���δ�. 2.�� ��� ������ ���ΰ� �����ٸ� �� �ֺ����� dfs Ȱ�� �Ѵ�.
		{
			xyPair dest = vbMaker(board);
			if (dest.x0 != -1)//dfs ȸ�� ���� fail safe -1 �۵�
			{
				x[0] = dest.x0;
				x[1] = dest.x1;
				y[0] = dest.y0;
				y[1] = dest.y1;
			}
			else//fail safe catch�϶� 1.���� �ֺ� ���� �������� ���� 5���� 2���� �������� ����� ����-����:rst.x0==-1���� �Ź� Ȯ��
			{
				xyPair fin = lastPunch(dest);
				if (fin.x0 != -1)
				{
					x[0] = fin.x0;
					x[1] = fin.x1;
					y[0] = fin.y0;
					y[1] = fin.y1;
				}
				else
				{

					for (int i = 0; i < cnt; i++) {
						do {
							x[i] = rand() % width;
							y[i] = rand() % height;
							if (terminateAI) return;
						} while (!isFree(x[i], y[i]));

						if (x[1] == x[0] && y[1] == y[0]) i--;
					}
				}

			}
		}
	}
	domymove(x, y, cnt);
}

