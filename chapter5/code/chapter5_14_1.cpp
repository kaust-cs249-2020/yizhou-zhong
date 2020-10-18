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

const char dataFileName[30] = "dataset_369322_5.txt";// "test.txt";//
const char dataFilePath[40] = "E:/GitHub/yizhou-zhong/chapter5/data/";
const char outputFileName[20] = "chapter5_14_1.txt";

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
	string str1, str2, str3;
	str1 = patterns[0];
	str2 = patterns[1];
	str3 = patterns[2];
	int score;
	// operation
	vector<string> outputStrs = MultipleLstCommonSubseqProblem(str1, str2,str3,score);

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