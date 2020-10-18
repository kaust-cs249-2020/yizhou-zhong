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

const char dataFileName[30] = "dataset_369321_12.txt";//"test.txt";
const char dataFilePath[40] = "E:/GitHub/yizhou-zhong/chapter5/data/";
const char outputFileName[20] = "chapter5_13_1.txt";
const char scoringMatFileName[20] = "BLOSUM62.txt";

int main(int argc, char *argv[])
{
	string buf;
	ifstream infile;

	// load scoring matrix file
	vector<string> fileData;
	char matFileFullName[100];
	strcpy(matFileFullName, dataFilePath);
	strcat(matFileFullName, scoringMatFileName);
	infile.open(matFileFullName);
	if (infile.is_open())
	{
		while (infile.good() && !infile.eof())
		{
			getline(infile, buf);
			if (buf[0] != '\0')
			{
				fileData.push_back(buf);
			}
		}
		infile.close();
	}
	string scoringChar;
	vector<vector<int>> scoringMat;
	string tmp;
	stringstream input(fileData[0]);
	while (input >> tmp)
		scoringChar.append(tmp);
	for (int i = 1; i < fileData.size(); i++)
	{
		vector<int> scoringLine;
		stringstream input(fileData[i]);
		input >> tmp;
		while (input >> tmp)
		{
			scoringLine.push_back(stoi(tmp));
		}
		scoringMat.push_back(scoringLine);
	}  

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
	string str1, str2;
	str1 = patterns[0];
	str2 = patterns[1];
	int sigma = 5;
	// operation
	vector<PAIR> outputPairs = MidEdgeLinearSpaceProblem(str1, str2,
		scoringChar, scoringMat, sigma);

	// output file
	char outputFullName[100];
	strcpy(outputFullName, dataFilePath);
	strcat(outputFullName, outputFileName);
	ofstream outfile(outputFullName);

	cout<<'('<<outputPairs[0].first << ", " << outputPairs[0].second << ')' << ' ';
	outfile << '(' << outputPairs[0].first << ", " << outputPairs[0].second << ')' << ' ';
	cout << '(' << outputPairs[1].first << ", " << outputPairs[1].second << ')';
	outfile << '(' << outputPairs[1].first << ", " << outputPairs[1].second << ')';

	outfile.close();
	system("pause");

	// end
	return 0;
}