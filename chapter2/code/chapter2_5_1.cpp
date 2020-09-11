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

const char dataFileName[30] = "dataset_369253_3.txt";
const char dataFilePath[40] = "E:/GitHub/yizhou-zhong/chapter2/data/";
const char outputFileName[20] = "chapter2_5_1.txt";

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
	vector<vector<double>> probMat;
	
	vector<int> dataSep;
	for (int i = 0; i < len; i++)
	{
		if (fileData[i] == '\n' || fileData[i] == ' ')
		{
			dataSep.push_back(i);
		}
	}

	Text = string(fileData, dataSep[0]);
	k = stoi(string(fileData + dataSep[0] + 1, dataSep[1] - dataSep[0] - 1));
	
	for (int i = 0; i < 4; i++)
	{
		vector<double> probRow(k, 0);
		for (int j = 0; j < k; j++)
		{
			int idx = i*k + j;
			probRow[j] = stod(string(fileData + dataSep[idx + 1] + 1, 
				dataSep[idx + 2] - dataSep[idx+1] - 1));
		}
		probMat.push_back(probRow);
	}
	
	dataSep.clear();
	dataSep.shrink_to_fit();
	free(fileData);

	// operation
	string profileMostKmer = FindProfileMost(&Text, k, probMat);

	// output file
	char outputFullName[100];
	strcpy(outputFullName, dataFilePath);
	strcat(outputFullName, outputFileName);

	ofstream outfile(outputFullName);

	cout << profileMostKmer << endl;
	outfile << profileMostKmer << endl;

	outfile.close();

	system("pause");
	// end
	return 0;
}