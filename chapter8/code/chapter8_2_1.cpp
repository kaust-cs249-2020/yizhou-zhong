#define _CRT_SECURE_NO_DEPRECATE

#include <string>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include "functions.h"
#include "mathtool.h"

const char dataFileName[30] = "dataset_369348_12.txt";// "test.txt";
const char dataFilePath[40] = "E:/GitHub/yizhou-zhong/chapter8/data/";
const char outputFileName[20] = "chapter8_2_1.txt";

int main(int argc, char *argv[])
{
	string buf;
	ifstream infile;
	
	// load txt file
	vector<string> patterns;
	char fileFullName[100];
	strcpy(fileFullName, dataFilePath);
	strcat(fileFullName, dataFileName);
	infile.open(fileFullName);
	if (infile.is_open())
	{
		while (infile.good() && !infile.eof())
		{
			getline(infile, buf);
			if (buf[0]!='\0')
			{
				patterns.push_back(buf);
			}
		}
		infile.close();
	}

	// data format
	int n = stoi(patterns[0]);
	vector<int> nodes, weightList;
	CountTable adjList;
	for (int i = 1; i < patterns.size(); i++)
	{
		int idx1 = patterns[i].find('-');
		int idx2 = patterns[i].find('>');
		int idx3 = patterns[i].find(':');
		int startNode = stoi(patterns[i].substr(0, idx1));
		int endNode = stoi(patterns[i].substr(idx2 + 1, idx3 - idx2 - 1));
		int edgeWeight = stoi(patterns[i].substr(idx3 + 1, patterns[i].length() - idx3 - 1));
		int startIdx, endIdx;
		if (!Belong2PepValues(startNode, nodes, startIdx))
		{
			nodes.push_back(startNode);
			startIdx = nodes.size() - 1;
		}
		if (!Belong2PepValues(endNode, nodes, endIdx))
		{
			nodes.push_back(endNode);
			endIdx = nodes.size() - 1;
		}
		adjList.push_back(pair<int, int>(startIdx, endIdx));
		weightList.push_back(edgeWeight);
	}


	// operation
	vector<vector<int>> disMat = DistanceBetweenLeaves(n, nodes, weightList, adjList);

	// output file
	char outputFullName[100];
	strcpy(outputFullName, dataFilePath);
	strcat(outputFullName, outputFileName);

	ofstream outfile(outputFullName);

	for (int i = 0; i < disMat.size(); i++)
	{
		for (int j = 0; j < disMat.size();j++)
		{
			cout << disMat[i][j];
			outfile << disMat[i][j];
			if (j!=disMat.size()-1)
			{
				cout << '\t';
				outfile << '\t';
			}
			else
			{
				cout << endl;
				outfile << endl;
			}
		}
	}
	outfile.close();
	system("pause");

	// end
	return 0;
}