#ifndef MATHTOOL_H
#define MATHTOOL_H

#include<vector>

using namespace std;

int findMin(vector<int>& in, int n);

int findMax(vector<int>& in, int n);

int findPosition(vector<string>& in, string str);

int findPositionPairs(vector<pair<string, string>>& in,
	pair<string, string> str);
#endif