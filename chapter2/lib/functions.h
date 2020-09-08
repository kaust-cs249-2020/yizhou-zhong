#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string.h>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

int PatternCount(string* Text, string Pattern);

map<string, int> FrequencyTable(string* Text, int k);

string TeverseComplement(string* Text);

vector<int> PatternMatching(string* Text, string patternStr);

vector<string> ClumpFinding(string* Text, int k, int L, int t);

vector<int> SkewDiagram(string* Text);

int HammingDistance(string* Pattern, string* Pattern2);

int ApproximatePatternCount(string* Text, string Pattern, int d);

vector<string> FrequentWordsWithMismatches(string* Text, int k, int d);

vector<string> FrequentWordsWithMismatchesAndReverse(string* Text, int k, int d);

vector<string> MotifEnumeration(vector<string>* DNA, int k, int d);

string MedianString(vector<string>* Dna, int k);

string FindProfileMost(string* Text, int k, vector<vector<double>> probMat);

vector<string> GreedyMotifSearch(vector<string>* DNA, int k, int t);

vector<string> RandomizedMotifSearch(vector<string>* DNA, int k, int t, int itertimes);
#endif