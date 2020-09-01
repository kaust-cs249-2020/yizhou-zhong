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

//const char dataFileName[30] = "dataset_369235_5.txt";
const char dataFileName[30] = "E_coli.txt";
const char dataFilePath[40] = "E:/GitHub/yizhou-zhong/chapter1/data/";
//const char outputFileName[20] = "chapter1_4_1.txt";
const char outputFileName[20] = "E_coli_out.txt";

int main(int argc, char *argv[])
{
	// load txt file
	char fileFullName[100];
	strcpy(fileFullName, dataFilePath);
	strcat(fileFullName, dataFileName);

	FILE *fp = fopen(fileFullName, "r");
	fseek(fp, 0, SEEK_END);
	long len = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char *fileData = (char*)malloc(len + 1);
	fread(fileData, 1, len, fp);
	fclose(fp);

	// seprate the data from file
	string Text;
	int k, L, t;
	
	vector<int> dataSep;
	for (int i = 0; i < len; i++)
	{
		if (fileData[i] == '\n' || fileData[i] == ' ')
		{
			dataSep.push_back(i);
		}
	}
	Text = string(fileData, dataSep[0]);
	//k = stoi(string(fileData + dataSep[0] + 1, dataSep[1] - dataSep[0] - 1));
	//L = stoi(string(fileData + dataSep[1] + 1, dataSep[2] - dataSep[1] - 1));
	//t = stoi(string(fileData + dataSep[2] + 1, dataSep[3] - dataSep[2] - 1));
	k = 9; L = 500; t = 3;
	free(fileData);

	//cout << Text.c_str() << endl;
	//cout << k << ' ' << L << ' ' << t << endl;

	// operation
	vector<string> clumpPatterns = ClumpFinding(&Text, k, L, t);

	// output file
	char outputFullName[100];
	strcpy(outputFullName, dataFilePath);
	strcat(outputFullName, outputFileName);

	ofstream outfile(outputFullName);

	for (int i = 0; i < clumpPatterns.size(); i++)
	{
		if (i == clumpPatterns.size() - 1)
		{
			cout << clumpPatterns[i].c_str() << endl;
			outfile << clumpPatterns[i].c_str() << endl;
		}
		else
		{
			cout << clumpPatterns[i].c_str() << ' ';
			outfile << clumpPatterns[i].c_str() << ' ';
		}
	}
	cout << clumpPatterns.size() << endl;
	outfile << clumpPatterns.size() << endl;

	outfile.close();

	// end
	return 0;
}