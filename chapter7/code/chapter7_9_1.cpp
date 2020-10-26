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

const char dataFileName[30] = "dataset_369337_4.txt";// "test.txt";
const char dataFilePath[40] = "E:/GitHub/yizhou-zhong/chapter7/data/";
const char outputFileName[20] = "chapter7_9_1.txt";

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

	vector<vector<int>> genoP;
	vector<vector<int>> genoQ;
	for (int i = 0; i < patterns.size();i++)
	{
		string outputStr = patterns[i];
		int idx1 = outputStr.find('(');
		int idx2 = outputStr.find(')');
		int len = idx2 - idx1 - 1;
		while (outputStr.length()>0)
		{
			vector<int> chromosome;
			string tmp;
			stringstream input(outputStr.substr(idx1 + 1, len));
			while (input >> tmp)
				chromosome.push_back(stoi(tmp));
			if (i==0)
			{
				genoP.push_back(chromosome);
			}
			else
			{
				genoQ.push_back(chromosome);
			}

			if (idx2 == (outputStr.length() - 1) || idx2 == -1)
			{
				outputStr = "";
			}
			else
			{
				outputStr = outputStr.substr(idx2 + 1, outputStr.length() - idx2 - 1);
			}
			idx1 = outputStr.find('(');
			idx2 = outputStr.find(')');
			len = idx2 - idx1 - 1;
		}
	}

	// operation
	int dis = TwoBreakDistance(genoP, genoQ);
	
	// output file
	char outputFullName[100];
	strcpy(outputFullName, dataFilePath);
	strcat(outputFullName, outputFileName);

	ofstream outfile(outputFullName);

	cout << dis;
	outfile << dis;

	//for (int i = 0; i < coloredEdges.size();i++)
	//{
	//	cout << '(';
	//	outfile << '(';
	//	cout << coloredEdges[i].first;
	//	outfile << coloredEdges[i].first;
	//	cout << ", ";
	//	outfile << ", ";
	//	cout << coloredEdges[i].second;
	//	outfile << coloredEdges[i].second;
	//	cout << ')';
	//	outfile << ')';
	//	if (i!=coloredEdges.size()-1)
	//	{
	//		cout << ", ";
	//		outfile << ", ";
	//	}
	//}

	outfile.close();
	system("pause");

	// end
	return 0;
}