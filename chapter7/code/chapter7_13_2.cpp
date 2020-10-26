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

const char dataFileName[30] = "dataset_369341_3.txt";// "test.txt";
const char dataFilePath[40] = "E:/GitHub/yizhou-zhong/chapter7/data/";
const char outputFileName[20] = "chapter7_13_2.txt";

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

	// load genome
	string outputStr = patterns[0];
	int idx1 = outputStr.find('(');
	int idx2 = outputStr.find(')');
	int len = idx2 - idx1 - 1;
	vector<vector<int>> genome;
	while (outputStr.length() > 0)
	{
		vector<int> chromosome;
		string tmp;
		stringstream input(outputStr.substr(idx1 + 1, len));
		while (input >> tmp)
			chromosome.push_back(stoi(tmp));
		genome.push_back(chromosome);

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

	outputStr = patterns[1];
	int idx = outputStr.find(',');
	int i1 = stoi(outputStr.substr(0, idx));
	outputStr = outputStr.substr(idx+1, outputStr.length()-idx-1);
	idx = outputStr.find(',');
	int i2 = stoi(outputStr.substr(0, idx));
	outputStr = outputStr.substr(idx+1, outputStr.length() - idx - 1);
	idx = outputStr.find(',');
	int i3 = stoi(outputStr.substr(0, idx));
	outputStr = outputStr.substr(idx+1, outputStr.length() - idx - 1);
	int i4 = stoi(outputStr);

	// operation
	vector<vector<int>> genomePback = TwoBreakOnGenome(genome, i1, i2, i3, i4);

	// output file
	char outputFullName[100];
	strcpy(outputFullName, dataFilePath);
	strcat(outputFullName, outputFileName);

	ofstream outfile(outputFullName);

	for (int i = 0; i < genomePback.size(); i++)
	{
		cout << '(';
		outfile << '(';
		cout << SequenceFormat(genomePback[i]);
		outfile << SequenceFormat(genomePback[i]);
		cout << ')';
		outfile << ')';
	}

	outfile.close();
	system("pause");

	// end
	return 0;
}