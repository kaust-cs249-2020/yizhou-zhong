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

const char dataFileName[30] = "test.txt";
const char dataFilePath[40] = "E:/GitHub/yizhou-zhong/chapter5/data/";
const char outputFileName[20] = "chapter5_13_2.txt";
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
	int score;
	// operation
	vector<string> outputStrs = LinearSpaceAlignment(str1, str2, 
		scoringChar, scoringMat, 
		sigma, score);

	// output file
	char outputFullName[100];
	strcpy(outputFullName, dataFilePath);
	strcat(outputFullName, outputFileName);
	ofstream outfile(outputFullName);
	cout << score << endl;
	outfile << score << endl;

	for (int i = 0; i < outputStrs.size();i++)
	{
		cout << outputStrs[i] << endl;
		outfile << outputStrs[i] << endl;
	}

	outfile.close();
	system("pause");

	// end
	return 0;
}