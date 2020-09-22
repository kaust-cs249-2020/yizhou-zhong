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

const char dataFileName[30] = "dataset_369269_6.txt";
const char dataFilePath[40] = "E:/GitHub/yizhou-zhong/chapter3/data/";
const char outputFileName[20] = "chapter3_4_1.txt";

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
	//int lenPattern = dataSep.size();
	
	int k;
	string Text;
	k = stoi(string(fileData, dataSep[0]));
	Text = string(fileData + dataSep[0] + 1, dataSep[1] - dataSep[0] - 1);
	
	dataSep.clear();
	dataSep.shrink_to_fit();
	free(fileData);

	// operation
	vector<string> patternStrs;
	vector<string> patternStrsNoRepeat;
	NodeMappingChart adjMat = DeBruijn(&Text, k, &patternStrs, &patternStrsNoRepeat);

	// output file
	char outputFullName[100];
	strcpy(outputFullName, dataFilePath);
	strcat(outputFullName, outputFileName);

	ofstream outfile(outputFullName);

	int matY = adjMat.size();
	int matX;
	if (matY > 0)
	{
		matX = adjMat[0].size();
	}
	 
	for (int i = 0; i < matY; i++)
	{
		bool adjexist = false;
		for (int j = 0; j < matX; j++)
		{
			if (adjMat[i][j])
			{
				if (!adjexist)
				{
					outfile << patternStrsNoRepeat[i] << "->";
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