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

const char dataFileName[30] = "dataset_369270_8.txt";
const char dataFilePath[40] = "E:/GitHub/yizhou-zhong/chapter3/data/";
const char outputFileName[20] = "chapter3_5_1.txt";

int main(int argc, char *argv[])
{
	vector<string> kmersPatterns;

	//// load txt file
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
				kmersPatterns.push_back(buf);
			}
			//
		}
		infile.close();
	}

	// operation
	vector<string> patternStrs;
	vector<string> patternStrsNoRepeat;
	vector<vector<bool>> adjMat = deBruijnGraphPatterns(&kmersPatterns, &patternStrs, &patternStrsNoRepeat);

	// output file
	char outputFullName[100];
	strcpy(outputFullName, dataFilePath);
	strcat(outputFullName, outputFileName);

	ofstream outfile(outputFullName);

	int matY = adjMat.size();
	int matX;
	if (matY > 0)
	{
		matX = adjMat[0].size();
	}
	 
	for (int i = 0; i < matY; i++)
	{
		bool adjexist = false;
		for (int j = 0; j < matX; j++)
		{
			if (adjMat[i][j])
			{
				if (!adjexist)
				{
					outfile << patternStrsNoRepeat[i] << " -> ";
					outfile << patternStrs[j];
					adjexist = true;
				}
				else
				{
					outfile << ',' << patternStrs[j];
				}
			}
		}
		if (adjexist)
		{
			outfile << endl;
		}
	}

	outfile.close();
	system("pause");

	// end
	return 0;
}