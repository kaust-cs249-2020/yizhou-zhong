#include"mathtool.h"

int findMin(vector<int>& in, int n)
{
	int i;
	int minvalue = in[0];
	for (i = 1; i<n; i++)
		if (minvalue>in[i]) minvalue = in[i];
	return minvalue;
}

int findMax(vector<int>& in, int n)
{
	int i;
	int maxvalue = in[0];
	for (i = 1; i < n; i++)
		if (maxvalue < in[i]) maxvalue = in[i];
	return maxvalue;
}

int findMax(vector<int>& in, int n, int& idx)
{
	int i;
	int maxvalue = in[0];
	idx = 0;
	for (i = 1; i < n; i++)
		if (maxvalue <= in[i])
		{
			maxvalue = in[i];
			idx = i;
		}
	return maxvalue;
}

int findPosition(vector<string>& in, string str)
{
	int idx = -1;
	for (int i = 0; i < in.size(); i++)
	{
		if (
			strcmp(
			in[i].c_str(), str.c_str()
			)==0
			)
		{
			idx = i;
			break;
		}
	}
	return idx;
}

int findPositionPairs(vector<pair<string, string>>& in, 
	pair<string, string> str)
{
	int idx = -1;
	for (int i = 0; i < in.size(); i++)
	{
		if (
			strcmp(in[i].first.c_str(), str.first.c_str()) == 0
			&& strcmp(in[i].second.c_str(), str.second.c_str()) == 0
			)
		{
			idx = i;
			break;
		}
	}
	return idx;
}

int findMaxOf2(int a, int b)
{
	return a >= b ? a : b;
}

int findMaxOfMat(vector<vector<int>>& in, int& idx1, int& idx2)
{
	int maxScore = in[0][0];
	idx1 = 0;
	idx2 = 0;

	for (int i = 0; i < in.size();i++)
	{
		for (int j = 0; j < in[0].size();j++)
		{
			if (in[i][j] > maxScore)
			{
				maxScore = in[i][j];
				idx1 = i;
				idx2 = j;
			}
		}
	}
	return maxScore;
}

int findMaxOfCol(vector<vector<int>>& in, int col, int& row)
{
	int maxScore = in[0][col];
	row = 0;
	for (int i = 1; i < in.size();i++)
	{
		if (in[i][col]>=maxScore)
		{
			maxScore = in[i][col];
			row = i;
		}
	}
	return maxScore;
}

bool Belong2PepValues(int pep, vector<int> pepValues)
{
	for (int i = 0; i < pepValues.size(); i++)
	{
		if (pepValues[i] == pep)
		{
			return true;
		}
	}
	return false;
}

bool Belong2PepValues(int pep, vector<int> pepValues, int& idx)
{
	for (int i = 0; i < pepValues.size(); i++)
	{
		if (pepValues[i] == pep)
		{
			idx = i;
			return true;
		}
	}
	return false;
}