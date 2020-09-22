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

const char dataFileName[30] = "dataset_369275_5.txt";
const char dataFilePath[40] = "E:/GitHub/yizhou-zhong/chapter3/data/";
const char outputFileName[20] = "chapter3_10_1.txt";

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

	// operation
	vector<string> contigs = ContigGeneration(&patternStrs);

	// output file
	char outputFullName[100];
	strcpy(outputFullName, dataFilePath);
	strcat(outputFullName, outputFileName);

	ofstream outfile(outputFullName);

	for (int i = 0; i < contigs.size();i++)
	{
		outfile << contigs[i].c_str() << endl;
		cout << contigs[i].c_str() << endl;
	}

	outfile.close();
	system("pause");

	// end
	return 0;
}