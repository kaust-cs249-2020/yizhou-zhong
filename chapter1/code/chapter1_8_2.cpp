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
#include"mathtool.h"

const char dataFileName[30] = "dataset_369239_4.txt";
const char dataFilePath[40] = "E:/GitHub/yizhou-zhong/chapter1/data/";
const char outputFileName[20] = "chapter1_8_2.txt";

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
	string Pattern, Text;
	int d;
	
	vector<int> dataSep;
	for (int i = 0; i < len; i++)
	{
		if (fileData[i] == '\n' || fileData[i] == ' ')
		{
			dataSep.push_back(i);
		}
	}
	Pattern = string(fileData, dataSep[0]);
	Text = string(fileData + dataSep[0] + 1, dataSep[1] - dataSep[0] - 1);
	d = stoi(string(fileData + dataSep[1] + 1, dataSep[2] - dataSep[1] - 1));

	free(fileData);

	// operation
	int k = Pattern.length();
	int n = Text.length();
	vector<int> approxIdx;

	for (int i = 0; i < n - k + 1; i++)
	{
		if (HammingDistance(&Text.substr(i, k), &Pattern) <= d)
		{
			approxIdx.push_back(i);
		}
	}

	// output file
	char outputFullName[100];
	strcpy(outputFullName, dataFilePath);
	strcat(outputFullName, outputFileName);

	ofstream outfile(outputFullName);

	for (int i = 0; i < approxIdx.size(); i++)
	{
		if (i == approxIdx.size() - 1)
		{
			cout << approxIdx[i] << endl;
			outfile << approxIdx[i] << endl;
		}
		else
		{
			cout << approxIdx[i] << ' ';
			outfile << approxIdx[i] << ' ';
		}
	}

	outfile.close();

	// end
	return 0;
}