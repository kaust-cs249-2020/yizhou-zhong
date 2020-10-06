#define _CRT_SECURE_NO_DEPRECATE

#include <string>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "functions.h"
#include "mathtool.h"

const char dataFileName[30] = "dataset_369316_7.txt"; // "test.txt";
const char dataFilePath[40] = "E:/GitHub/yizhou-zhong/chapter5/data/";
const char outputFileName[20] = "chapter5_8_2.txt";

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

	// translation
	int graphStartNode, graphEndNode;
	graphStartNode = stoi(patterns[0]);
	graphEndNode = stoi(patterns[1]);
	vector<int> nodes, weightList;
	CountTable adjList;

	for (int i = 2; i < patterns.size();i++)
	{
		int idx1 = patterns[i].find('-');
		int idx2 = patterns[i].find('>');
		int idx3 = patterns[i].find(':');
		int startNode = stoi(patterns[i].substr(0,idx1));
		int endNode = stoi(patterns[i].substr(idx2+1, idx3-idx2-1));
		int edgeWeight = stoi(patterns[i].substr(idx3+1,patterns[i].length()-idx3-1));
		int startIdx, endIdx;
		if (!Belong2PepValues(startNode, nodes,startIdx))
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
	int longestPathLen;
	vector<int> longestPath = LongestPathinDag(graphStartNode, 
		graphEndNode,
		nodes,
		weightList,
		adjList,
		longestPathLen);

	// output file
	char outputFullName[100];
	strcpy(outputFullName, dataFilePath);
	strcat(outputFullName, outputFileName);

	ofstream outfile(outputFullName);

	cout << longestPathLen << endl;
	outfile << longestPathLen << endl;

	for (int i = 0; i < longestPath.size();i++)
	{
		cout << longestPath[i];
		outfile << longestPath[i];
		if (i!=longestPath.size()-1)
		{
			cout << "->";
			outfile << "->";
		}
	}

	outfile.close();
	system("pause");

	// end
	return 0;
}