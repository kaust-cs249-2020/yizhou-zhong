#ifndef MATHTOOL_H
#define MATHTOOL_H

#include<vector>

using namespace std;

class NODE
{
public:
	NODE(string val, string lab = "None")
	{
		this->index = val;
		this->label = lab;
	}
public:
	string index;
	string label;
	vector<NODE> parent;
	vector<NODE> children;
};

int findMin(vector<int>& in, int n);

int findMax(vector<int>& in, int n);

int findMax(vector<int>& in, int n, int& idx);

int findPosition(vector<string>& in, string str);

int findPositionPairs(vector<pair<string, string>>& in,
	pair<string, string> str);

int findMaxOf2(int a, int b);

int findMaxOfMat(vector<vector<int>>& in, int& idx1, int& idx2);

int findMaxOfCol(vector<vector<int>>& in, int col, int& row);

bool Belong2PepValues(int pep, vector<int> pepValues);

bool Belong2PepValues(int pep, vector<int> pepValues, int& idx);

bool IsDigits(const std::string &str);

bool Belong2Nodes(NODE a, vector<NODE> nodes, int& idx);

bool Belong2Nodes(NODE a, vector<NODE> nodes);
#endif