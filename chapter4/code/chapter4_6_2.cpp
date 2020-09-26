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

const char dataFileName[30] = "dataset_369294_6.txt"; // "test.txt";
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
	string specStrs;
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
				specStrs = buf;
			}
		}
		infile.close();
	}

	vector<int> specInt;
	int lastIdx = 0;
	int len = specStrs.length();
	for (int i = 0; i < len; i++)
	{
		if (specStrs[i] == ' ')
		{
			specInt.push_back(stoi(specStrs.substr(lastIdx, i-lastIdx)));
			lastIdx = i + 1;
		}
	}
	specInt.push_back(stoi(specStrs.substr(lastIdx, len-lastIdx)));

	// operation
	vector<string> finalPeptides = CyclopeptideSequencing(specInt, &massTable);
	
	// output file
	char outputFullName[100];
	strcpy(outputFullName, dataFilePath);
	strcat(outputFullName, outputFileName);

	ofstream outfile(outputFullName);

	for (int i = 0; i < finalPeptides.size(); i++)
	{
		if (i == finalPeptides.size() - 1)
		{
			outfile << finalPeptides[i] << endl;
			cout << finalPeptides[i] << endl;
		}
		else
		{
			outfile << finalPeptides[i] << ' ';
			cout << finalPeptides[i] << ' ';
		}
	}

	outfile.close();
	system("pause");

	// end
	return 0;
}