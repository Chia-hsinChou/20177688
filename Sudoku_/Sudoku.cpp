// Sudoku.cpp: 定义控制台应用程序的入口点。

//
#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <string>
#pragma warning(disable:4996)

using namespace std;
int num, gsize, glength, gwidth, single_bor[100][100], out_bor[10][100][100];

bool check(int x, int y, int i) //判断在(x,y)处数字i在同一行、列、宫是否唯一
{
	int l, w;

	for (l = 0; l < gsize; l++) //按列检查同一行是否有重复
	{
		if (l != y && single_bor[x][l] == i)
			return false;
	}

	for (w = 0; w < gsize; w++)//按行检查同一列是否有重复
	{
		if (w != x && single_bor[w][y] == i)
			return false;
	}

	if (glength != gsize) //如果有宫
	{
		for (l = (x / glength) * glength; l < (x / glength) * glength + glength; l++)
		{
			for (w = (y / gwidth) * gwidth; w < (y / gwidth) * gwidth + gwidth; w++)
			{
				if (single_bor[l][w] == i)
				{
					if (l == x && w == y)
						continue;
					else
						return false;
				}
			}
		}
	}
	return true;
}

bool DSF(int depth) 
{
	single_bor[0][0] = 1;
	int i, x, y;
	if (depth >= gsize * gsize)
		return true;
	x = depth / gsize, y = depth % gsize;
	if (single_bor[x][y] != 0)
		return DSF(depth + 1);
	else
	{
		for (i = 1; i <= gsize; i++)
		{
			if (check(x, y, i))
			{
				single_bor[x][y] = i;
				
				if (DSF(depth + 1))
					return true;
			}
			single_bor[x][y] = 0;
		}
	}
	return false;
}

int main(int argc, char* argv[])
{
	int  i, j, k;
	int InputFile = 0, OutputFile = 0;
	string m = "-m", in = "-i", out = "-o", n = "-n";

	if (argc > 0 && argv != NULL)
	{
		for (i = 0; i < argc; i++)
		{
			if (argv[i] == in)
				InputFile = i + 1;
			if (argv[i] == out)
				OutputFile = i + 1;
			if (argv[i] == m)
				gsize = atoi(argv[i + 1]);
			if (argv[i] == n)
				num = atoi(argv[i + 1]);
		}
	}

	else
	{
		cout << "未输入参数" << endl;
	}
	if (gsize % 3 == 0)
		glength = gsize / 3, gwidth = gsize / glength;
	else if (gsize % 2 == 0)
		glength = gsize / 2, gwidth = gsize / glength;
	else
		glength = gsize, gwidth = gsize;

	FILE* afile;
	afile = fopen(argv[InputFile], "r");
	if (afile == NULL)
	{
		cout << "cannot find input file" << endl;
		return 0;
	}
	for (i = 0; i < num; i++)
	{
		for (j = 0; j < gsize; j++)
			for (k = 0; k < gsize; k++)
				fscanf_s(afile, "%d", &single_bor[j][k]);
		DSF(0);
		for (j = 0; j < gsize; j++)
			for (k = 0; k < gsize; k++)
				out_bor[i][j][k] = single_bor[j][k];
	}

	fclose(afile);
	afile = fopen(argv[OutputFile], "w");

	for (i = 0; i < num; i++)
	{
		for (j = 0; j < gsize; j++)
		{
			for (k = 0; k < gsize; k++)
			{
				fprintf(afile, "%d", out_bor[i][j][k]);
				if (k != gsize - 1)
					fprintf(afile, " ");
			}
			if (j != gsize - 1)
				fprintf(afile, "\n");
		}

		if (i != num - 1)
			fprintf(afile, "\n\n");
	}
	fclose(afile);
	return 0;

}