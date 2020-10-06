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

const char dataFileName[30] = "dataset_369325_3.txt";// "test.txt";
const char dataFilePath[40] = "E:/GitHub/yizhou-zhong/chapter5/data/";
const char outputFileName[20] = "chapter5_17_1.txt";

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

	CountTable adjList;
	vector<int> nodes;
	int len = patterns.size();
	for (int i = 0; i < len; i++)
	{
		int idx1 = patterns[i].find('-')-1;
		int idx2 = patterns[i].find('>')+1;
		int startNode = stoi(patterns[i].substr(0, idx1));
		int startIdx, endIdx;
		if (!Belong2PepValues(startNode, nodes, startIdx))
		{
			nodes.push_back(startNode);
			startIdx = nodes.size() - 1;
		}
		int endNode;
		string subStr = patterns[i].substr(idx2 + 1, patterns[i].length() - idx2 + 1);
		vector<int> commas;
		for (int j = 0; j < subStr.length();j++)
		{
			if (subStr.at(j)==',')
			{
				commas.push_back(j);
			}
		}
		int lastidx = 0;
		for (int j = 0; j < commas.size(); j++)
		{
			endNode = stoi(subStr.substr(lastidx, commas[j] - lastidx));
			lastidx = commas[j] + 1;
			if (!Belong2PepValues(endNode, nodes, endIdx))
			{
				nodes.push_back(endNode);
				endIdx = nodes.size() - 1;
			}
			adjList.push_back(pair<int, int>(startIdx, endIdx));
		}
		endNode = stoi(subStr.substr(lastidx, subStr.length()-lastidx));
		if (!Belong2PepValues(endNode, nodes, endIdx))
		{
			nodes.push_back(endNode);
			endIdx = nodes.size() - 1;
		}
		adjList.push_back(pair<int, int>(startIdx, endIdx));	
	}

	// operation
	vector<int> graphOrdering = TopologicalOrdering(nodes, adjList);

	// output file
	char outputFullName[100];
	strcpy(outputFullName, dataFilePath);
	strcat(outputFullName, outputFileName);

	ofstream outfile(outputFullName);

	len = graphOrdering.size();
	for (int i = 0; i < len;i++)
	{
		cout << graphOrdering[i];
		outfile << graphOrdering[i];
		if (i!=len-1)
		{
			cout << ", ";
			outfile << ", ";
		}
	}
	outfile.close();
	system("pause");

	// end
	return 0;
}