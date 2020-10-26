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

const char dataFileName[30] = "dataset_369340_4.txt";// "test.txt";
const char dataFilePath[40] = "E:/GitHub/yizhou-zhong/chapter7/data/";
const char outputFileName[20] = "chapter7_12_1.txt";

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
	int idx1 = patterns[0].find('(');
	int idx2 = patterns[0].find(')');
	int len = idx2-idx1-1;
	vector <int> Chromosome;
	string tmp;
	stringstream input(patterns[0].substr(idx1+1, len));
	while (input >> tmp)
		Chromosome.push_back(stoi(tmp));

	// operation
	vector<int> nodes = ChromosomeToCycle(Chromosome);
	
	// output file
	char outputFullName[100];
	strcpy(outputFullName, dataFilePath);
	strcat(outputFullName, outputFileName);

	ofstream outfile(outputFullName);

	cout << '(';
	outfile << '(';
	for (int i = 0; i < nodes.size();i++)
	{
		cout << nodes[i];
		outfile << nodes[i];
		if (i!=nodes.size()-1)
		{
			cout << ' ';
			outfile << ' ';
		}
	}
	cout << ')';
	outfile << ')';

	outfile.close();
	system("pause");

	// end
	return 0;
}