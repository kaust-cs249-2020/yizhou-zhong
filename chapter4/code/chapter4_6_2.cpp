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

const char dataFileName[30] = "test.txt";
const char dataFilePath[40] = "E:/GitHub/yizhou-zhong/chapter4/data/";
const char outputFileName[20] = "chapter4_6_2.txt";
//const char tableFileName[30] = "RNA_codon_table_1.txt";
const char massTableName[30] = "integer_mass_table.txt";

int main(int argc, char *argv[])
{
	// load the mass table first
	char tableFileFullName[150];
	strcpy(tableFileFullName, dataFilePath);
	strcat(tableFileFullName, massTableName);
	string buf;
	ifstream infile;
	vector<string> massTableStr;

	infile.open(tableFileFullName);
	if (infile.is_open())
	{
		while (infile.good() && !infile.eof())
		{
			getline(infile, buf);
			if (buf[0] != '\0')
			{
				massTableStr.push_back(buf);
			}
		}
		infile.close();
	}

	IntegerMassTable massTable;
	for (int i = 0; i < massTableStr.size(); i++)
	{
		int sep = massTableStr[i].find(' ');
		char key = massTableStr[i][0];
		string valueStr;
		if (sep == massTableStr[i].length()-1)
		{
			valueStr = '\0';
		}
		else
		{
			valueStr = massTableStr[i].substr(sep + 1, massTableStr[i].length()-sep-1);
		}
		int valueInt = stoi(valueStr);
		massTable.insert(pair<char, int>(key, valueInt));
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
	vector<int> cycloSpectrum = TheoreticalSpectrum(patternStrs[0], &massTable);
	
	// output file
	char outputFullName[100];
	strcpy(outputFullName, dataFilePath);
	strcat(outputFullName, outputFileName);

	ofstream outfile(outputFullName);

	for (int i = 0; i < cycloSpectrum.size(); i++)
	{
		if (i == cycloSpectrum.size() - 1)
		{
			outfile << cycloSpectrum[i] << endl;
			cout << cycloSpectrum[i] << endl;
		}
		else
		{
			outfile << cycloSpectrum[i] << ' ';
			cout << cycloSpectrum[i] << ' ';
		}
	}

	outfile.close();
	system("pause");

	// end
	return 0;
}