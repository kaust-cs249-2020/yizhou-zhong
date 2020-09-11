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