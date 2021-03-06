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

const char dataFileName[30] = "dataset_369268_10.txt";
const char dataFilePath[40] = "E:/GitHub/yizhou-zhong/chapter3/data/";
const char outputFileName[20] = "chapter3_3_2.txt";

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
	vector<int> dataSep;
	for (int i = 0; i < len; i++)
	{
		if (fileData[i] == '\n' || fileData[i] == ' ')
		{
			dataSep.push_back(i);
		}
	}
	int lenPattern = dataSep.size();

	vector<string> patternStrs;

	patternStrs.push_back(string(fileData, dataSep[0]));
	for (int i = 0; i < lenPattern - 1; i++)
	{
		patternStrs.push_back(string(fileData + dataSep[i] + 1, dataSep[i + 1] - dataSep[i] - 1));
	}
	
	dataSep.clear();
	dataSep.shrink_to_fit();
	free(fileData);

	// operation
	NodeMappingChart adjMat = OverlapGraph(&patternStrs);

	// output file
	char outputFullName[100];
	strcpy(outputFullName, dataFilePath);
	strcat(outputFullName, outputFileName);

	ofstream outfile(outputFullName);

	int matSize = adjMat.size();
	for (int i = 0; i < matSize; i++)
	{
		bool adjexist = false;
		for (int j = 0; j < matSize; j++)
		{
			if (adjMat[i][j])
			{
				if (!adjexist)
				{
					outfile << patternStrs[i] << "->";
					outfile << patternStrs[j];
					adjexist = true;
				}
				else
				{
					outfile << ',' << patternStrs[j];
				}
			}
		}
		if (adjexist)
		{
			outfile << endl;
		}
	}

	outfile.close();
	system("pause");

	// end
	return 0;
}