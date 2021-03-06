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

const char dataFileName[30] = "dataset_369313_10.txt";// "test.txt";
const char dataFilePath[40] = "E:/GitHub/yizhou-zhong/chapter5/data/";
const char outputFileName[20] = "chapter5_5_1.txt";

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

	vector<int> Coins;
	int lastIdx = 0, len = patterns[1].length();
	for (int i = 0; i < len; i++)
	{
		if (patterns[1][i] == ',')
		{
			Coins.push_back(stoi(patterns[1].substr(lastIdx, i - lastIdx)));
			lastIdx = i + 1;
		}
	}
	Coins.push_back(stoi(patterns[1].substr(lastIdx, len - lastIdx)));
	int money = stoi(patterns[0]);

	// operation
	int minCoinNum = DPChange(money, Coins);

	// output file
	char outputFullName[100];
	strcpy(outputFullName, dataFilePath);
	strcat(outputFullName, outputFileName);

	ofstream outfile(outputFullName);

	cout << minCoinNum << endl;
	outfile << minCoinNum << endl;

	outfile.close();
	system("pause");

	// end
	return 0;
}