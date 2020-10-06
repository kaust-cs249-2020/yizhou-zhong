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

const char dataFileName[30] = "dataset_369314_10.txt";// "test.txt";
const char dataFilePath[40] = "E:/GitHub/yizhou-zhong/chapter5/data/";
const char outputFileName[20] = "chapter5_6_1.txt";

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

	int len = patterns.size();
	int n, m;
	int sep = patterns[0].find(' ');
	n = stoi(patterns[0].substr(0, sep));
	m = stoi(patterns[0].substr(sep+1, patterns[0].length()-1-sep));
	
	vector<vector<int>> d, r;
	int i = 1;
	for (; i < len;i++)
	{
		if (strcmp(patterns[i].c_str(), "-")==0)
		{
			break;
		}
		vector<int> tmp;
		int lastIdx = 0, plen = patterns[i].length();
		for (int j = 0; j < plen; j++)
		{
			if (patterns[i][j] == ' ')
			{
				tmp.push_back(stoi(patterns[i].substr(lastIdx, j - lastIdx)));
				lastIdx = j + 1;
			}
		}
		tmp.push_back(stoi(patterns[i].substr(lastIdx, plen - lastIdx)));
		d.push_back(tmp);
	}
	i++;
	for (; i < len; i++)
	{
		vector<int> tmp;
		int lastIdx = 0, plen = patterns[i].length();
		for (int j = 0; j < plen; j++)
		{
			if (patterns[i][j] == ' ')
			{
				tmp.push_back(stoi(patterns[i].substr(lastIdx, j - lastIdx)));
				lastIdx = j + 1;
			}
		}
		tmp.push_back(stoi(patterns[i].substr(lastIdx, plen - lastIdx)));
		r.push_back(tmp);
	}

	// operation
	int longestPathLen = ManhattanTourist(n, m, d, r);

	// output file
	char outputFullName[100];
	strcpy(outputFullName, dataFilePath);
	strcat(outputFullName, outputFileName);

	ofstream outfile(outputFullName);

	cout << longestPathLen << endl;
	outfile << longestPathLen << endl;

	outfile.close();
	system("pause");

	// end
	return 0;
}