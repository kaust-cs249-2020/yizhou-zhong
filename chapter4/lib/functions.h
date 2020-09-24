#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string.h>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

typedef map<string, int> StrFreqTable;
typedef vector<pair<int, int>> GraphEdgeChart;
typedef vector<pair<int, int>> NodeDegreeChart;
typedef vector<pair<string, string>> PairedReadsChart;
typedef vector<vector<bool>> NodeMappingChart;
typedef map<string, string> GeneticCodeTable;
typedef map<char, int> IntegerMassTable;

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

vector<string> Composition(string* Text, int k);

string Reconstruct(vector<string>* patternStrs);

NodeMappingChart OverlapGraph(vector<string>* patternStrs);

NodeMappingChart DeBruijn(string* Text, int k, vector<string>* patternStrs);

NodeMappingChart DeBruijn(string* Text, int k,
	vector<string>* patternStrs, vector<string>* patternStrsNoRepeat);

NodeMappingChart deBruijnGraphPatterns(vector<string>* kmersPatterns,
	vector<string>* patternStrs, vector<string>* patternStrsNoRepeat);

vector<int> EulerianCycle(NodeMappingChart* nodeRoute);

vector<int> EulerianPath(NodeMappingChart* nodeRoute);

string StringReconstruction(vector<string>* Patterns);

vector<string> GetKmersPatterns(int k);

string StringReconstructionByPairedReads(int k, int d, PairedReadsChart* pairedReads);

vector<string> ContigGeneration(vector<string>* Pattens);

string ProteinTranslation(string rnaStr, GeneticCodeTable* codeTable);

vector<string> PeptideEncoding(string dnaStr, string peptide, GeneticCodeTable* codeTable);

vector<int> LinearSpectrum(string peptide, IntegerMassTable* massTable);

vector<int> TheoreticalSpectrum(string peptide, IntegerMassTable* massTable);
#endif