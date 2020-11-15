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

const char dataFileName[30] = "dataset_369353_7.txt"; // "test.txt";
const char dataFilePath[40] = "../../../yizhou-zhong/chapter8/data/";
const char outputFileName[20] = "chapter8_7_1.txt";

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
	vector<vector<int>> disMat;
	for (int i = 1; i < patterns.size();i++)
	{
		vector <int> disVec;
		string tmp;
		stringstream input(patterns[i]);
		while (input >> tmp)
			disVec.push_back(stoi(tmp));
		disMat.push_back(disVec);
	}

	// operation
	vector<string> outStr = NeighborJoiningProblem(n, disMat);

	// output file
	char outputFullName[100];
	strcpy(outputFullName, dataFilePath);
	strcat(outputFullName, outputFileName);

	ofstream outfile(outputFullName);

	for (int i = 0; i < outStr.size(); i++)
	{
		cout << outStr[i] << endl;
		outfile << outStr[i] << endl;
	}

	outfile.close();
	system("pause");

	// end
	return 0;
}