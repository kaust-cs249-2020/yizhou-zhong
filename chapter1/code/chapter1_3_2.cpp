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

const char dataFileName[30] = "dataset_369234_5.txt";
const char dataFilePath[40] = "E:/GitHub/yizhou-zhong/chapter1/data/";
const char outputFileName[20] = "chapter1_3_2.txt";

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
	string patternStr;
	string Text;
	vector<int> dataSep;
	for (int i = 0; i < len; i++)
	{
		if (fileData[i] == '\n')
		{
			dataSep.push_back(i);
		}
	}
	patternStr = string(fileData, dataSep[0]);
	Text = string(fileData + dataSep[0] + 1, dataSep[1] - dataSep[0] - 1);
	free(fileData);

	cout << patternStr.c_str() << endl;
	cout << Text.c_str() << endl;

	// operation
	vector<int> patternIdx = PatternMatching(&Text, patternStr);

	// output file
	char outputFullName[100];
	strcpy(outputFullName, dataFilePath);
	strcat(outputFullName, outputFileName);

	ofstream outfile(outputFullName);

	for (int i = 0; i < patternIdx.size(); i++)
	{
		if (i == patternIdx.size() - 1)
		{
			cout << patternIdx[i] << endl;
			outfile << patternIdx[i] << endl;
		}
		else
		{
			cout << patternIdx[i] << ' ';
			outfile << patternIdx[i] << ' ';
		}
	}
	outfile.close();

	// end
	return 0;
}