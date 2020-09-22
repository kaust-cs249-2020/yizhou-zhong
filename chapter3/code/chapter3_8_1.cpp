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

const char dataFileName[30] = "dataset_369273_2.txt";
const char dataFilePath[40] = "E:/GitHub/yizhou-zhong/chapter3/data/";
const char outputFileName[20] = "chapter3_8_1.txt";

int main(int argc, char *argv[])
{
	vector<string> eulerianGraph;

	// load txt file
	char fileFullName[100];
	strcpy(fileFullName, dataFilePath);
	strcat(fileFullName, dataFileName);

	char buf[1024];
	ifstream infile;
	infile.open(fileFullName);
	if (infile.is_open())
	{
		while (infile.good() && !infile.eof())
		{
			memset(buf, 0, 1024);
			infile.getline(buf, 1204);
			//
			if (buf[0]!='\0')
			{
				eulerianGraph.push_back(buf);
			}
			//
		}
		infile.close();
	}

	// Translate the string to a graph, use a matrix to present
	int nodeNum = eulerianGraph.size();
	vector<string> nodeStr;
	NodeMappingChart nodeRoute(nodeNum, vector<bool>(nodeNum, false));// this is the matrix of graph
	int edgeCount = 0;
	
	for (int i = 0; i < nodeNum; i++)
	{
		int strLen = eulerianGraph[i].length();
		vector<int> spaceIdx;
		vector<int> commaIdx;
		for (int j = 0; j < strLen; j++)
		{
			if (eulerianGraph[i].at(j) == ' ')
			{
				spaceIdx.push_back(j);
			}
			else if (eulerianGraph[i].at(j) == ',')
			{
				commaIdx.push_back(j);
			}
		}
		string startNode = eulerianGraph[i].substr(0, spaceIdx[0]);
		bool nodeExist = false;
		int startNodeIdx;
		for (int j = 0; j < nodeStr.size();j++)
		{
			if (
				strcmp(
				nodeStr[j].c_str(), startNode.c_str()
				) == 0
				)
			{
				nodeExist = true;
				startNodeIdx = j;
				break;
			}
		}
		if (!nodeExist)
		{
			nodeStr.push_back(startNode);
			startNodeIdx = nodeStr.size() - 1;
		}
		vector<string> endNodes;
		if (commaIdx.size() == 0)
		{
			endNodes.push_back(eulerianGraph[i].substr(spaceIdx[1] + 1, eulerianGraph[i].length() - spaceIdx[1]-1));
		}
		else
		{
			endNodes.push_back(eulerianGraph[i].substr(spaceIdx[1] + 1, commaIdx[0] - spaceIdx[1] - 1));
			for (int j = 0; j < commaIdx.size() - 1; j++)
			{
				endNodes.push_back(eulerianGraph[i].substr(commaIdx[j] + 1, commaIdx[j + 1] - commaIdx[j] - 1));
			}
			endNodes.push_back(eulerianGraph[i].substr(commaIdx[commaIdx.size() - 1] + 1, eulerianGraph[i].length() - commaIdx[commaIdx.size() - 1] - 1));
		}
		for (int j = 0; j < endNodes.size();j++)
		{
			nodeExist = false;
			int endNodeIdx;
			for (int m = 0; m < nodeStr.size();m++)
			{
				if (
					strcmp(
					nodeStr[m].c_str(), endNodes[j].c_str()
					) == 0
					)
				{
					nodeExist = true;
					endNodeIdx = m;
					break;
				}
			}
			if (!nodeExist)
			{
				nodeStr.push_back(endNodes[j]);
				endNodeIdx = nodeStr.size() - 1;
			}
			nodeRoute[startNodeIdx][endNodeIdx] = true;
			edgeCount++;
		}
	}
	cout << "edgeCount: " << edgeCount << endl;
	cout << "nodeRoute Size: " << nodeRoute.size() << endl;

	// operation
	vector<int> cycleRoute = EulerianCycle(&nodeRoute);
	cout << "cycleRoute Size: " << cycleRoute.size() << endl;

	// output file
	char outputFullName[100];
	strcpy(outputFullName, dataFilePath);
	strcat(outputFullName, outputFileName);

	ofstream outfile(outputFullName);

	int cycleSize = cycleRoute.size();
	if (cycleSize > 0)
	{
		outfile << nodeStr[cycleRoute[0]];
	}
	for (int i = 1; i < cycleSize; i++)
	{
		outfile << "->" << nodeStr[cycleRoute[i]];
	}

	outfile.close();
	system("pause");

	// end
	return 0;
}