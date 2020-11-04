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

const char dataFileName[30] = "dataset_369339_5.txt"; // "test.txt";
const char dataFilePath[40] = "E:/GitHub/yizhou-zhong/chapter7/data/";
const char outputFileName[20] = "chapter7_11_1.txt";

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

	int k = stoi(patterns[0]);
	string seq1 = patterns[1];
	string seq2 = patterns[2];

	// operation
	vector<PAIR> sharedKmers =  SharedKmersProblem(k, seq1, seq2);
	
	// output file
	char outputFullName[100];
	strcpy(outputFullName, dataFilePath);
	strcat(outputFullName, outputFileName);

	ofstream outfile(outputFullName);

	for (int i = 0; i < sharedKmers.size(); i++)
	{
		cout << '(';
		outfile << '(';
		cout<<sharedKmers[i].first;
		outfile<<sharedKmers[i].first;
		cout << ", ";
		outfile << ", ";
		cout<<sharedKmers[i].second;
		outfile<<sharedKmers[i].second;
		cout << ')';
		outfile << ')';
		cout << endl;
		outfile << endl;
	}

	outfile.close();
	system("pause");

	// end
	return 0;
}