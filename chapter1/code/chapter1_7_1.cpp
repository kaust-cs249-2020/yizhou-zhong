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

const char dataFileName[30] = "dataset_369238_6.txt";
const char dataFilePath[40] = "E:/GitHub/yizhou-zhong/chapter1/data/";
const char outputFileName[20] = "chapter1_7_1.txt";

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
	
	vector<int> dataSep;
	for (int i = 0; i < len; i++)
	{
		if (fileData[i] == '\n' || fileData[i] == ' ')
		{
			dataSep.push_back(i);
		}
	}
	Text = string(fileData, dataSep[0]);
	free(fileData);

	// operation
	vector<int> skewSeq = SkewDiagram(&Text);
	int minValue = findMin(skewSeq, skewSeq.size());
	vector<int> minIdx;
	for (int i = 0; i < skewSeq.size(); i++)
	{
		if (skewSeq[i] == minValue)
		{
			minIdx.push_back(i);
		}
	}

	// output file
	char outputFullName[100];
	strcpy(outputFullName, dataFilePath);
	strcat(outputFullName, outputFileName);

	ofstream outfile(outputFullName);

	for (int i = 0; i < minIdx.size(); i++)
	{
		if (i == minIdx.size() - 1)
		{
			cout << minIdx[i] << endl;
			outfile << minIdx[i] << endl;
		}
		else
		{
			cout << minIdx[i] << ' ';
			outfile << minIdx[i] << ' ';
		}
	}

	outfile.close();

	// end
	return 0;
}