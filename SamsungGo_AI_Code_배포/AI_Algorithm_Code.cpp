// Samsung Go Tournament Form C (g++-4.8.3)

/*
[AI 코드 작성 방법]

1. char info[]의 배열 안에               "TeamName:자신의 팀명,Department:자신의 소속"               순서로 작성합니다.
( 주의 ) Teamname:과 Department:는 꼭 들어가야 합니다.
"자신의 팀명", "자신의 소속"을 수정해야 합니다.

2. 아래의 myturn() 함수 안에 자신만의 AI 코드를 작성합니다.

3. AI 파일을 테스트 하실 때는 "육목 알고리즘대회 툴"을 사용합니다.

4. 육목 알고리즘 대회 툴의 연습하기에서 바둑돌을 누른 후, 자신의 "팀명" 이 들어간 알고리즘을 추가하여 테스트 합니다.



[변수 및 함수]
myturn(int cnt) : 자신의 AI 코드를 작성하는 메인 함수 입니다.
int cnt (myturn()함수의 파라미터) : 돌을 몇 수 둬야하는지 정하는 변수, cnt가 1이면 육목 시작 시  한 번만  두는 상황(한 번), cnt가 2이면 그 이후 돌을 두는 상황(두 번)
int  x[0], y[0] : 자신이 둘 첫 번 째 돌의 x좌표 , y좌표가 저장되어야 합니다.
int  x[1], y[1] : 자신이 둘 두 번 째 돌의 x좌표 , y좌표가 저장되어야 합니다.
void domymove(int x[], int y[], cnt) : 둘 돌들의 좌표를 저장해서 출력


//int board[BOARD_SIZE][BOARD_SIZE]; 바둑판 현재상황 담고 있어 바로사용 가능함. 단, 원본데이터로 수정 절대금지
// 놓을수 없는 위치에 바둑돌을 놓으면 실격패 처리.

boolean ifFree(int x, int y) : 현재 [x,y]좌표에 바둑돌이 있는지 확인하는 함수 (없으면 true, 있으면 false)
int showBoard(int x, int y) : [x, y] 좌표에 무슨 돌이 존재하는지 보여주는 함수 (1 = 자신의 돌, 2 = 상대의 돌, 3 = 블럭킹)


<-------AI를 작성하실 때, 같은 이름의 함수 및 변수 사용을 권장하지 않습니다----->
*/

#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include "Connect6Algo.h"



// "샘플코드[C]"  -> 자신의 팀명 (수정)
// "AI부서[C]"  -> 자신의 소속 (수정)
// 제출시 실행파일은 반드시 팀명으로 제출!
char info[] = { "TeamName:육목스님,Department:동국대학교 정각원" };
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

xy blackFirst()//흑돌 첫 수 함수
{
	int points[8][2] = { { 3,3 },{ 3,9 },{ 3,15 },{ 9,3 },{ 9,15 },{ 15,3 },{ 15,9 },{ 15,15 } };
	xy tmp;
	int index = 0;
	if (isFree(9, 9))//가운데 착수가 유리
	{
		tmp.x = 9;
		tmp.y = 9;
		return tmp;
	}
	else//가운데에 블럭 들어가있으면
	{
		do {
			index = rand() % 8;
			tmp.x = points[index][0];
			tmp.y = points[index][1];
		} while (!isFree(tmp.x, tmp.y));
		return tmp;
	}
	
}
bool isBlackT2(int board[][20])//흑돌의 두번째 턴인지 보는 함수
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

xyPair dfs(xy center, int until, bool recur)//center 기준 8방향 탐색 until개 까지 붙여서 만들 수 있는지 찾아보고 가능하면 그 방향 두 좌표 리턴 함수
{
	int x = center.x;
	int y = center.y;
	xyPair rst;
	bool flag = true;
	//좌상대각
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
	//우상대각
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
	//좌하대각
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
	//우하대각
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
	//상수직
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
	//하수직
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
	//좌수평
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
	//우수평
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
	//이하 개노답인경우 재귀. 자기 돌 주변 8방향 곳 중 두곳이 상대걸로 막혀있으며 나머지 여섯곳은 블락이 되어있는 노답일때 상대의 모든 돌에 대해 twoBuilder를 조진다. twoBuilder 내부에서 다시 dfs 재귀호출할 가능성은 희박하므로 상정하지 않았다.
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
xyPair twoBuilder(xy center)//상대 돌 하나 주변 최적의 두개를 쌓는 함수 1. 마름모 판별을 시도후 2.없으면 내돌 8방향 dfs 시행
{
	int x = center.x;
	int y = center.y;
	xyPair rst;
	//제일 좋은 마름모 대각 판별
	if ((isFree(x + 1, y - 2) && isFree(x + 2, y - 3)) && (isFree(x - 2, y + 1) && isFree(x - 3, y + 2)))//9-12시 대각
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
	if ((isFree(x - 1, y - 2) && isFree(x - 2, y - 3)) && (isFree(x + 2, y + 1) && isFree(x + 3, y + 2)))//3-12시 대각
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
	if ((isFree(x - 2, y - 1) && isFree(x - 3, y - 2)) && (isFree(x + 1, y + 2) && isFree(x + 2, y + 3)))//9-6시 대각
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

	if ((isFree(x + 2, y - 1) && isFree(x + 3, y - 2)) && (isFree(x - 1, y + 2) && isFree(x - 2, y + 3)))//3-6시 대각
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
	//8방향 깊이 우선 탐색 알고리즘
	
	{
		return dfs(center, 5, false);
	}
}
xy singleChecker(int pia)//피아식별 1,2로 내돌이나 상대 돌 하나를 가져온다.
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

xyPair vbMaker(int board[][20])//가중치 보드 제작
{

	int vb[20][20][2] = { 0, };//3차원 인덱스 0 에는 최대 가중치, 1에는 그때의 놔야될 방향
							   //좌상대각0
							   //우상대각1
							   //상수직2
							   //좌수평3
							   //우수평4
							   //하수직5
							   //좌하대각6
							   //우하대각7

							   //이하 이어야 할 가장 최적의 돌 정보
	int maxfreq = 0;//현재까지 이은 돌 개수
	int maxway = -1;//진행 방향
	int maxi = -1;//돌 x위치
	int maxj = -1;//돌 y위치
	int totalmine = 0;
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (board[i][j] == 1)
			{
				totalmine += 1;
				int direction[8] = { 0, };
				//좌상대각
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
				//우상대각
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
				//좌하대각
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
				//우하대각
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
				//상수직
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
				//하수직
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
				//좌수평
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
				//우수평
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
				int dirmaxvalue = 0;//가장 최대치 direction 찾음
				int dirmax = -1;//그때의 방향

				for (int i = 0; i < 8; i++)
				{
					if (dirmaxvalue < direction[i])
					{
						dirmaxvalue = direction[i];
						dirmax = 7 - i;
					}
				}

				if (vb[i][j][0] < dirmaxvalue)//현재 가중치 보드에 저장된 가장 큰 이음값
				{
					vb[i][j][0] = dirmaxvalue;//가장 큰 이음값 저장
					vb[i][j][1] = dirmax;//그때 방향
				}
			}
		}
	}
	int tmindex = 0;
	vec queue[361];
	for (int i = 0; i < 20; i++)//가중치 보드 최대값 찾기
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
	//최대값 벡터로 두개 놔보고 안되면 벡터 소팅해서 하나씩 해보고 안되면 dfs 간다.
	int x = maxi;
	int y = maxj;
	xyPair rst;
	//최대값 돌에 대한 두 개 이어 반환
	bool flag = true;
	switch (maxway)
	{
	case 0:	//좌상대각0
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
	case 1: //우상대각1
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
	case 2://상수직2
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
	case 3://좌수평3
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
	case 4://우수평4
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
	case 5://하수직5
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
	case 6://좌하대각6
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
	case 7://우하대각7
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
	//여기 까지 오면 최대 값 가지고 안되는거다. 내림차순 정렬해서 이음 가중치 큰 것 부터 공격 개시
	if (flag)
	{
		rst = vecqueSorter(queue, totalmine, maxfreq);
		return rst;
	}
}
xyPair vecqueSorter(vec queue[], int totalmine, int maxfreq)
{
	for (int mf = maxfreq; mf > 0; mf--)//이음 가중치 큰 것 부터 공격 개시
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
				case 0:	//좌상대각0
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
				case 1: //우상대각1
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
				case 2://상수직2
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
				case 3://좌수평3
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
				case 4://우수평4
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
				case 5://하수직5
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
				case 6://좌하대각6
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
				case 7://우하대각7
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
	//모든 가능한 돌에 대해 이음 가능 경로 없을시 dfs 공격
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
xyPair lastPunch(xyPair dest)//마지막 공격. 이거안되면 랜덤
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
	//판단 변수 A,D_4,5_H,V,LDG,RDG
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
	/*for문 알고리즘 주석 형식 : who - num - direction - A/D*/

	for (int i = 0; i < 16; i++) { // 방어 - 4개 - 가로
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
				else if (isFree(i - 1, j) && !isFree(i + 4, j)) { // 오른쪽만 막혀있는 경우
					temp[0] = i - 1;
					temp[1] = j;
					
				}
				else if (!isFree(i - 1, j) && isFree(i + 4, j)) { // 왼쪽만 막혀있는 경우
					temp[0] = i + 4;
					temp[1] = j;
					xyPair dest = vbMaker(board);
					if (dest.x0 != -1)//dfs 회귀 방지 fail safe -1 작동
					{
						x[0] = dest.x0;
						x[1] = dest.x1;
						y[0] = dest.y0;
						y[1] = dest.y1;
					}
					else//fail safe catch일때 1.내꺼 주변 빌딩 가능한지 예측 5에서 2까지 가능한지 만들어 보기-조건:rst.x0==-1인지 매번 확인
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
				if (dest.x0 != -1)//dfs 회귀 방지 fail safe -1 작동
				{
					x[0] = dest.x0;
					x[1] = dest.x1;
					y[0] = dest.y0;
					y[1] = dest.y1;
				}
				else//fail safe catch일때 1.내꺼 주변 빌딩 가능한지 예측 5에서 2까지 가능한지 만들어 보기-조건:rst.x0==-1인지 매번 확인
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
				if (dest.x0 != -1)//dfs 회귀 방지 fail safe -1 작동
				{
					x[0] = dest.x0;
					x[1] = dest.x1;
					y[0] = dest.y0;
					y[1] = dest.y1;
				}
				else//fail safe catch일때 1.내꺼 주변 빌딩 가능한지 예측 5에서 2까지 가능한지 만들어 보기-조건:rst.x0==-1인지 매번 확인
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
				if (dest.x0 != -1)//dfs 회귀 방지 fail safe -1 작동
				{
					x[0] = dest.x0;
					x[1] = dest.x1;
					y[0] = dest.y0;
					y[1] = dest.y1;
				}
				else//fail safe catch일때 1.내꺼 주변 빌딩 가능한지 예측 5에서 2까지 가능한지 만들어 보기-조건:rst.x0==-1인지 매번 확인
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

	for (int i = 0; i < 19; i++) { // 방어 - 4개 - 세로
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
				else if (!isFree(i, j + 4) && isFree(i, j - 1)) { // 아래쪽만 막혀있는 경우
					temp[0] = i;
					temp[1] = j - 1;
					xyPair dest = vbMaker(board);
					if (dest.x0 != -1)//dfs 회귀 방지 fail safe -1 작동
					{
						x[0] = dest.x0;
						x[1] = dest.x1;
						y[0] = dest.y0;
						y[1] = dest.y1;
					}
					else//fail safe catch일때 1.내꺼 주변 빌딩 가능한지 예측 5에서 2까지 가능한지 만들어 보기-조건:rst.x0==-1인지 매번 확인
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
				else if (isFree(i, j + 4) && !isFree(i, j - 1)) { // 위쪽만 막혀있는 경우
					temp[0] = i;
					temp[1] = j + 4;
					xyPair dest = vbMaker(board);
					if (dest.x0 != -1)//dfs 회귀 방지 fail safe -1 작동
					{
						x[0] = dest.x0;
						x[1] = dest.x1;
						y[0] = dest.y0;
						y[1] = dest.y1;
					}
					else//fail safe catch일때 1.내꺼 주변 빌딩 가능한지 예측 5에서 2까지 가능한지 만들어 보기-조건:rst.x0==-1인지 매번 확인
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
				if (dest.x0 != -1)//dfs 회귀 방지 fail safe -1 작동
				{
					x[0] = dest.x0;
					x[1] = dest.x1;
					y[0] = dest.y0;
					y[1] = dest.y1;
				}
				else//fail safe catch일때 1.내꺼 주변 빌딩 가능한지 예측 5에서 2까지 가능한지 만들어 보기-조건:rst.x0==-1인지 매번 확인
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
				if (dest.x0 != -1)//dfs 회귀 방지 fail safe -1 작동
				{
					x[0] = dest.x0;
					x[1] = dest.x1;
					y[0] = dest.y0;
					y[1] = dest.y1;
				}
				else//fail safe catch일때 1.내꺼 주변 빌딩 가능한지 예측 5에서 2까지 가능한지 만들어 보기-조건:rst.x0==-1인지 매번 확인
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
				if (dest.x0 != -1)//dfs 회귀 방지 fail safe -1 작동
				{
					x[0] = dest.x0;
					x[1] = dest.x1;
					y[0] = dest.y0;
					y[1] = dest.y1;
				}
				else//fail safe catch일때 1.내꺼 주변 빌딩 가능한지 예측 5에서 2까지 가능한지 만들어 보기-조건:rst.x0==-1인지 매번 확인
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

	for (int i = 0; i < 16; i++) { // 방어 - 4개 - 왼쪽 대각
		for (int j = 0; j < 16; j++) {
			if (showBoard(i, j) == 2 && showBoard(i + 1, j + 1) == 2 && showBoard(i + 2, j + 2) == 2 && showBoard(i + 3, j + 3) == 2) {
				if (isFree(i - 1, j - 1) && isFree(i + 4, j + 4)) { // 양쪽 다 안 막힌 경우
					temp[0] = i - 1;
					temp[1] = j - 1;
					temp[2] = i + 4;
					temp[3] = j + 4;

					D_4_LDG = 1;
					break;
				}
				else if (!isFree(i - 1, j - 1) && isFree(i + 4, j + 4)) { // 위만 막혀있는 경우
					temp[0] = i + 4;
					temp[1] = j + 4;
					xyPair dest = vbMaker(board);
					if (dest.x0 != -1)//dfs 회귀 방지 fail safe -1 작동
					{
						x[0] = dest.x0;
						x[1] = dest.x1;
						y[0] = dest.y0;
						y[1] = dest.y1;
					}
					else//fail safe catch일때 1.내꺼 주변 빌딩 가능한지 예측 5에서 2까지 가능한지 만들어 보기-조건:rst.x0==-1인지 매번 확인
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
				else if (isFree(i - 1, j - 1) && !isFree(i + 4, j + 4)) { // 위쪽만 막혀있는 경우
					temp[0] = i - 1;
					temp[1] = j - 1;
					xyPair dest = vbMaker(board);
					if (dest.x0 != -1)//dfs 회귀 방지 fail safe -1 작동
					{
						x[0] = dest.x0;
						x[1] = dest.x1;
						y[0] = dest.y0;
						y[1] = dest.y1;
					}
					else//fail safe catch일때 1.내꺼 주변 빌딩 가능한지 예측 5에서 2까지 가능한지 만들어 보기-조건:rst.x0==-1인지 매번 확인
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
				if (dest.x0 != -1)//dfs 회귀 방지 fail safe -1 작동
				{
					x[0] = dest.x0;
					x[1] = dest.x1;
					y[0] = dest.y0;
					y[1] = dest.y1;
				}
				else//fail safe catch일때 1.내꺼 주변 빌딩 가능한지 예측 5에서 2까지 가능한지 만들어 보기-조건:rst.x0==-1인지 매번 확인
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
				if (dest.x0 != -1)//dfs 회귀 방지 fail safe -1 작동
				{
					x[0] = dest.x0;
					x[1] = dest.x1;
					y[0] = dest.y0;
					y[1] = dest.y1;
				}
				else//fail safe catch일때 1.내꺼 주변 빌딩 가능한지 예측 5에서 2까지 가능한지 만들어 보기-조건:rst.x0==-1인지 매번 확인
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
				if (dest.x0 != -1)//dfs 회귀 방지 fail safe -1 작동
				{
					x[0] = dest.x0;
					x[1] = dest.x1;
					y[0] = dest.y0;
					y[1] = dest.y1;
				}
				else//fail safe catch일때 1.내꺼 주변 빌딩 가능한지 예측 5에서 2까지 가능한지 만들어 보기-조건:rst.x0==-1인지 매번 확인
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

	for (int i = 0; i < 16; i++) { // 방어 - 4개 - 오른쪽 대각
		for (int j = 3; j < 19; j++) {
			if (showBoard(i, j) == 2 && showBoard(i + 1, j - 1) == 2 && showBoard(i + 2, j - 2) == 2 && showBoard(i + 3, j - 3) == 2) {
				if (isFree(i - 1, j + 1) && isFree(i + 4, j - 4)) { // 양쪽 다 안 막힌 경우
					temp[0] = i - 1;
					temp[1] = j + 1;
					temp[2] = i + 4;
					temp[3] = j - 4;

					D_4_RDG = 1;
					break;
				}
				else if (!isFree(i - 1, j + 1) && isFree(i + 4, j - 4)) { // 아래쪽만 막혀있는 경우
					temp[0] = i + 4;
					temp[1] = j - 4;
					xyPair dest = vbMaker(board);
					if (dest.x0 != -1)//dfs 회귀 방지 fail safe -1 작동
					{
						x[0] = dest.x0;
						x[1] = dest.x1;
						y[0] = dest.y0;
						y[1] = dest.y1;
					}
					else//fail safe catch일때 1.내꺼 주변 빌딩 가능한지 예측 5에서 2까지 가능한지 만들어 보기-조건:rst.x0==-1인지 매번 확인
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
				else if (isFree(i - 1, j + 1) && !isFree(i + 4, j - 4)) { // 위쪽만 막혀있는 경우
					temp[0] = i - 1;
					temp[1] = j + 1;
					xyPair dest = vbMaker(board);
					if (dest.x0 != -1)//dfs 회귀 방지 fail safe -1 작동
					{
						x[0] = dest.x0;
						x[1] = dest.x1;
						y[0] = dest.y0;
						y[1] = dest.y1;
					}
					else//fail safe catch일때 1.내꺼 주변 빌딩 가능한지 예측 5에서 2까지 가능한지 만들어 보기-조건:rst.x0==-1인지 매번 확인
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
				if (dest.x0 != -1)//dfs 회귀 방지 fail safe -1 작동
				{
					x[0] = dest.x0;
					x[1] = dest.x1;
					y[0] = dest.y0;
					y[1] = dest.y1;
				}
				else//fail safe catch일때 1.내꺼 주변 빌딩 가능한지 예측 5에서 2까지 가능한지 만들어 보기-조건:rst.x0==-1인지 매번 확인
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
				if (dest.x0 != -1)//dfs 회귀 방지 fail safe -1 작동
				{
					x[0] = dest.x0;
					x[1] = dest.x1;
					y[0] = dest.y0;
					y[1] = dest.y1;
				}
				else//fail safe catch일때 1.내꺼 주변 빌딩 가능한지 예측 5에서 2까지 가능한지 만들어 보기-조건:rst.x0==-1인지 매번 확인
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
				if (dest.x0 != -1)//dfs 회귀 방지 fail safe -1 작동
				{
					x[0] = dest.x0;
					x[1] = dest.x1;
					y[0] = dest.y0;
					y[1] = dest.y1;
				}
				else//fail safe catch일때 1.내꺼 주변 빌딩 가능한지 예측 5에서 2까지 가능한지 만들어 보기-조건:rst.x0==-1인지 매번 확인
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






	for (int i = 0; i < 15; i++) { // 방어 - 5개 - 가로
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
				else if (isFree(i - 1, j) && !isFree(i + 5, j)) { // 오른쪽만 막혀있는 경우
					temp[0] = i - 1;
					temp[1] = j;
					xyPair dest = vbMaker(board);
					if (dest.x0 != -1)//dfs 회귀 방지 fail safe -1 작동
					{
						x[0] = dest.x0;
						x[1] = dest.x1;
						y[0] = dest.y0;
						y[1] = dest.y1;
					}
					else//fail safe catch일때 1.내꺼 주변 빌딩 가능한지 예측 5에서 2까지 가능한지 만들어 보기-조건:rst.x0==-1인지 매번 확인
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
				else if (!isFree(i - 1, j) && isFree(i + 5, j)) { // 왼쪽만 막혀있는 경우
					temp[0] = i + 5;
					temp[1] = j;
					xyPair dest = vbMaker(board);
					if (dest.x0 != -1)//dfs 회귀 방지 fail safe -1 작동
					{
						x[0] = dest.x0;
						x[1] = dest.x1;
						y[0] = dest.y0;
						y[1] = dest.y1;
					}
					else//fail safe catch일때 1.내꺼 주변 빌딩 가능한지 예측 5에서 2까지 가능한지 만들어 보기-조건:rst.x0==-1인지 매번 확인
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

	for (int i = 0; i < 19; i++) { // 방어 - 5개 - 세로
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
				else if (isFree(i, j - 1) && !isFree(i, j + 5)) { // 위쪽만 막혀있는 경우
					temp[0] = i;
					temp[1] = j - 1;
					xyPair dest = vbMaker(board);
					if (dest.x0 != -1)//dfs 회귀 방지 fail safe -1 작동
					{
						x[0] = dest.x0;
						x[1] = dest.x1;
						y[0] = dest.y0;
						y[1] = dest.y1;
					}
					else//fail safe catch일때 1.내꺼 주변 빌딩 가능한지 예측 5에서 2까지 가능한지 만들어 보기-조건:rst.x0==-1인지 매번 확인
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
				else if (!isFree(i, j - 1) && isFree(i, j + 5)) { // 아래쪽만 막혀있는 경우
					temp[0] = i;
					temp[1] = j + 5;
					xyPair dest = vbMaker(board);
					if (dest.x0 != -1)//dfs 회귀 방지 fail safe -1 작동
					{
						x[0] = dest.x0;
						x[1] = dest.x1;
						y[0] = dest.y0;
						y[1] = dest.y1;
					}
					else//fail safe catch일때 1.내꺼 주변 빌딩 가능한지 예측 5에서 2까지 가능한지 만들어 보기-조건:rst.x0==-1인지 매번 확인
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


	for (int i = 0; i < 15; i++) { // 방어 - 5개 - 왼쪽 대각
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
				else if (!isFree(i - 1, j - 1) && isFree(i + 5, j + 5)) { // 위쪽만 막혀있는 경우
					temp[0] = i + 5;
					temp[1] = j + 5;
					xyPair dest = vbMaker(board);
					if (dest.x0 != -1)//dfs 회귀 방지 fail safe -1 작동
					{
						x[0] = dest.x0;
						x[1] = dest.x1;
						y[0] = dest.y0;
						y[1] = dest.y1;
					}
					else//fail safe catch일때 1.내꺼 주변 빌딩 가능한지 예측 5에서 2까지 가능한지 만들어 보기-조건:rst.x0==-1인지 매번 확인
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
				else if (isFree(i - 1, j - 1) && !isFree(i + 5, j + 5)) { // 아래쪽만 막혀있는 경우
					temp[0] = i - 1;
					temp[1] = j - 1;
					xyPair dest = vbMaker(board);
					if (dest.x0 != -1)//dfs 회귀 방지 fail safe -1 작동
					{
						x[0] = dest.x0;
						x[1] = dest.x1;
						y[0] = dest.y0;
						y[1] = dest.y1;
					}
					else//fail safe catch일때 1.내꺼 주변 빌딩 가능한지 예측 5에서 2까지 가능한지 만들어 보기-조건:rst.x0==-1인지 매번 확인
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

	for (int i = 0; i < 15; i++) { // 방어 - 5개 - 오른쪽 대각
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
				else if (!isFree(i - 1, j + 1) && isFree(i + 5, j - 5)) { // 아래쪽만 막혀있는 경우
					temp[0] = i + 5;
					temp[1] = j - 5;
					xyPair dest = vbMaker(board);
					if (dest.x0 != -1)//dfs 회귀 방지 fail safe -1 작동
					{
						x[0] = dest.x0;
						x[1] = dest.x1;
						y[0] = dest.y0;
						y[1] = dest.y1;
					}
					else//fail safe catch일때 1.내꺼 주변 빌딩 가능한지 예측 5에서 2까지 가능한지 만들어 보기-조건:rst.x0==-1인지 매번 확인
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
				else if (isFree(i - 1, j + 1) && !isFree(i + 5, j - 5)) { // 위쪽만 막혀있는 경우
					temp[0] = i - 1;
					temp[1] = j + 1;
					xyPair dest = vbMaker(board);
					if (dest.x0 != -1)//dfs 회귀 방지 fail safe -1 작동
					{
						x[0] = dest.x0;
						x[1] = dest.x1;
						y[0] = dest.y0;
						y[1] = dest.y1;
					}
					else//fail safe catch일때 1.내꺼 주변 빌딩 가능한지 예측 5에서 2까지 가능한지 만들어 보기-조건:rst.x0==-1인지 매번 확인
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



	// 공격 - 4개 - 가로
	for (int i = 0; i < 16; i++) { // 공격 - 4개 - 가로
		for (int j = 0; j < 19; j++) {
			if ((showBoard(i, j) == 1 && showBoard(i + 1, j) == 1 && showBoard(i + 2, j) == 1 && showBoard(i + 3, j) == 1)) {
				if (isFree(i - 1, j) && isFree(i - 2, j)) {  // 왼쪽 두개가 비어 있을 경우
					temp[0] = i - 1;
					temp[1] = j;
					temp[2] = i - 2;
					temp[3] = j;
					A_4_H = 1;
					break;
				}

				else if (isFree(i + 4, j) && isFree(i + 5, j)) { // 오른쪽 두개가 비어 있을 경우
					temp[0] = i + 4;
					temp[1] = j;
					temp[2] = i + 5;
					temp[3] = j;
					A_4_H = 1;
					break;
				}

				else if (isFree(i - 1, j) && isFree(i + 4, j)) { // 양 옆이 비어 있을 경우
					temp[0] = i - 1;
					temp[1] = j;
					temp[2] = i + 4;
					temp[3] = j;
					A_4_H = 1;
					break;
				}
			}
			else if (showBoard(i, j) == 1 && showBoard(i + 1, j) == 0 && showBoard(i + 2, j) == 1 && showBoard(i + 3, j) == 1 && showBoard(i + 4, j) == 1) { // 중간 비어 있는 경우 1
				    temp[0] = i + 1;
					temp[1] = j;
					if(isFree(i - 1, j)){  // 가운데 두고 왼쪽이 비어 있을 경우
						temp[2] = i - 1;
						temp[3] = j;
						A_4_H = 1;
						break;
					}
					else if(isFree(i + 5, j)) { // 가운데 두고 오른쪽이 비어 있을 경우
						temp[2] = i + 5;
						temp[3] = j;
						A_4_H = 1;
						break;
					}
			}

			else if (showBoard(i, j) == 1 && showBoard(i + 1, j) == 1 && showBoard(i + 2, j) == 0 && showBoard(i + 3, j) == 1 && showBoard(i + 4, j) == 1) { // 중간 비어 있는 경우 2
				temp[0] = i + 2;
				temp[1] = j;
				if (isFree(i - 1, j)) {  // 가운데 두고 왼쪽이 비어 있을 경우
					temp[2] = i - 1;
					temp[3] = j;
					A_4_H = 1;
					break;
				}
				else if (isFree(i + 5, j)) { // 가운데 두고 오른쪽이 비어 있을 경우
					temp[2] = i + 5;
					temp[3] = j;
					A_4_H = 1;
					break;
				}
			}

			else if (showBoard(i, j) == 1 && showBoard(i + 1, j) == 1 && showBoard(i + 2, j) == 1 && showBoard(i + 3, j) == 0 && showBoard(i + 4, j) == 1) { // 중간 비어 있는 경우 2
				temp[0] = i + 3;
				temp[1] = j;
				if (isFree(i - 1, j)) {  // 가운데 두고 왼쪽이 비어 있을 경우
					temp[2] = i - 1;
					temp[3] = j;
					A_4_H = 1;
					break;
				}
				else if (isFree(i + 5, j)) { // 가운데 두고 오른쪽이 비어 있을 경우
					temp[2] = i + 5;
					temp[3] = j;
					A_4_H = 1;
					break;
				}
			}
			else if (showBoard(i, j) == 1 && showBoard(i + 1, j) == 0 && showBoard(i + 2, j) == 0 && showBoard(i + 3, j) == 1 && showBoard(i + 4, j) == 1 && showBoard(i + 5, j) == 1) { // 중간 2칸 비어 있는 경우 2
				temp[0] = i + 1;
				temp[1] = j;
				temp[2] = i + 2;
				temp[3] = j;
				A_4_H = 1;
				break;
			}
			else if (showBoard(i, j) == 1 && showBoard(i + 1, j) == 0 && showBoard(i + 2, j) == 1 && showBoard(i + 3, j) == 0 && showBoard(i + 4, j) == 1 && showBoard(i + 5, j) == 1) { // 중간 2칸 비어 있는 경우 2
				temp[0] = i + 1;
				temp[1] = j;
				temp[2] = i + 3;
				temp[3] = j;
				A_4_H = 1;
				break;
			}
			else if (showBoard(i, j) == 1 && showBoard(i + 1, j) == 0 && showBoard(i + 2, j) == 1 && showBoard(i + 3, j) == 1 && showBoard(i + 4, j) == 0 && showBoard(i + 5, j) == 1) { // 중간 2칸 비어 있는 경우 2
				temp[0] = i + 1;
				temp[1] = j;
				temp[2] = i + 4;
				temp[3] = j;
				A_4_H = 1;
				break;
			}
			else if (showBoard(i, j) == 1 && showBoard(i + 1, j) == 1 && showBoard(i + 2, j) == 0 && showBoard(i + 3, j) == 0 && showBoard(i + 4, j) == 1 && showBoard(i + 5, j) == 1) { // 중간 2칸 비어 있는 경우 2
				temp[0] = i + 2;
				temp[1] = j;
				temp[2] = i + 3;
				temp[3] = j;
				A_4_H = 1;
				break;
			}
			else if (showBoard(i, j) == 1 && showBoard(i + 1, j) == 1 && showBoard(i + 2, j) == 0 && showBoard(i + 3, j) == 1 && showBoard(i + 4, j) == 0 && showBoard(i + 5, j) == 1) { // 중간 2칸 비어 있는 경우 2
				temp[0] = i + 2;
				temp[1] = j;
				temp[2] = i + 4;
				temp[3] = j;
				A_4_H = 1;
				break;
			}

			else if (showBoard(i, j) == 1 && showBoard(i + 1, j) == 1 && showBoard(i + 2, j) == 1 && showBoard(i + 3, j) == 0 && showBoard(i + 4, j) == 0 && showBoard(i + 5, j) == 1) { // 중간 2칸 비어 있는 경우 2
				temp[0] = i + 3;
				temp[1] = j;
				temp[2] = i + 4;
				temp[3] = j;
				A_4_H = 1;
				break;
			}

		}
	}
	// 공격 - 4개 - 세로
	for (int i = 0; i < 19; i++) { // 공격 - 4개 - 세로
		for (int j = 0; j < 16; j++) {
			if ((showBoard(i, j) == 1 && showBoard(i , j + 1) == 1 && showBoard(i , j + 2) == 1 && showBoard(i , j + 3) == 1)) {
				if (isFree(i, j - 1) && isFree(i, j - 2)) {  // 위쪽 두개가 비어 있을 경우
					temp[0] = i;
					temp[1] = j - 1;
					temp[2] = i;
					temp[3] = j - 2;
					A_4_V = 1;
					break;
				}

				else if (isFree(i , j + 4) && isFree(i + 5, j + 5)) { // 오른쪽 두개가 비어 있을 경우
					temp[0] = i;
					temp[1] = j + 4;
					temp[2] = i;
					temp[3] = j + 5;
					A_4_V = 1;
					break;
				}

				else if (isFree(i , j - 1) && isFree(i , j + 4)) { // 양 옆이 비어 있을 경우
					temp[0] = i;
					temp[1] = j - 1;
					temp[2] = i;
					temp[3] = j + 4;
					A_4_V = 1;
					break;
				}
			}
			else if (showBoard(i, j) == 1 && showBoard(i, j + 1) == 0 && showBoard(i, j + 2) == 1 && showBoard(i, j + 3) == 1 && showBoard(i, j + 4) == 1) { // 중간 비어 있는 경우 1
				temp[0] = i;
				temp[1] = j + 1;
				if (isFree(i, j - 1)) {  // 가운데 두고 위쪽이 비어 있을 경우
					temp[2] = i;
					temp[3] = j - 1;
					A_4_V = 1;
					break;
				}
				else if (isFree(i, j + 5)) { // 가운데 두고 아래쪽이 비어 있을 경우
					temp[2] = i;
					temp[3] = j + 5;
					A_4_V = 1;
					break;
				}
			}

			else if (showBoard(i, j) == 1 && showBoard(i, j + 1) == 1 && showBoard(i, j + 2) == 0 && showBoard(i, j + 3) == 1 && showBoard(i, j + 4) == 1) { // 중간 비어 있는 경우 2
				temp[0] = i;
				temp[1] = j + 2;
				if (isFree(i, j - 1)) {  // 가운데 두고 위쪽이 비어 있을 경우
					temp[2] = i;
					temp[3] = j - 1;
					A_4_V = 1;
					break;
				}
				else if (isFree(i, j + 5)) { // 가운데 두고 아래쪽이 비어 있을 경우
					temp[2] = i;
					temp[3] = j + 5;
					A_4_V = 1;
					break;
				}
			}

			else if (showBoard(i, j) == 1 && showBoard(i, j + 1) == 1 && showBoard(i, j + 2) == 1 && showBoard(i, j + 3) == 0 && showBoard(i, j + 4) == 1) { // 중간 비어 있는 경우 3
				temp[0] = i;
				temp[1] = j + 3;
				if (isFree(i, j - 1)) {  // 가운데 두고 위쪽이 비어 있을 경우
					temp[2] = i;
					temp[3] = j - 1;
					A_4_V = 1;
					break;
				}
				else if (isFree(i, j + 5)) { // 가운데 두고 아래쪽이 비어 있을 경우
					temp[2] = i;
					temp[3] = j + 5;
					A_4_V = 1;
					break;
				}
			}
		
			
			else if (showBoard(i, j) == 1 && showBoard(i, j + 1) == 0 && showBoard(i, j + 2) == 0 && showBoard(i, j + 3) == 1 && showBoard(i, j + 4) == 1 && showBoard(i, j + 5) == 1) { // 중간 2칸 비어 있는 경우 2
				temp[0] = i;
				temp[1] = j + 1;
				temp[2] = i;
				temp[3] = j + 2;
				A_4_V = 1;
				break;
			}
			else if (showBoard(i, j) == 1 && showBoard(i, j + 1) == 0 && showBoard(i, j + 2) == 1 && showBoard(i, j + 3) == 0 && showBoard(i, j + 4) == 1 && showBoard(i, j + 5) == 1) { // 중간 2칸 비어 있는 경우 3
				temp[0] = i;
				temp[1] = j + 1;
				temp[2] = i;
				temp[3] = j + 3;
				A_4_V = 1;
				break;
			}
			else if (showBoard(i, j) == 1 && showBoard(i, j + 1) == 0 && showBoard(i, j + 2) == 1 && showBoard(i, j + 3) == 1 && showBoard(i, j + 4) == 0 && showBoard(i, j + 5) == 1) { // 중간 2칸 비어 있는 경우 4
				temp[0] = i;
				temp[1] = j + 1;
				temp[2] = i;
				temp[3] = j + 4;
				A_4_V = 1;
				break;
			}
			else if (showBoard(i, j) == 1 && showBoard(i, j + 1) == 1 && showBoard(i, j + 2) == 0 && showBoard(i, j + 3) == 0 && showBoard(i, j + 4) == 1 && showBoard(i, j + 5) == 1) { // 중간 비어 있는 경우 5
				temp[0] = i;
				temp[1] = j + 2;
				temp[2] = i;
				temp[3] = j + 3;
				A_4_V = 1;
				break;
			}
			else if (showBoard(i, j) == 1 && showBoard(i, j + 1) == 1 && showBoard(i, j + 2) == 0 && showBoard(i, j + 3) == 1 && showBoard(i, j + 4) == 0 && showBoard(i, j + 5) == 1) { // 중간 비어 있는 경우 6
				temp[0] = i;
				temp[1] = j + 2;
				temp[2] = i;
				temp[3] = j + 4;
				A_4_V = 1;
				break;
			}

			else if (showBoard(i, j) == 1 && showBoard(i, j + 1) == 1 && showBoard(i, j + 2) == 1 && showBoard(i, j + 3) == 0 && showBoard(i, j + 4) == 0 && showBoard(i, j + 5) == 1) { // 중간 2칸 비어 있는 경우 1
				temp[0] = i;
				temp[1] = j + 3;
				temp[2] = i;
				temp[3] = j + 4;
				A_4_V = 1;
				break;
			}
		}
	}
	// 공격 - 4개 - 왼쪽 대각선
	for (int i = 0; i < 16; i++) { // 공격 - 4개 - 가로
		for (int j = 0; j < 16; j++) {
			if ((showBoard(i, j) == 1 && showBoard(i + 1, j + 1) == 1 && showBoard(i + 2, j + 2) == 1 && showBoard(i + 3, j + 3) == 1)) {
				if (isFree(i - 1, j - 1) && isFree(i - 2, j - 2)) {  // 왼쪽 두개가 비어 있을 경우
					temp[0] = i - 1;
					temp[1] = j - 1;
					temp[2] = i - 2;
					temp[3] = j - 2;
					A_4_LDG = 1;
					break;
				}

				else if (isFree(i + 4, j + 4) && isFree(i + 5, j + 5)) { // 오른쪽 두개가 비어 있을 경우
					temp[0] = i + 4;
					temp[1] = j + 4;
					temp[2] = i + 5;
					temp[3] = j + 5;
					A_4_LDG = 1;
					break;
				}

				else if (isFree(i - 1, j - 1) && isFree(i + 4, j + 4) == 1) { // 양 옆이 비어 있을 경우
					temp[0] = i - 1;
					temp[1] = j - 1;
					temp[2] = i + 4;
					temp[3] = j + 4;
					A_4_LDG = 1;
					break;
				}
			}
			else if ((showBoard(i, j) == 1 && showBoard(i + 1, j + 1) == 0 && showBoard(i + 2, j + 2) == 1 && showBoard(i + 3, j + 3) == 1) && showBoard(i + 4, j + 4) == 1) { // 중간 비어 있는 경우 1
				temp[0] = i + 1;
				temp[1] = j + 1;
				if (isFree(i - 1, j - 1)) {  // 가운데 두고 왼쪽이 비어 있을 경우
					temp[2] = i - 1;
					temp[3] = j - 1;
					A_4_LDG = 1;
					break;
				}
				else if (isFree(i + 5, j + 5)) { // 가운데 두고 오른쪽이 비어 있을 경우
					temp[2] = i + 5;
					temp[3] = j + 5;
					A_4_LDG = 1;
					break;
				}
			}

			else if (showBoard(i, j) == 1 && showBoard(i + 1, j + 1) == 1 && showBoard(i + 2, j + 2) == 0 && showBoard(i + 3, j + 3) == 1 && showBoard(i + 4, j + 4) == 1) { // 중간 비어 있는 경우 1
				temp[0] = i + 2;
				temp[1] = j + 2;
				if (isFree(i - 1, j - 1)) {  // 가운데 두고 왼쪽이 비어 있을 경우
					temp[2] = i - 1;
					temp[3] = j - 1;
					A_4_LDG = 1;
					break;
				}
				else if (isFree(i + 5, j + 5)) { // 가운데 두고 오른쪽이 비어 있을 경우
					temp[2] = i + 5;
					temp[3] = j + 5;
					A_4_LDG = 1;
					break;
				}
			}

			else if (showBoard(i, j) == 1 && showBoard(i + 1, j + 1) == 1 && showBoard(i + 2, j + 2) == 1 && showBoard(i + 3, j + 3) == 0 && showBoard(i + 4, j + 4) == 1) { // 중간 비어 있는 경우 1
				temp[0] = i + 3;
				temp[1] = j + 3;
				if (isFree(i - 1, j - 1)) {  // 가운데 두고 왼쪽이 비어 있을 경우
					temp[2] = i - 1;
					temp[3] = j - 1;
					A_4_LDG = 1;
					break;
				}
				else if (isFree(i + 5, j + 5)) { // 가운데 두고 오른쪽이 비어 있을 경우
					temp[2] = i + 5;
					temp[3] = j + 5;
					A_4_LDG = 1;
					break;
				}
			}
			else if (showBoard(i, j) == 1 && showBoard(i + 1, j + 1) == 0 && showBoard(i + 2, j + 2) == 0 && showBoard(i + 3, j + 3) == 1 && showBoard(i + 4, j + 4) == 1 && showBoard(i + 5, j + 5) == 1) { // 중간 2칸 비어 있는 경우 2
				temp[0] = i + 1;
				temp[1] = j + 1;
				temp[2] = i + 2;
				temp[3] = j + 2;
				A_4_LDG = 1;
				break;
			}
			else if (showBoard(i, j) == 1 && showBoard(i + 1, j + 1) == 0 && showBoard(i + 2, j + 2) == 1 && showBoard(i + 3, j + 3) == 0 && showBoard(i + 4, j + 4) == 1 && showBoard(i + 5, j + 5) == 1) { // 중간 2칸 비어 있는 경우 2
				temp[0] = i + 1;
				temp[1] = j + 1;
				temp[2] = i + 3;
				temp[3] = j + 3;
				A_4_LDG = 1;
				break;
			}
			else if (showBoard(i, j) == 1 && showBoard(i + 1, j + 1) == 0 && showBoard(i + 2, j + 2) == 1 && showBoard(i + 3, j + 3) == 1 && showBoard(i + 4, j + 4) == 0 && showBoard(i + 5, j + 5) == 1) { // 중간 2칸 비어 있는 경우 2
				temp[0] = i + 1;
				temp[1] = j + 1;
				temp[2] = i + 4;
				temp[3] = j + 4;
				A_4_LDG = 1;
				break;
			}
			else if (showBoard(i, j) == 1 && showBoard(i + 1, j + 1) == 1 && showBoard(i + 2, j + 2) == 0 && showBoard(i + 3, j + 3) == 0 && showBoard(i + 4, j + 4) == 1 && showBoard(i + 5, j + 5) == 1) { // 중간 2칸 비어 있는 경우 2
				temp[0] = i + 2;
				temp[1] = j + 2;
				temp[2] = i + 3;
				temp[3] = j + 3;
				A_4_LDG = 1;
				break;
			}
			else if (showBoard(i, j) == 1 && showBoard(i + 1, j + 1) == 1 && showBoard(i + 2, j + 2) == 0 && showBoard(i + 3, j + 3) == 1 && showBoard(i + 4, j + 4) == 0 && showBoard(i + 5, j + 5) == 1) { // 중간 2칸 비어 있는 경우 2
				temp[0] = i + 2;
				temp[1] = j + 2;
				temp[2] = i + 4;
				temp[3] = j + 4;
				A_4_LDG = 1;
				break;
			}

			else if (showBoard(i, j) == 1 && showBoard(i + 1, j + 1) == 1 && showBoard(i + 2, j + 2) == 1 && showBoard(i + 3, j + 3) == 0 && showBoard(i + 4, j + 4) == 0 && showBoard(i + 5, j + 5) == 1) { // 중간 2칸 비어 있는 경우 2
				temp[0] = i + 3;
				temp[1] = j + 3;
				temp[2] = i + 4;
				temp[3] = j + 4;
				A_4_LDG = 1;
				break;
			}

		}
	}

	// 공격 - 4개 - 오른쪽 대각선

	for (int i = 0; i < 16; i++) { // 공격 - 4개 - 가로
		for (int j = 3; j < 19; j++) {
			if ((showBoard(i, j) == 1 && showBoard(i + 1, j - 1) == 1 && showBoard(i + 2, j - 2) == 1 && showBoard(i + 3, j - 3) == 1)) {
				if (isFree(i - 1, j + 1) && isFree(i - 2, j + 2)) {  // 왼쪽 두개가 비어 있을 경우
					temp[0] = i - 1;
					temp[1] = j + 1;
					temp[2] = i - 2;
					temp[3] = j + 2;
					A_4_RDG = 1;
					break;
				}

				else if (isFree(i + 4, j - 4) && isFree(i + 5, j - 5)) { // 오른쪽 두개가 비어 있을 경우
					temp[0] = i + 4;
					temp[1] = j - 4;
					temp[2] = i + 5;
					temp[3] = j - 5;
					A_4_RDG = 1;
					break;
				}

				else if (isFree(i - 1, j + 1) && isFree(i + 4, j - 4) == 1) { // 양 옆이 비어 있을 경우
					temp[0] = i - 1;
					temp[1] = j + 1;
					temp[2] = i + 4;
					temp[3] = j - 4;
					A_4_RDG = 1;
					break;
				}
			}
			else if (showBoard(i, j) == 1 && showBoard(i + 1, j - 1) == 0 && showBoard(i + 2, j - 2) == 1 && showBoard(i + 3, j - 3) == 1 && showBoard(i + 4, j - 4) == 1) { // 중간 비어 있는 경우 1
				temp[0] = i + 1;
				temp[1] = j - 1;
				if (isFree(i - 1, j + 1)) {  // 가운데 두고 왼쪽이 비어 있을 경우
					temp[2] = i - 1;
					temp[3] = j + 1;
					A_4_RDG = 1;
					break;
				}
				else if (isFree(i + 5, j - 5)) { // 가운데 두고 오른쪽이 비어 있을 경우
					temp[2] = i + 5;
					temp[3] = j - 5;
					A_4_RDG = 1;
					break;
				}
			}

			else if (showBoard(i, j) == 1 && showBoard(i + 1, j - 1) == 1 && showBoard(i + 2, j - 2) == 0 && showBoard(i + 3, j - 3) == 1 && showBoard(i + 4, j - 4) == 1) { // 중간 비어 있는 경우 1
				temp[0] = i + 2;
				temp[1] = j - 2;
				if (isFree(i - 1, j + 1)) {  // 가운데 두고 왼쪽이 비어 있을 경우
					temp[2] = i - 1;
					temp[3] = j + 1;
					A_4_RDG = 1;
					break;
				}
				else if (isFree(i + 5, j - 5)) { // 가운데 두고 오른쪽이 비어 있을 경우
					temp[2] = i + 5;
					temp[3] = j - 5;
					A_4_RDG = 1;
					break;
				}
			}

			else if (showBoard(i, j) == 1 && showBoard(i + 1, j - 1) == 1 && showBoard(i + 2, j - 2) == 1 && showBoard(i + 3, j - 3) == 0 && showBoard(i + 4, j - 4) == 1) { // 중간 비어 있는 경우 1
				temp[0] = i + 3;
				temp[1] = j - 3;
				if (isFree(i - 1, j + 1)) {  // 가운데 두고 왼쪽이 비어 있을 경우
					temp[2] = i - 1;
					temp[3] = j + 1;
					A_4_RDG = 1;
					break;
				}
				else if (isFree(i + 5, j - 5)) { // 가운데 두고 오른쪽이 비어 있을 경우
					temp[2] = i + 5;
					temp[3] = j - 5;
					A_4_RDG = 1;
					break;
				}
			}
			else if (showBoard(i, j) == 1 && showBoard(i + 1, j - 1) == 0 && showBoard(i + 2, j - 2) == 0 && showBoard(i + 3, j - 3) == 1 && showBoard(i + 4, j - 4) == 1 && showBoard(i + 5, j - 5) == 1) { // 중간 2칸 비어 있는 경우 2
				temp[0] = i + 1;
				temp[1] = j - 1;
				temp[2] = i + 2;
				temp[3] = j - 2;
				A_4_RDG = 1;
				break;
			}
			else if (showBoard(i, j) == 1 && showBoard(i + 1, j - 1) == 0 && showBoard(i + 2, j - 2) == 1 && showBoard(i + 3, j - 3) == 0 && showBoard(i + 4, j - 4) == 1 && showBoard(i + 5, j - 5) == 1) { // 중간 2칸 비어 있는 경우 2
				temp[0] = i + 1;
				temp[1] = j - 1;
				temp[2] = i + 3;
				temp[3] = j - 3;
				A_4_RDG = 1;
				break;
			}
			else if (showBoard(i, j) == 1 && showBoard(i + 1, j - 1) == 0 && showBoard(i + 2, j - 2) == 1 && showBoard(i + 3, j - 3) == 1 && showBoard(i + 4, j - 4) == 0 && showBoard(i + 5, j - 5) == 1) { // 중간 2칸 비어 있는 경우 2
				temp[0] = i + 1;
				temp[1] = j - 1;
				temp[2] = i + 4;
				temp[3] = j - 4;
				A_4_RDG = 1;
				break;
			}
			else if (showBoard(i, j) == 1 && showBoard(i + 1, j - 1) == 1 && showBoard(i + 2, j - 2) == 0 && showBoard(i + 3, j - 3) == 0 && showBoard(i + 4, j - 4) == 1 && showBoard(i + 5, j - 5) == 1) { // 중간 2칸 비어 있는 경우 2
				temp[0] = i + 2;
				temp[1] = j - 2;
				temp[2] = i + 3;
				temp[3] = j - 3;
				A_4_RDG = 1;
				break;
			}
			else if (showBoard(i, j) == 1 && showBoard(i + 1, j - 1) == 1 && showBoard(i + 2, j - 2) == 0 && showBoard(i + 3, j - 3) == 1 && showBoard(i + 4, j - 4) == 0 && showBoard(i + 5, j - 5) == 1) { // 중간 2칸 비어 있는 경우 2
				temp[0] = i + 2;
				temp[1] = j - 2;
				temp[2] = i + 4;
				temp[3] = j - 4;
				A_4_RDG = 1;
				break;
			}

			else if (showBoard(i, j) == 1 && showBoard(i + 1, j - 1) == 1 && showBoard(i + 2, j - 2) == 1 && showBoard(i + 3, j - 3) == 0 && showBoard(i + 4, j - 4) == 0 && showBoard(i + 5, j - 5) == 1) { // 중간 2칸 비어 있는 경우 2
				temp[0] = i + 3;
				temp[1] = j - 3;
				temp[2] = i + 4;
				temp[3] = j - 4;
				A_4_RDG = 1;
				break;
			}
		}
	}


	// 판단 변수로 체크
	if (D_4_H == 1) { // 방어 4개 가로
		x[0] = temp[0];
		y[0] = temp[1];
		x[1] = temp[2];
		y[1] = temp[3];
	}

	else if (D_4_V == 1) { // 방어 4개 세로
		x[0] = temp[0];
		y[0] = temp[1];
		x[1] = temp[2];
		y[1] = temp[3];
	}

	else if (D_4_LDG == 1) { // 방어 4개 왼쪽 대각 
		x[0] = temp[0];
		y[0] = temp[1];
		x[1] = temp[2];
		y[1] = temp[3];
	}

	else if (D_4_RDG == 1) { // 방어 4개 오른쪽 대각 
		x[0] = temp[0];
		y[0] = temp[1];
		x[1] = temp[2];
		y[1] = temp[3];
	}

	else if (D_5_H == 1) { // 방어 5개 가로 
		x[0] = temp[0];
		y[0] = temp[1];
		x[1] = temp[2];
		y[1] = temp[3];
	}

	else if (D_5_V == 1) { // 방어 5개 세로
		x[0] = temp[0];
		y[0] = temp[1];
		x[1] = temp[2];
		y[1] = temp[3];
	}

	else if (D_5_LDG == 1) { // 방어 5개 왼쪽 대각
		x[0] = temp[0];
		y[0] = temp[1];
		x[1] = temp[2];
		y[1] = temp[3];
	}

	else if (D_5_RDG == 1) { // 방어 5개 오른쪽 대각
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
		if (cnt == 1 && gcnt == 1)//흑으로 결정나서 선공시 착수 알고리즘
		{
			xy tmp = blackFirst();
			x[0] = tmp.x;
			y[0] = tmp.y;
		}
		else if (cnt == 2 && gcnt == 1)//백으로 결정나서 후공시 처음 두개 착수 알고리즘
		{

			xy tmp = singleChecker(2);//제일 먼저 흑돌의 위치를 찾아온다
			xyPair dest = twoBuilder(tmp);//흑돌 기준 주변 흰색 두개 빌딩 방법 검색

			x[0] = dest.x0;
			x[1] = dest.x1;
			y[0] = dest.y0;
			y[1] = dest.y1;

		}
		else if (isBlackT2(board))//흑의 두번째 공격 알고리즘. 자신의 위치를 찾아서 dfs 활용한다.
		{
			xy tmp = singleChecker(1);//내 흑돌 하나 찾아온다
			xyPair dest = dfs(tmp, 5, true);//흑돌 기준 주변 두개 빌딩 방법 검색. 하나 놨으니까 나머지 다섯개 이어서 놀 수있는지 8방향별로 탐색한다.

			x[0] = dest.x0;
			x[1] = dest.x1;
			y[0] = dest.y0;
			y[1] = dest.y1;
		}
		else if (cnt == 2 && gcnt > 1)//백의 첫번째 이후 공격 및 흑의 두번째 이후 공격은 1. 내돌들 찾아서 8방향 패턴 확인후 그방향 진로가 막히지 않았으면 이어서 붙인다. 2.내 모든 돌들의 진로가 막혔다면 그 주변에서 dfs 활용 한다.
		{
			xyPair dest = vbMaker(board);
			if (dest.x0 != -1)//dfs 회귀 방지 fail safe -1 작동
			{
				x[0] = dest.x0;
				x[1] = dest.x1;
				y[0] = dest.y0;
				y[1] = dest.y1;
			}
			else//fail safe catch일때 1.내꺼 주변 빌딩 가능한지 예측 5에서 2까지 가능한지 만들어 보기-조건:rst.x0==-1인지 매번 확인
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

