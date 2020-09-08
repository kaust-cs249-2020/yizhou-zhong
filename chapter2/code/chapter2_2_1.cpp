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

const char dataFileName[30] = "dataset_369250_8.txt";
const char dataFilePath[40] = "E:/GitHub/yizhou-zhong/chapter2/data/";
const char outputFileName[20] = "chapter2_2_1.txt";

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
	vector<string> DNA;
	int k, d;
	
	vector<int> dataSep;
	for (int i = 0; i < len; i++)
	{
		if (fileData[i] == '\n' || fileData[i] == ' ')
		{
			dataSep.push_back(i);
		}
	}

	int lenDNA = dataSep.size() - 2;

	k = stoi(string(fileData, dataSep[0]));
	d = stoi(string(fileData + dataSep[0] + 1, dataSep[1] - dataSep[0] - 1));
	for (int i = 0; i < lenDNA; i++)
	{
		DNA.push_back(string(fileData + dataSep[i+1] + 1, dataSep[i+2] - dataSep[i+1] - 1));
	}
	
	dataSep.clear();
	dataSep.shrink_to_fit();
	free(fileData);

	// operation
	vector<string> motifsDna = MotifEnumeration(&DNA, k, d);
	DNA.clear();
	DNA.shrink_to_fit();

	// output file
	char outputFullName[100];
	strcpy(outputFullName, dataFilePath);
	strcat(outputFullName, outputFileName);

	ofstream outfile(outputFullName);

	for (int i = 0; i < motifsDna.size(); i++)
	{
		if (i == motifsDna.size() - 1)
		{
			cout << motifsDna[i] << endl;
			outfile << motifsDna[i] << endl;
		}
		else
		{
			cout << motifsDna[i] << ' ';
			outfile << motifsDna[i] << ' ';
		}
	}

	outfile.close();
	motifsDna.clear();
	motifsDna.shrink_to_fit();

	// end
	return 0;
}