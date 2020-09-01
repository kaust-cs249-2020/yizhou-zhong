#define _CRT_SECURE_NO_DEPRECATE

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "functions.h"

const char dataFileName[30] = "dataset_369233_6.txt";
const char dataFilePath[40] = "E:/GitHub/yizhou-zhong/chapter1/data/";
const char outputFileName[20] = "chapter1_2_1.txt";

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
	string Pattern;
	vector<int> dataSep;

	for (int i = 0; i < len; i++)
	{
		if (fileData[i] == '\n')
		{
			dataSep.push_back(i);
		}
	}
	Text = string(fileData, dataSep[0]);
	Pattern = string(fileData + dataSep[0] + 1, dataSep[1] - dataSep[0] - 1);
	free(fileData);
	cout << Text.c_str() << ' ' << Pattern.c_str() << endl;

	// operation
	int pCount = PatternCount(&Text, Pattern);

	// output file
	cout << pCount << endl;

	char outputFullName[100];
	strcpy(outputFullName, dataFilePath);
	strcat(outputFullName, outputFileName);

	ofstream outfile(outputFullName);
	outfile << pCount << endl;
	outfile.close();

	// end
	return 0;
}