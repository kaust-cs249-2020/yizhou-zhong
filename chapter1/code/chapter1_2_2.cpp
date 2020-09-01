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

const char dataFileName[30] = "dataset_369233_13.txt";
const char dataFilePath[40] = "E:/GitHub/yizhou-zhong/chapter1/data/";
const char outputFileName[20] = "chapter1_2_2.txt";

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
	int k;
	vector<int> dataSep;

	for (int i = 0; i < len; i++)
	{
		if (fileData[i] == '\n')
		{
			dataSep.push_back(i);
		}
	}
	Text = string(fileData, dataSep[0]);
	k = stoi(string(fileData + dataSep[0] + 1, dataSep[1] - dataSep[0] - 1));
	free(fileData);
	cout << Text.c_str() << ' ' << k << endl;

	// operation
	map<string, int> freMap = FrequencyTable(&Text, k);
	map<string, int>::iterator iter;
	int maxmun = 0;
	for (iter = freMap.begin(); iter != freMap.end(); iter++)
	{
		if (iter->second > maxmun)
		{
			maxmun = iter->second;
		}
	}
	vector<string> outputStr;
	for (iter = freMap.begin(); iter != freMap.end(); iter++)
	{
		if (iter->second == maxmun)
		{
			outputStr.push_back(iter->first);
		}
	}

	// output file
	char outputFullName[100];
	strcpy(outputFullName, dataFilePath);
	strcat(outputFullName, outputFileName);

	ofstream outfile(outputFullName);

	for (int i = 0; i < outputStr.size(); i++)
	{
		cout << outputStr[i].c_str() << ' ';
		outfile << outputStr[i].c_str() << ' ';
	}
	cout << endl;
	outfile << endl;
	outfile.close();

	// end
	return 0;
}