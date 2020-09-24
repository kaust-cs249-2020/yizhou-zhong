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

const char dataFileName[30] = "dataset_369290_7.txt";//"test.txt";
const char dataFilePath[40] = "E:/GitHub/yizhou-zhong/chapter4/data/";
const char outputFileName[20] = "chapter4_2_2.txt";
const char tableFileName[30] = "RNA_codon_table_1.txt";

int main(int argc, char *argv[])
{
	// load the RNA table first
	char tableFileFullName[150];
	strcpy(tableFileFullName, dataFilePath);
	strcat(tableFileFullName, tableFileName);
	string buf;
	ifstream infile;
	vector<string> rnaTableStr;

	infile.open(tableFileFullName);
	if (infile.is_open())
	{
		while (infile.good() && !infile.eof())
		{
			getline(infile, buf);
			if (buf[0] != '\0')
			{
				rnaTableStr.push_back(buf);
			}
		}
		infile.close();
	}

	GeneticCodeTable rnaCodeTable;
	for (int i = 0; i < rnaTableStr.size(); i++)
	{
		int sep = rnaTableStr[i].find(' ');
		string key = rnaTableStr[i].substr(0, sep);
		string valueChar;
		if (sep == rnaTableStr[i].length()-1)
		{
			valueChar = '\0';
		}
		else
		{
			valueChar = rnaTableStr[i].substr(sep + 1, rnaTableStr[i].length()-sep-1);
		}
		rnaCodeTable.insert(pair<string, string>(key, valueChar));
	}

	
	// load txt file
	vector<string> patternStrs;
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
				patternStrs.push_back(buf);
			}
		}
		infile.close();
	}

	// operation
	vector<string> subString = PeptideEncoding(patternStrs[0], patternStrs[1], &rnaCodeTable);

	// output file
	char outputFullName[100];
	strcpy(outputFullName, dataFilePath);
	strcat(outputFullName, outputFileName);

	ofstream outfile(outputFullName);

	for (int i = 0; i < subString.size(); i++)
	{
		outfile << subString[i].c_str() << endl;
		cout << subString[i].c_str() << endl;
	}

	outfile.close();
	system("pause");

	// end
	return 0;
}