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

const char dataFileName[30] = "dataset_369340_8.txt"; //"test.txt";
const char dataFilePath[40] = "E:/GitHub/yizhou-zhong/chapter7/data/";
const char outputFileName[20] = "chapter7_12_4.txt";

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

	string outputStr = patterns[0];
	int idx1 = outputStr.find('(');
	int idx2 = outputStr.find(')');
	int len = idx2-idx1-1;
	vector<PAIR> edges;
	while (outputStr.length()>0)
	{
		PAIR oneEdge;
		string tmp;
		string section = outputStr.substr(idx1 + 1, len);
		int idx3 = section.find(',');
		oneEdge.first = stoi(section.substr(0, idx3));
		oneEdge.second = stoi(section.substr(idx3+1, section.length()-idx3-1));
		edges.push_back(oneEdge);

		if (idx2 == (outputStr.length() - 1) || idx2==-1)
		{
			outputStr = ""; 
		}
		else
		{
			outputStr = outputStr.substr(idx2 + 1, outputStr.length() - idx2 - 1);
		}
			
		idx1 = outputStr.find('(');
		idx2 = outputStr.find(')');
		len = idx2 - idx1 - 1;
	}

	// operation
	vector<vector<int>> genome = GraphToGenome(edges);
	
	// output file
	char outputFullName[100];
	strcpy(outputFullName, dataFilePath);
	strcat(outputFullName, outputFileName);

	ofstream outfile(outputFullName);

	for (int i = 0; i < genome.size(); i++)
	{
		cout << '(';
		outfile << '(';
		cout << SequenceFormat(genome[i]);
		outfile << SequenceFormat(genome[i]);
		cout << ')';
		outfile << ')';
	}

	outfile.close();
	system("pause");

	// end
	return 0;
}