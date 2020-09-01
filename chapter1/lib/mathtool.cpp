#include"mathtool.h"

float findMin(vector<int>& in, int n)
{
	int i;
	int minvalue = in[0];
	for (i = 1; i<n; i++)
		if (minvalue>in[i]) minvalue = in[i];
	return minvalue;
}

float findMax(vector<int>& in, int n)
{
	int i;
	int maxvalue = in[0];
	for (i = 1; i < n; i++)
		if (maxvalue < in[i]) maxvalue = in[i];
	return maxvalue;
}