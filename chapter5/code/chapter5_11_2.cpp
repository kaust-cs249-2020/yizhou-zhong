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

const char dataFileName[30] = "dataset_369319_5.txt";// "test.txt";
const char dataFilePath[40] = "E:/GitHub/yizhou-zhong/chapter5/data/";
const char outputFileName[20] = "chapter5_11_2.txt";

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
	string str1, str2;
	str1 = patterns[0];
	str2 = patterns[1];
	int highestScore;
	// operation
	vector<string> outputStrs = FittingAlignmentProblem(str1, str2, highestScore);

	// output file
	char outputFullName[100];
	strcpy(outputFullName, dataFilePath);
	strcat(outputFullName, outputFileName);
	ofstream outfile(outputFullName);
	cout << highestScore << endl;
	outfile << highestScore << endl;

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