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

const char dataFileName[30] = "dataset_369274_16.txt";// "sample.txt";
const char dataFilePath[40] = "E:/GitHub/yizhou-zhong/chapter3/data/";
const char outputFileName[20] = "chapter3_9_1.txt";

int main(int argc, char *argv[])
{
	vector<string> patternStrs;

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
				patternStrs.push_back(buf);
			}
			//
		}
		infile.close();
	}
	int len = patternStrs.size()-1;
	int sep = patternStrs[0].find(' ');
	int k = stoi(patternStrs[0].substr(0, sep));
	int d = stoi(patternStrs[0].substr(sep + 1, patternStrs[0].length()-sep-1));
	
	PairedReadsChart pairedReads;
	for (int i = 0; i < len; i++)
	{
		int sepr = patternStrs[i + 1].find('|');
		pairedReads.push_back(pair<string, string>(patternStrs[i + 1].substr(0, sepr),
			patternStrs[i + 1].substr(sepr + 1, patternStrs[i+1].length() - sepr - 1)));
	}

	// operation
	string Text = StringReconstructionByPairedReads(k, d, &pairedReads);

	// output file
	char outputFullName[100];
	strcpy(outputFullName, dataFilePath);
	strcat(outputFullName, outputFileName);

	ofstream outfile(outputFullName);

	outfile << Text.c_str() << endl;
	cout << Text.c_str() << endl;

	outfile.close();
	system("pause");

	// end
	return 0;
}