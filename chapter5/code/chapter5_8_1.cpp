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

const char dataFileName[30] = "dataset_369316_5.txt"; // "test.txt";
const char dataFilePath[40] = "E:/GitHub/yizhou-zhong/chapter5/data/";
const char outputFileName[20] = "chapter5_8_1.txt";

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

	string s, t;
	s = patterns[0];
	t = patterns[1];

	// operation
	string longestComSeq = LongestComSubSeq(s, t);

	// output file
	char outputFullName[100];
	strcpy(outputFullName, dataFilePath);
	strcat(outputFullName, outputFileName);

	ofstream outfile(outputFullName);

	cout << longestComSeq << endl;
	outfile << longestComSeq << endl;

	outfile.close();
	system("pause");

	// end
	return 0;
}