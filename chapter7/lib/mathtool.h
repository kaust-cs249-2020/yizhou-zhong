#ifndef MATHTOOL_H
#define MATHTOOL_H

#include<vector>

using namespace std;

int findMin(vector<int>& in, int n);

int findMax(vector<int>& in, int n);

int findMax(vector<int>& in, int n, int& idx);

int findPosition(vector<string>& in, string str);

int findPositionPairs(vector<pair<string, string>>& in,
	pair<string, string> str);

int findMaxOf2(int a, int b);

int findMaxOfMat(vector<vector<int>>& in, int& idx1, int& idx2);

int findMaxOfCol(vector<vector<int>>& in, int col, int& row);
#endif