#include "stdafx.h"
#include "MYmine.h"
#include<Windows.h>
#include<time.h>
#include"MineMap.h"


CMinemap::CMinemap():mx(30)
{
	 my = 20;
	 nMine = 10;
	 rMine = 0;
	 ctime = 0;
	 iswin = FALSE;
	 isfail = FALSE;
};

CMinemap::~CMinemap()
{};

void CMinemap::Create()//初始化
{
	Map = new block *[mx];
	int i, j;
	for (i = 0; i < mx; i++)
		Map[i] = new block[my];
	for (i = 0; i < mx; i++)
		for (j = 0; j < my; j++)
			Map[i][j] = { 0,FALSE ,back};//初始化
	srand(time(NULL));
	{//布雷2.0
		int * list;
		list = new int[mx*my];
		for (i = 0; i < mx*my; i++)
		{
			list[i] = i;
		}
		for (i = 0; i < nMine; i++)
		{
			int a = rand() % (mx*my - i);
			int b;
			b = list[a];
			int c, d;
			d = b / mx;
			c = b % mx;
			Map[c][d].isMine = TRUE;
			list[a] = list[mx*my - 1 - i];
		}

	}



	/*for (i = 0; i < nMine; i++)//布雷
	{
		int a = rand() % mx;
		int b = rand() % my;
		if (Map[a][b].isMine == TRUE)
			i--;
		else
		{
			Map[a][b].isMine = TRUE;
		}

	}*/

	for (i=0;i<mx;i++)
		for (j = 0; j < my; j++)//计雷数(雷格自记)
		{
			if (Map[i][j].isMine == TRUE)
			{
				for (int m = -1; m < 2; m++)
					for (int n = -1; n < 2; n++)
					{
						if ((i + m >= 0) && (j + n >= 0) && (i + m < mx) &&(j + n < my))
							Map[i + m][j + n].Num++;
					}
			}
		}

};

void CMinemap::LClick(int x,int y,CRect *rc)
{
	if (x >= mx || y >= my || x < 0 || y < 0)
		return;
	if (16 * x < rc->left)
		rc->left = rc->left - 16;
	if (16 * y + 32 < rc->top)
		rc->top = rc->top - 16;
	if (16 * x + 16 > rc->right)
		rc->right = rc->right + 16;
	if (16 * y + 48 > rc->bottom)
		rc->bottom = rc->bottom + 16;//把包括当前格在内的区域扩入rc
	
	
	if (Map[x][y].state ==back)
		if (Map[x][y].isMine == TRUE)
		{
			isfail = TRUE;
			Map[x][y].state = boom;
			rc->left = 0;
			rc->top = 0;
			rc->right = 16 * mx + 16;
			rc->bottom = 16 * my + 48;
		}
		else 
		{
			Map[x][y].state = lclicked;
			if (Map[x][y].Num == 0)//自动点开周围
			{
				LClick(x - 1, y - 1, rc);
				LClick(x - 1, y, rc);
				LClick(x - 1, y + 1, rc);
				LClick(x, y - 1, rc);
				LClick(x, y + 1, rc);
				LClick(x + 1, y - 1, rc);
				LClick(x + 1, y, rc);
				LClick(x + 1, y + 1, rc);
			}
		}
	




};

void CMinemap::RClick(int x, int y)
{

		if (iswin == FALSE)
		{
			switch (Map[x][y].state)
			{
			case back:
				if (nflag != nMine)
				{
					Map[x][y].state = flaged;
					nflag++;
					if (Map[x][y].isMine == TRUE)
						rMine++;
				}
				break;
			case flaged:
				Map[x][y].state = question;
				nflag--;
				if (Map[x][y].isMine == TRUE)
					rMine--;
				break;
			case question:
				Map[x][y].state = back;
				break;
			default:
				break;
			}

			if (rMine == nMine)
				iswin = TRUE;
		}

	
	
}

void CMinemap::Set()
{
	mx = 30;
	my = 20;
	nMine = 50;
	rMine = 0;
	ctime = 0;
	nflag = 0;
	iswin = FALSE;
	isfail = FALSE;
	{
		int i, j;
		for (i = 0; i < mx; i++)
			for (j = 0; j < my; j++)
				Map[i][j] = { 0,FALSE ,back };//初始化
		srand(time(NULL));
		{//布雷2.0
			int * list;
			list = new int[mx*my];
			for (i = 0; i < mx*my; i++)
			{
				list[i] = i;
			}
			for (i = 0; i < nMine; i++)
			{
				int a = rand() % (mx*my - i);
				int b;
				b = list[a];
				int c, d;
				d = b / mx;
				c = b % mx;
				Map[c][d].isMine = TRUE;
				list[a] = list[mx*my - 1 - i];
			}

		}

		for (i = 0; i < mx; i++)
			for (j = 0; j < my; j++)//计雷数(雷格自记)
			{
				if (Map[i][j].isMine == TRUE)
				{
					for (int m = -1; m < 2; m++)
						for (int n = -1; n < 2; n++)
						{
							if ((i + m >= 0) && (j + n >= 0) && (i + m < mx) && (j + n < my))
								Map[i + m][j + n].Num++;
						}
				}
			}
	}
}