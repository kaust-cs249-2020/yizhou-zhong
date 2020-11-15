#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

typedef map<string, int> StrFreqTable;
typedef vector<pair<int, int>> GraphEdgeChart;
typedef vector<pair<int, int>> NodeDegreeChart;
typedef vector<pair<string, string>> PairedReadsChart;
typedef vector<vector<bool>> NodeMappingChart;
typedef map<string, string> GeneticCodeTable;
typedef map<char, int> IntegerMassTable;
typedef vector< pair<int, int> > CountTable;
typedef pair<int, int> PAIR;
typedef map<int, int> NodeWeightMap;
struct PATH
{
	int nextNode;
	vector<int> nodeList;
	int costSum;
};

struct cmp
{
	bool operator() (const PAIR& P1, const PAIR& P2)
	{
		return P1.second > P2.second;
	}
};

struct pathcmp
{
	bool operator() (const PATH& P1, const PATH& P2)
	{
		return P1.nextNode > P2.nextNode;
	}
};

struct DMAT
{
	vector<vector<float>> mat;
	vector<int> index;
};

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

vector<string> CyclopeptideSequencing(vector<int> specInt, IntegerMassTable* massTable);

int Score(string peptide, vector<int> specInt, IntegerMassTable* massTable);

int LinearScore(string peptide, vector<int> specInt, IntegerMassTable* massTable);

vector<string> Trim(vector<string> leaderboard, vector<int> specInt, int N, IntegerMassTable* massTable);

string LeaderboardCyclopeptideSequencing(vector<int> specInt, int N, IntegerMassTable* massTable);

string LeaderboardCyclopeptideSequencing(vector<int> specInt,
	int N, IntegerMassTable* massTable,
	const vector<int> aminoList = vector<int>());

string  ConvolutionCycPepSeq(int M, int N, vector<int> specInt, IntegerMassTable* massTable);

int DPChange(int money, vector<int> coins);

int ManhattanTourist(int n, int m, vector<vector<int>> d, vector<vector<int>> r);

string LongestComSubSeq(string s, string t);

bool Belong2PepValues(int pep, vector<int> pepValues, int& idx);

vector<int>  TopologicalOrdering(vector<int> nodes, CountTable adjList);

vector<int> LongestPathinDag(int graphStartNode, int graphEndNode,
	vector<int> nodes, vector<int> weightList, CountTable adjList, int& longestPathLen);

vector<string> GlobalAlignProblem(string strV, string strW,
	string scoringChar, vector<vector<int>> scoringMat, int sigma, int& scoreMax);

vector<string> LoaclAlignProblem(string strV, string strW,
	string scoringChar, vector<vector<int>> scoringMat, int sigma, int& scoreMax);

int EditDistanceProblem(string strV, string strW);

vector<string> FittingAlignmentProblem(string strV, string strW, int& highestScore);

vector<string> OverlapAlignmentProblem(string strV, string strW, int& highestScore);

vector<string> AffineGapPenaltiesProblem(string strV, string strW,
	string scoringChar, vector<vector<int>> scoringMat, int& scoreMax);

vector<string> MultipleLstCommonSubseqProblem(string strV, string strW, string strU, int& scoreMax);

vector<PAIR> MidEdgeLinearSpaceProblem(string strV, string strW,
	string scoringChar, vector<vector<int>> scoringMat, int sigma);

vector<string> LinearSpaceAlignment(string strV, string strW,
	string scoringChar, vector<vector<int>> scoringMat,
	int sigma, int& score);

string SequenceFormat(vector<int> p);

vector<string>  GreedySorting(vector<int> p, int& dist);

int NumberOfBreakpoints(vector<int> p);

vector<int> ChromosomeToCycle(vector<int> chromosome);

vector<int>  CycleToChromosome(vector<int> nodes);

vector<PAIR> ColoredEdges(vector<vector<int>> genome);

vector<vector<int>> GraphToGenome(vector<PAIR> edges);

int TwoBreakDistance(vector<vector<int>> genoP, vector<vector<int>> genoQ);

vector<PAIR> TwoBreakOnGenomeGraph(vector<PAIR> genomeEdges, 
	int i1, int i2, int i3, int i4);

vector<vector<int>> TwoBreakOnGenome(vector<vector<int>> genome,
	int i1, int i2, int i3, int i4);

vector<vector<vector<int>>> TwoBreakSorting(vector<vector<int>> genoP, vector<vector<int>> genoQ);

vector<PAIR> SharedKmersProblem(int k, string seq1, string seq2);

vector<vector<int>> DistanceBetweenLeaves(int n, vector<int> nodes, vector<int> weightList, CountTable adjList);

int LimbLengthProblem(int n, int j, vector<vector<int>> disMat);

vector<string> AdditivePhylogenyProblem(int innerStart, vector<vector<int>> disMat);

vector<string> UPGMA(int n, vector<vector<int>> disMat);

vector<string> NeighborJoiningProblem(int n, vector<vector<int>> disMat);

vector<string> SmallParsimony(int n, vector<string> treeString);
#endif