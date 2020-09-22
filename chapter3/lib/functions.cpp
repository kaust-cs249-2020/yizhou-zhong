#include "functions.h"
#include "mathtool.h"
#include <cstdlib>
#include <iostream>

int PatternCount(string* Text, string Pattern)
{
	int pCount = 0;
	int textLen = Text->length();
	int patternLen = Pattern.length();
	for (int i = 0; i < textLen - patternLen + 1; i++)
	{
		string comPattern = Text->substr(i, patternLen);
		if (strcmp(comPattern.c_str(), Pattern.c_str()) == 0)
		{
			pCount++;
		}
	}
	return pCount;
}

map<string, int> FrequencyTable(string* Text, int k)
{
	int n = Text->length();
	map<string, int> freMap;
	map<string, int>::iterator freMapIte;

	for (int i = 0; i < n - k + 1; i++)
	{
		string patternStr = Text->substr(i, k);
		freMapIte = freMap.find(patternStr);
		if (freMapIte != freMap.end())
		{// find the same key
			(freMapIte->second)++;
		}
		else
		{// no same key
			freMap.insert(pair<string, int>(patternStr, 1));
		}
		/*
		bool patFlag = false;
		for (freMapIte = freMap.begin(); freMapIte != freMap.end(); freMapIte++)
		{
			if (strcmp(freMapIte->first.c_str(), patternStr.c_str()) == 0)
			{
				patFlag = true;
				break;
			}
		}
		if (patFlag)
		{
			(freMapIte->second)++;
		}
		else
		{
			freMap.insert(pair<string, int>(patternStr, 1));
		}
		*/
	}
	return freMap;
}

string TeverseComplement(string* Text)
{
	int n = Text->length();
	string outPut(n, ' ');
	for (int i = n - 1; i >= 0; i--)
	{
		switch (Text->at(i))
		{
		case 'A':
			outPut[n - 1 - i] = 'T';
			break;
		case 'T':
			outPut[n - 1 - i] = 'A';
			break;
		case 'G':
			outPut[n - 1 - i] = 'C';
			break;
		default:
			outPut[n - 1 - i] = 'G';	
		}
	}
	return outPut;
}

vector<int> PatternMatching(string* Text, string patternStr)
{
	vector<int> patternIdx;
	int tLen = Text->length();
	int pLen = patternStr.length();
	for (int i = 0; i < tLen - pLen + 1; i++)
	{
		string comPattern = Text->substr(i, pLen);
		if (strcmp(comPattern.c_str(), patternStr.c_str()) == 0)
		{
			patternIdx.push_back(i);
		}
	}
	return patternIdx;
}

vector<string> ClumpFinding(string* Text, int k, int L, int t)
{
	vector<string> outputPatterns;
	
	int n = Text->length();
	for (int i = 0; i < n - L + 1; i++)
	{
		string window = Text->substr(i, L);
		map<string, int> freqMap = FrequencyTable(&window, k);
		map<string, int>::iterator iterFreMap;
		for (iterFreMap = freqMap.begin(); iterFreMap != freqMap.end(); iterFreMap++)
		{
			if (iterFreMap->second >= t)
			{
				bool dupFlag = false;
				for (int m = 0; m < outputPatterns.size(); m++)
				{
					if (strcmp(outputPatterns[m].c_str(), (iterFreMap->first).c_str()) == 0)
					{
						dupFlag = true;
						break;
					}
				}
				if (!dupFlag)
				{
					outputPatterns.push_back(iterFreMap->first);
				}
			}
		}
	}
	return outputPatterns;
}

vector<int> SkewDiagram(string* Text)
{
	int n = Text->length();
	vector<int> skewSeq(1, 0);
	int skew = 0;
	for (int i = 0; i < n; i++)
	{
		switch (Text->at(i))
		{
		case 'C':
			skew--;
			break;
		case 'G':
			skew++;
			break;
		default:
			break;
		}
		skewSeq.push_back(skew);
	}
	return skewSeq;
}

int HammingDistance(string* Pattern, string* Pattern2)
{
	int hamdis = 0;
	int n = Pattern->length();
	for (int i = 0; i < n; i++)
	{
		if (Pattern->at(i) == Pattern2->at(i))
		{
		}
		else
		{
			hamdis++;
		}
	}
	return hamdis;
}

int ApproximatePatternCount(string* Text, string Pattern, int d)
{
	int k = Pattern.length();
	int n = Text->length();
	int approxCount = 0;

	for (int i = 0; i < n - k + 1; i++)
	{
		if (HammingDistance(&Text->substr(i, k), &Pattern) <= d)
		{
			approxCount++;
		}
	}
	return approxCount;
}

vector<string> Neighbors(string Pattern, int d)
{
	vector<string> neighborpatterns;
	if (d == 0)
	{
		neighborpatterns = vector<string>(1, Pattern);
		return neighborpatterns;
	}
	if (Pattern.length() == 1)
	{
		neighborpatterns = vector<string>{string(1, 'A'),
			string(1, 'C'), 
			string(1, 'G'), 
			string(1, 'T')};
		return neighborpatterns;
	}
	string suffixPattern = Pattern.substr(1, Pattern.length() - 1);
	vector<string> suffixneighbors = Neighbors(suffixPattern, d);
	for (int i = 0; i < suffixneighbors.size(); i++)
	{
		if (HammingDistance(&suffixPattern, &suffixneighbors[i]) < d)
		{
			neighborpatterns.push_back(string(1, 'A') + suffixneighbors[i]);
			neighborpatterns.push_back(string(1, 'T') + suffixneighbors[i]);
			neighborpatterns.push_back(string(1, 'G') + suffixneighbors[i]);
			neighborpatterns.push_back(string(1, 'C') + suffixneighbors[i]);
		}
		else
		{
			neighborpatterns.push_back(Pattern.at(0) + suffixneighbors[i]);
		}
	}
	return neighborpatterns;
}

vector<string> FrequentWordsWithMismatches(string* Text, int k, int d)
{
	vector<string> Patterns;
	map<string, int> freqMap;
	map<string, int>::iterator iterFreqMap;
	int n = Text->length();
	for (int i = 0; i < n - k + 1; i++)
	{
		string Pattern = Text->substr(i, k);
		vector<string> neighborhood = Neighbors(Pattern, d);
		for (int j = 0; j < neighborhood.size(); j++)
		{
			string neighbor = neighborhood[j];
			iterFreqMap = freqMap.find(neighbor);
			if (iterFreqMap == freqMap.end())
			{
				freqMap.insert(pair<string, int>(neighbor, 1));
			}
			else
			{
				(iterFreqMap->second)++;
			}
		}
	}
	int maxValue = 0;
	for (iterFreqMap = freqMap.begin(); iterFreqMap != freqMap.end(); iterFreqMap++)
	{
		if (iterFreqMap->second > maxValue)
		{
			maxValue = iterFreqMap->second;
		}
	}
	for (iterFreqMap = freqMap.begin(); iterFreqMap != freqMap.end(); iterFreqMap++)
	{
		if (iterFreqMap->second == maxValue)
		{
			Patterns.push_back(iterFreqMap->first);
		}
	}
	return Patterns;
}

vector<string> FrequentWordsWithMismatchesAndReverse(string* Text, int k, int d)
{
	vector<string> Patterns;
	map<string, int> freqMap;
	map<string, int>::iterator iterFreqMap;
	int n = Text->length();

	for (int i = 0; i < n-k+1; i++)
	{
		string patternStr = Text->substr(0, k);
		vector<string> neighborhood = Neighbors(patternStr, d);

		for (int j = 0; j < neighborhood.size(); j++)
		{
			string neighbor = neighborhood[j];
			iterFreqMap = freqMap.find(neighbor);
			if (iterFreqMap == freqMap.end())
			{
				int approxCount = ApproximatePatternCount(Text, neighbor, d) +
					ApproximatePatternCount(Text, TeverseComplement(&neighbor), d);
				freqMap.insert(pair<string, int>(neighbor, approxCount));
			}
		}
	}

	int maxValue = 0;
	for (iterFreqMap = freqMap.begin(); iterFreqMap != freqMap.end(); iterFreqMap++)
	{
		if (iterFreqMap->second > maxValue)
		{
			maxValue = iterFreqMap->second;
		}
	}
	for (iterFreqMap = freqMap.begin(); iterFreqMap != freqMap.end(); iterFreqMap++)
	{
		if (iterFreqMap->second == maxValue)
		{
			Patterns.push_back(iterFreqMap->first);
		}
	}
	return Patterns;
}

vector<string> MotifEnumeration(vector<string>* DNA, int k, int d)
{
	
	vector<string> outputPattern;
	
	if (DNA->size() > 0)
	{
		int dnaLen = DNA->size();
		int strLen = (*DNA)[0].length();
		// find all the kmers into potentialPattern
		vector<string> potentialPattern;
		for (int i = 0; i < dnaLen; i++)
		{
			for (int j = 0; j < strLen - k + 1; j++)
			{
				string kmer = (*DNA)[i].substr(j, k);
				bool existFlag = false;
				for (int m = 0; m < potentialPattern.size(); m++)
				{
					if (strcmp(kmer.c_str(), potentialPattern[m].c_str()) == 0)
					{
						existFlag = true;
						break;
					}
				}
				if (!existFlag)
				{
					potentialPattern.push_back(kmer);
				}
			}
		}

		// find all the patten' of each kmers with d-distance
		vector<string> potentialNeighborhoods = potentialPattern;
		for (int i = 0; i < potentialPattern.size(); i++)
		{
			vector<string> neighborhoods = Neighbors(potentialPattern[i], d);
			for (int j = 0; j < neighborhoods.size(); j++)
			{
				bool existFlag = false;
				for (int m = 0; m < potentialNeighborhoods.size(); m++)
				{
					if (strcmp(neighborhoods[j].c_str(), 
						potentialNeighborhoods[m].c_str()) == 0)
					{
						existFlag = true;
						break;
					}
				}
				if (!existFlag)
				{
					potentialNeighborhoods.push_back(neighborhoods[j]);
				}
			}
		}
		potentialPattern.clear();
		potentialPattern.shrink_to_fit();
		
		// does potentialNeighborhoods pattern exist in DNA
		for (int i = 0; i < potentialNeighborhoods.size(); i++)
		{
			bool inDNAFlag = true;
			for (int j = 0; j < DNA->size(); j++)
			{
				int approxCount = ApproximatePatternCount(&(*DNA)[j], potentialNeighborhoods[i], d);
				if (approxCount == 0)
				{
					inDNAFlag = false;
					break;
				}
			}
			if (inDNAFlag)
			{
				outputPattern.push_back(potentialNeighborhoods[i]);
			}
		}
		potentialNeighborhoods.clear();
		potentialNeighborhoods.shrink_to_fit();
	}

	return outputPattern;
}

vector<string> AllkmerPattern(int k)
{
	vector<string> allkmerPat;
	if (k <= 0)
	{
		return allkmerPat;
	}
	if (k == 1)
	{
		allkmerPat = vector < string > {string(1, 'A'),
			string(1, 'C'),
			string(1, 'G'),
			string(1, 'T')};
		return allkmerPat;
	}
	else
	{
		vector<string> lastAllkmerPat = AllkmerPattern(k - 1);
		int lenLast = lastAllkmerPat.size();
		for (int i = 0; i < lenLast; i++)
		{
			allkmerPat.push_back(string(1, 'A') + lastAllkmerPat[i]);
			allkmerPat.push_back(string(1, 'C') + lastAllkmerPat[i]);
			allkmerPat.push_back(string(1, 'G') + lastAllkmerPat[i]);
			allkmerPat.push_back(string(1, 'T') + lastAllkmerPat[i]);
		}
		return allkmerPat;
	}
}

int MinHammingDis(string* pattern, string* Text)
{
	int lenP = pattern->length();
	int lenT = Text->length();
	int minHammDis = INT_MAX;
	for (int i = 0; i < lenT - lenP + 1; i++)
	{
		int hammDis = HammingDistance(pattern, &Text->substr(i, lenP));
		if (hammDis < minHammDis)
		{
			minHammDis = hammDis;
		}
	}
	return minHammDis;
}

int Pattern2DnaDistance(string* pattern, vector<string>* Dna)
{
	int p2d = 0;
	int lenDna = Dna->size();
	for (int i = 0; i < lenDna; i++)
	{
		p2d += MinHammingDis(pattern, &(*Dna)[i]);
	}
	return p2d;
}

string MedianString(vector<string>* Dna, int k)
{
	int distance = INT_MAX;
	string median;
	vector<string> allkmer = AllkmerPattern(k);
	int lenAllkmer = allkmer.size();
	for (int i = 0; i < lenAllkmer; i++)
	{
		int p2d = Pattern2DnaDistance(&allkmer[i], Dna);
		if (distance > p2d)
		{
			distance = p2d;
			median = allkmer[i];
		}
	}
	return median;
}

bool Belong2Patterns(string Pattern, vector<string> Patterns)
{
	bool belongFlag = false;
	for (int i = 0; i < Patterns.size(); i++)
	{
		if (strcmp(Patterns[i].c_str(), Pattern.c_str()) == 0)
		{
			belongFlag = true;
			break;
		}
	}
	return belongFlag;
}

bool Belong2Patterns(string Pattern, vector<string> Patterns, int& idx)
{
	bool belongFlag = false;
	for (int i = 0; i < Patterns.size(); i++)
	{
		if (strcmp(Patterns[i].c_str(), Pattern.c_str()) == 0)
		{
			belongFlag = true;
			idx = i;
			break;
		}
	}
	return belongFlag;
}

string FindProfileMost(string* Text, int k, vector<vector<double>> probMat)
{
	vector<string> kmerPatterns;
	int lenText = Text->length();
	// find all k-mers
	for (int i = 0; i < lenText - k + 1;i++)
	{
		string subString = Text->substr(i, k);
		if (!Belong2Patterns(subString, kmerPatterns))
		{
			kmerPatterns.push_back(subString);
		}
	}
	// cal probability of each kmer;
	double maxProb=-1;
	int maxPronIdx;
	for (int i = 0; i < kmerPatterns.size(); i++)
	{
		double kmerProb = 1;
		for (int j = 0; j < k; j++)
		{
			int nucIdx;
			switch (kmerPatterns[i].at(j))
			{
			case 'A':
				nucIdx = 0;
				break;
			case 'C':
				nucIdx = 1;
				break;
			case 'G':
				nucIdx = 2;
				break;
			default:
				nucIdx = 3;
			}
			kmerProb *= probMat[nucIdx][j];
		}
		////
		//if (showcout && strcmp(kmerPatterns[i].c_str(), "AGTAATATGTAC") == 0)
		//{
		//	cout << "AGTAATATGTAC " << kmerProb << endl;
		//}
		//if (showcout && strcmp(kmerPatterns[i].c_str(), "TACAGGTAGATA") == 0)
		//{
		//	cout << "TACAGGTAGATA " << kmerProb << endl;
		//}
		////
		if (kmerProb > maxProb)
		{
			maxProb = kmerProb;
			maxPronIdx = i;
		}
	}
	// return the profile max prob string
	return kmerPatterns[maxPronIdx];
}

vector < vector<double>> GetProfile(vector<string> motifs)
{
	int lenM = motifs.size();
	int lenS = motifs[0].length();
	vector < vector<double>> profileMat(4, vector<double>(lenS, 0));
	for (int i = 0; i < lenS; i++)
	{
		int Anum = 0, Cnum = 0, Gnum = 0, Tnum = 0;
		for (int j = 0; j < lenM; j++)
		{
			switch (motifs[j].at(i))
			{
			case 'A':
				Anum++;
				break;
			case 'C':
				Cnum++;
				break;
			case 'G':
				Gnum++;
				break;
			default:
				Tnum++;
			}
		}
		profileMat[0][i] = 1.0*Anum / (lenM*1.0);
		profileMat[1][i] = 1.0*Cnum / (lenM*1.0);
		profileMat[2][i] = 1.0*Gnum / (lenM*1.0);
		profileMat[3][i] = 1.0*Tnum / (lenM*1.0);
	}
	return profileMat;
}

vector < vector<double>> GetLaplaceRuleProfile(vector<string> motifs)
{
	int lenM = motifs.size();
	int lenS = motifs[0].length();
	vector < vector<double>> profileMat(4, vector<double>(lenS, 0));
	for (int i = 0; i < lenS; i++)
	{
		int Anum = 1, Cnum = 1, Gnum = 1, Tnum = 1;
		for (int j = 0; j < lenM; j++)
		{
			switch (motifs[j].at(i))
			{
			case 'A':
				Anum++;
				break;
			case 'C':
				Cnum++;
				break;
			case 'G':
				Gnum++;
				break;
			default:
				Tnum++;
			}
		}
		profileMat[0][i] = 1.0*Anum / (lenM+4);
		profileMat[1][i] = 1.0*Cnum / (lenM+4);
		profileMat[2][i] = 1.0*Gnum / (lenM+4);
		profileMat[3][i] = 1.0*Tnum / (lenM+4);
	}
	return profileMat;
}

int MotifScore(vector<string> motifs)
{
	int lenT = motifs.size();
	int lenS = motifs[0].length();
	int score = 0;
	for (int i = 0; i < lenS; i++)
	{
		vector<int> nucNum(4, 0);
		for (int j = 0; j < lenT; j++)
		{
			switch (motifs[j].at(i))
			{
			case 'A':
				nucNum[0]++;
				break;
			case 'C':
				nucNum[1]++;
				break;
			case 'G':
				nucNum[2]++;
				break;
			default:
				nucNum[3]++;
			}
		}
		score += (lenT - findMax(nucNum, 4));
	}
	return score;
}

vector<string> GreedyMotifSearch(vector<string>* DNA, int k, int t)
{
	// initial the BestMotifs
	vector<string> BestMotifs;
	for (int i = 0; i < DNA->size(); i++)
	{
		BestMotifs.push_back((*DNA)[i].substr(0, k));
	}
	// find all the k-mer motif in first row
	int lenText = (*DNA)[0].length();
	vector<string> firstKmers;
	for (int i = 0; i < lenText - k + 1; i++)
	{
		string kmer = (*DNA)[0].substr(i, k);
		if (!Belong2Patterns(kmer, firstKmers))
		{
			firstKmers.push_back(kmer);
		}
	}
	// find the best motifs
	for (int i = 0; i < firstKmers.size(); i++)
	{	
		string kmer = firstKmers[i];
		vector<string> motifs(t, kmer);
		/*vector<string> motifs = BestMotifs;
		motifs[0] = kmer;*/

		for (int j = 1; j < DNA->size(); j++)
		{
			// vector<vector<double>> motifProfile = GetProfile(motifs);
			vector<vector<double>> motifProfile = GetLaplaceRuleProfile(motifs);
			//if (i == 143 && j == 6)
			//{
			//	// cout << "i j:" << i << ' ' << j << ' ' << motifs[j].c_str() << endl;
			//	showcout = true;
			//	cout << "motifs:" << endl;
			//	for (int m = 0; m < motifs.size(); m++)
			//	{
			//		cout << motifs[m].c_str() << endl;
			//	}
			//	for (int p = 0; p < motifProfile.size(); p++)
			//	{
			//		for (int q = 0; q < motifProfile[0].size(); q++)
			//		{
			//			cout << motifProfile[p][q] << ' ';
			//		}
			//		cout << endl;
			//	}
			//}
			motifs[j] = FindProfileMost(&(*DNA)[j], k, motifProfile);
			//showcout = false;
		}
		if (MotifScore(motifs) < MotifScore(BestMotifs))
		{
			BestMotifs = motifs;
		}
	}
	return BestMotifs;
}

// rand int from [a, b]: (rand() % (b - a + 1)) + a 
int RandIdx(int a, int b)
{
	return (rand() % (b - a + 1)) + a;
}

vector<string> FindProfileMotifs(vector<string>* DNA, int k, vector<vector<double>> probMat)
{
	vector<string> profileMotifs;
	int t = DNA->size();

	for (int i = 0; i < t; i++)
	{
		profileMotifs.push_back(FindProfileMost(&(*DNA)[i], k, probMat));
	}
	return profileMotifs;
}

vector<string> RandomizedMotifSearch(vector<string>* DNA, int k, int t, int itertimes)
{
	vector<string> bestMotifs, motifs;
	int lenS = (*DNA)[0].length();
	for (int i = 0; i < t; i++)
	{
		motifs.push_back((*DNA)[i].substr(RandIdx(0, lenS - k), k));
	}
	bestMotifs = motifs;

	for (int j = 0; j < itertimes; j++)
	{
		if (j != 0)
		{
			for (int n = 0; n < t; n++)
			{
				motifs[n] = (*DNA)[n].substr(RandIdx(0, lenS - k), k);
			}
		}

		vector<vector<double>> motifProfile;
		while (1)
		{
			motifProfile = GetLaplaceRuleProfile(motifs);
			motifs = FindProfileMotifs(DNA, k, motifProfile);
			if (MotifScore(motifs) < MotifScore(bestMotifs))
			{
				bestMotifs = motifs;
			}
			else
			{
				break;
			}
		}
	}
	return bestMotifs;
}

int CharValue(char letter)
{
	switch (letter)
	{
	case 'A':
		return 1;
	case 'C':
		return 2;
	case 'G':
		return 3;
	default:
		return 4;
	}
}

vector<string> Composition(string* Text, int k)
{
	int lenT = Text->length();
	vector<string> kmersCompositions;

	for (int i = 0; i < lenT -k+1; i++)
	{
		string patternStr = Text->substr(i, k);
		kmersCompositions.push_back(patternStr);
	}

	return kmersCompositions;
}

string Reconstruct(vector<string>* patternStrs)
{
	int lenP = patternStrs->size();
	int lenS = (*patternStrs)[0].length();
	string Text;

	if (lenP>0)
	{
		Text = (*patternStrs)[0];
	}

	for (int i = 1; i < lenP; i++)
	{
		Text.append(1, (*patternStrs)[i].at(lenS - 1));
	}

	return Text;
}

string Prefix(string Text)
{
	int lenT = Text.length();
	return Text.substr(0, lenT - 1);
}

string Suffix(string Text)
{
	int lenT = Text.length();
	return Text.substr(1, lenT - 1);
}

NodeMappingChart OverlapGraph(vector<string>* patternStrs)
{
	int patLen = patternStrs->size();
	NodeMappingChart adjMat(patLen, vector<bool>(patLen, false));

	for (int i = 0; i < patLen; i++)
	{
		for (int j = 0; j < patLen;j++)
		{
			if (i!=j)
			{
				if (
					strcmp(
					Suffix((*patternStrs)[i]).c_str(),
					Prefix((*patternStrs)[j]).c_str()
					) == 0
					)
				{
					adjMat[i][j] = true;
				}
			}
		}
	}

	return adjMat;
}

int FindPatternIdx(string patternStr, vector<string>* patterns)
{
	int len = patterns->size();
	for (int i = 0; i < len; i++)
	{
		if (
			strcmp(
			patternStr.c_str(), (*patterns)[i].c_str()
			)==0
			)
		{
			return i;
		}
	}
}

NodeMappingChart DeBruijn(string* Text, int k, 
	vector<string>* patternStrs, vector<string>* patternStrsNoRepeat)
{
	int b = k - 1;
	int lenT = Text->length();
	for (int i = 0; i < lenT - b + 1; i++)
	{
		string patStr = Text->substr(i, b);
		patternStrs->push_back(patStr);
		if (!Belong2Patterns(patStr, *patternStrsNoRepeat))
		{
			patternStrsNoRepeat->push_back(patStr);
		}
	}

	int patLen = patternStrs->size();
	int patLenNoRe = patternStrsNoRepeat->size();
	NodeMappingChart adjMat(patLenNoRe, vector<bool>(patLen, false));

	for (int i = 0; i < patLen; i++)
	{
		if (i > 0)
		{
			int j = FindPatternIdx((*patternStrs)[i - 1], patternStrsNoRepeat);
			adjMat[j][i] = true;
		}
	}

	/*for (int i = 0; i < patLenNoRe; i++)
	{
		for (int j = 0; j < patLen; j++)
		{
			if (i==8)
			{
				int a = 0;
			}
			if (
				strcmp(
				Suffix((*patternStrsNoRepeat)[i]).c_str(),
				Prefix((*patternStrs)[j]).c_str()
				) == 0
				)
				{
					adjMat[i][j] = true;
				}
		}
	}*/
	return adjMat;
}

NodeMappingChart deBruijnGraphPatterns(vector<string>* kmersPatterns,
	vector<string>* patternStrs, vector<string>* patternStrsNoRepeat)
{
	int lenS = kmersPatterns->size();
	int lenT = (*kmersPatterns)[0].length();

	NodeMappingChart adjMat;

	for (int i = 0; i < lenS; i++)
	{
		string kmerspattern = (*kmersPatterns)[i];
		string prePattern = kmerspattern.substr(0, lenT - 1);
		string sufPattern = kmerspattern.substr(1, lenT - 1);
		patternStrs->push_back(sufPattern);
		if (!Belong2Patterns(prePattern, *patternStrsNoRepeat))
		{
			patternStrsNoRepeat->push_back(prePattern);
			adjMat.push_back(vector<bool>(lenS, false));
		}
		int j = FindPatternIdx(prePattern, patternStrsNoRepeat);
		adjMat[j][i] = true;
	}

	return adjMat;
}

GraphEdgeChart deBruijnGraphPatterns(vector<string>* kmersPatterns,
	vector<string>* patternStrsNoRepeat)
{
	int lenS = kmersPatterns->size();
	int lenT = (*kmersPatterns)[0].length();

	GraphEdgeChart adjMat;

	cout << "Patten size: " << lenS << endl;

	for (int i = 0; i < lenS; i++)
	{
		cout << "deBruijnGraph steps: " << i << endl;
		string kmerspattern = (*kmersPatterns)[i];
		string prePattern = kmerspattern.substr(0, lenT - 1);
		string sufPattern = kmerspattern.substr(1, lenT - 1);

		int startIdx, endIdx;
		if (!Belong2Patterns(prePattern, *patternStrsNoRepeat, startIdx))
		{
			patternStrsNoRepeat->push_back(prePattern);
			startIdx = patternStrsNoRepeat->size() - 1;
		}
		if (!Belong2Patterns(sufPattern, *patternStrsNoRepeat, endIdx))
		{
			patternStrsNoRepeat->push_back(sufPattern);
			endIdx = patternStrsNoRepeat->size() - 1;
		}
		adjMat.push_back(pair<int, int>(startIdx, endIdx));
	}

	return adjMat;
}

bool UnexploredEdegs(NodeMappingChart nodeRoute)
{
	int nodeNum = nodeRoute.size();
	for (int i = 0; i < nodeNum; i++)
	{
		for (int j = 0; j < nodeNum; j++)
		{
			if (nodeRoute[i][j])
			{
				return true;
			}
		}
	}
	return false;
}

vector<int> EulerianCycle(NodeMappingChart* nodeRoute)
{
	vector<int> cycleRoute;
	NodeMappingChart updateRoute; 
	// form a cycle Cycle by randomly walking in Graph
	for (int i = 0; i < nodeRoute->size(); i++)
	{// start with the node of every row
		updateRoute = *nodeRoute;
		cycleRoute.push_back(i);

		int lastIdx = i;
		while (true)
		{
			bool nextNodeExist=false;
			for (int j = 0; j < updateRoute[lastIdx].size(); j++)
			{
				if (updateRoute[lastIdx][j])
				{
					updateRoute[lastIdx][j] = false;
					cycleRoute.push_back(j);
					lastIdx = j;
					nextNodeExist = true;
					break;
				}
			}
			// if no edge exists from this node, than break from while
			if (!nextNodeExist)
			{
				break;
			}
		}
		
		if (cycleRoute[0] == cycleRoute[cycleRoute.size()-1])
		{
			//cout << "First cycleRoute Size: " << cycleRoute.size() << endl;
			break;
		}
		else
		{
			cycleRoute.clear();
			cycleRoute.shrink_to_fit();
		}
	}

	// while there are unexplored edges in Graph
	while (UnexploredEdegs(updateRoute))
	{
		int nodeNum = updateRoute.size();
		int subStart;
		for (int i = 0; i < cycleRoute.size(); i++)
		{
			bool findExplore = false;
			for (int j = 0; j < nodeNum; j++)
			{
				if (updateRoute[cycleRoute[i]][j])
				{
					subStart = cycleRoute[i];
					findExplore = true;
					break;
				}
			}
			if (findExplore)
			{
				break;
			}
		}
		vector<int> subCycleRoute;
		subCycleRoute.push_back(subStart);
		int lastNode = subStart;
		while (true)
		{
			bool nextNodeExist = false;
			for (int j = 0; j < updateRoute[lastNode].size(); j++)
			{
				if (updateRoute[lastNode][j])
				{
					updateRoute[lastNode][j] = false;
					subCycleRoute.push_back(j);
					lastNode = j;
					nextNodeExist = true;
					break;
				}
			}
			// if no edge exists from this node, than break from while
			if (!nextNodeExist)
			{
				break;
			}
		}
		//form Cycle¡¯ by traversing Cycle (starting at newStart) and then randomly 
		//cout << "subCycleRoute size: " << subCycleRoute.size() << endl;
		//cout << "before cycleRoute size: " << cycleRoute.size() << endl;
		for (int i = 0; i < cycleRoute.size(); i++)
		{
			if (cycleRoute[i] == subStart)
			{
				for (int j = 1; j < subCycleRoute.size(); j++)
				{
					cycleRoute.insert(cycleRoute.begin() + i + j, subCycleRoute[j]);
				}
				break;
			}
		}
		//cout << "after cycleRoute size: " << cycleRoute.size() << endl;
	}

	return cycleRoute;
}

vector<int> EulerianPath(NodeMappingChart* nodeRoute)
{
	vector<int> cycleRoute;
	NodeMappingChart updateRoute;
	// find the start position in the graph
	int startPoint;
	bool findStartPoint;
	for (int i = 0; i < nodeRoute->size(); i++)
	{
		findStartPoint = true;
		for (int j = 0; j<nodeRoute->size();j++)
		{
			if ((*nodeRoute)[j][i])
			{
				findStartPoint = false;
				break;
			}
		}
		if (findStartPoint)
		{
			startPoint = i;
			break;
		}
	}
	// find the end point
	int endPoint;
	bool findEndPoint;
	for (int i = 0; i < nodeRoute->size(); i++)
	{
		findEndPoint = true;
		for (int j = 0; j < nodeRoute->size(); j++)
		{
			if ((*nodeRoute)[i][j])
			{
				findEndPoint = false;
				break;
			}
		}
		if (findEndPoint)
		{
			endPoint = i;
			break;
		}
	}

	int lastIdx;
	if (findStartPoint)
	{
		lastIdx = startPoint;
	}
	else if (findEndPoint)
	{
		for (int i = 0; i < nodeRoute->size(); i++)
		{
			if (i!=endPoint)
			{
				lastIdx = i;
			}
		}
	}
	else
	{
		lastIdx = 0;
	}

	// form the first path
	updateRoute = *nodeRoute;
	cycleRoute.push_back(lastIdx);
	
	while (true)
	{
		bool nextNodeExist = false;
		for (int j = 0; j < updateRoute[lastIdx].size(); j++)
		{
			if (updateRoute[lastIdx][j])
			{
				updateRoute[lastIdx][j] = false;
				cycleRoute.push_back(j);
				lastIdx = j;
				nextNodeExist = true;
				break;
			}
		}
		// if no edge exists from this node, than break from while
		if (!nextNodeExist)
		{
			break;
		}
	}

	// while there are unexplored edges in Graph
	while (UnexploredEdegs(updateRoute))
	{
		int nodeNum = updateRoute.size();
		int subStart;
		for (int i = 0; i < cycleRoute.size(); i++)
		{
			bool findExplore = false;
			for (int j = 0; j < nodeNum; j++)
			{
				if (updateRoute[cycleRoute[i]][j])
				{
					subStart = cycleRoute[i];
					findExplore = true;
					break;
				}
			}
			if (findExplore)
			{
				break;
			}
		}
		vector<int> subCycleRoute;
		subCycleRoute.push_back(subStart);
		int lastNode = subStart;
		while (true)
		{
			bool nextNodeExist = false;
			for (int j = 0; j < updateRoute[lastNode].size(); j++)
			{
				if (updateRoute[lastNode][j])
				{
					updateRoute[lastNode][j] = false;
					subCycleRoute.push_back(j);
					lastNode = j;
					nextNodeExist = true;
					break;
				}
			}
			// if no edge exists from this node, than break from while
			if (!nextNodeExist)
			{
				break;
			}
		}
		//form Cycle¡¯ by traversing Cycle (starting at newStart) and then randomly 
		cout << "subCycleRoute size: " << subCycleRoute.size() << endl;
		cout << "before cycleRoute size: " << cycleRoute.size() << endl;
		for (int i = 0; i < cycleRoute.size(); i++)
		{
			if (cycleRoute[i] == subStart)
			{
				for (int j = 1; j < subCycleRoute.size(); j++)
				{
					cycleRoute.insert(cycleRoute.begin() + i + j, subCycleRoute[j]);
				}
				break;
			}
		}
		cout << "after cycleRoute size: " << cycleRoute.size() << endl;
	}

	return cycleRoute;
}

string StringReconstruction(vector<string>* Patterns)
{
	string Text;
	vector<string> patternStrs, patternStrsNoRepeat;
	// dB ¡û DeBruijn(Patterns)
	NodeMappingChart dB = deBruijnGraphPatterns(Patterns, &patternStrs, &patternStrsNoRepeat);
	// matrix switch
	vector<string> nodeList;
	for (int i = 0; i < patternStrsNoRepeat.size(); i++)
	{
		if (!Belong2Patterns(patternStrsNoRepeat[i], nodeList))
		{
			nodeList.push_back(patternStrsNoRepeat[i]);
		}	
	}
	for(int j = 0; j < patternStrs.size(); j++)
	{
		if (!Belong2Patterns(patternStrs[j], nodeList))
		{
			nodeList.push_back(patternStrs[j]);
		}
	}
	NodeMappingChart nodeRoute(nodeList.size(), vector<bool>(nodeList.size(), false));
	int startIdx, endIdx;
	for (int i = 0; i < patternStrsNoRepeat.size(); i++)
	{
		startIdx = findPosition(nodeList, patternStrsNoRepeat[i]);
		for(int j = 0; j < patternStrs.size(); j++)
		{
			endIdx = findPosition(nodeList, patternStrs[j]);
			if (dB[i][j])
			{
				nodeRoute[startIdx][endIdx] = true;
			}
		}
	}
	// path ¡û EulerianPath(dB)
	vector<int> ePath = EulerianPath(&nodeRoute);
	// PathToGenome
	int k = 0;
	if (ePath.size() > 0)
	{
		Text.append(nodeList[ePath[0]]);
		k = nodeList[ePath[0]].length();
	}
	for (int i = 1; i < ePath.size(); i++)
	{
		Text.append(string(1, nodeList[ePath[i]].at(k-1)));
	}

	return Text;
}

vector<string> GetKmersPatterns(int k)
{
	vector<string> kmersPatterns;
	if (k<=0)
	{
		return kmersPatterns;
	}
	else if (k==1)
	{
		kmersPatterns.push_back("0");
		kmersPatterns.push_back("1");
		return kmersPatterns;
	}
	else
	{
		vector<string> preKmersPatterns = GetKmersPatterns(k-1);
		int n = preKmersPatterns.size();
		for (int i = 0; i < n; i++)
		{
			kmersPatterns.push_back(preKmersPatterns[i] + "0");
			kmersPatterns.push_back(preKmersPatterns[i] + "1");
		}
		return kmersPatterns;
	}
}

bool Belong2Pairs(pair<string, string>& Pattern, PairedReadsChart& Patterns, int& idx)
{
	bool belongFlag = false;
	for (int i = 0; i < Patterns.size(); i++)
	{
		if (strcmp(Patterns[i].first.c_str(), Pattern.first.c_str()) == 0
			&& strcmp(Patterns[i].second.c_str(), Pattern.second.c_str()) == 0
			)
		{
			belongFlag = true;
			idx = i;
			break;
		}
	}
	return belongFlag;
}

int FindPairIdx(pair<string, string> patternStr, PairedReadsChart* patterns)
{
	int len = patterns->size();
	for (int i = 0; i < len; i++)
	{
		if (
			strcmp(patternStr.first.c_str(), (*patterns)[i].first.c_str()) == 0
			&& strcmp(patternStr.second.c_str(), (*patterns)[i].second.c_str()) == 0
			)
		{
			return i;
		}
	}
}

GraphEdgeChart deBruijnGraphFromPairs(PairedReadsChart* readPairs, PairedReadsChart* pairStrsNoRepeat)
{
	int lenS = readPairs->size();
	int lenT = (*readPairs)[0].first.length();

	GraphEdgeChart adjMat;

	for (int i = 0; i < lenS; i++)
	{
		pair<string, string> kmerspair = (*readPairs)[i];
		pair<string, string> prepair = pair<string, string>(
			kmerspair.first.substr(0, lenT - 1),
			kmerspair.second.substr(0, lenT - 1)
			);
		pair<string, string> sufpair = pair<string, string>(
			kmerspair.first.substr(1, lenT - 1),
			kmerspair.second.substr(1, lenT - 1)
			);
		int startIdx, endIdx;

		if (!Belong2Pairs(prepair, *pairStrsNoRepeat, startIdx))
		{
			pairStrsNoRepeat->push_back(prepair);
			startIdx = pairStrsNoRepeat->size() - 1;
		}
		if (!Belong2Pairs(sufpair, *pairStrsNoRepeat, endIdx))
		{
			pairStrsNoRepeat->push_back(sufpair);
			endIdx = pairStrsNoRepeat->size() - 1;
		}
		adjMat.push_back(pair<int, int>(startIdx, endIdx));
	}

	return adjMat;
}

string StringReconstructionByPairedReads(int k, int d, PairedReadsChart* pairedReads)
{
	string Text;
	PairedReadsChart pairStrsNoRepeat;
	
	// dB ¡û DeBruijn(Patterns)
	GraphEdgeChart dB = deBruijnGraphFromPairs(pairedReads, &pairStrsNoRepeat);
	
	// matrix switch
	NodeMappingChart nodeRoute(pairStrsNoRepeat.size(), vector<bool>(pairStrsNoRepeat.size(), false));
	for (int i = 0; i < dB.size();i++)
	{
		nodeRoute[dB[i].first][dB[i].second] = true;
	}

	// path ¡û EulerianPath(dB)
	vector<int> ePath = EulerianPath(&nodeRoute);

	// PathToGenome
	if (ePath.size() > 0)
	{
		Text.append(pairStrsNoRepeat[ePath[0]].first);
	}
	for (int i = 1; i < ePath.size(); i++)
	{
		Text.append(string(1, pairStrsNoRepeat[ePath[i]].first.at(k - 2)));
	}
	for (int i = 0; i < d + 1;i++)
	{
		Text.append(string(1, pairStrsNoRepeat[ePath[ePath.size() - d - 2 + i]].second.at(0)));
	}
	Text.append(pairStrsNoRepeat[ePath[ePath.size() - 1]].second);

	return Text;
}

NodeDegreeChart GraphDegrees(GraphEdgeChart dB, int nodeNum)
{
	NodeDegreeChart degrees(nodeNum, pair<int, int>(0, 0));
	// pair.first is node indegree num, pair.second is outdegree num
	
	for(int i=0; i < dB.size(); i++)
	{
		degrees[dB[i].first].second += 1;
		degrees[dB[i].second].first += 1;
	}

	return degrees;
}

vector<string> GetBranches(GraphEdgeChart dB, vector<string>* patternStrsNoRepeat)
{
	vector<string> allPaths; // Paths ¡û empty list
	
	int nodeNum = patternStrsNoRepeat->size();
	NodeDegreeChart nodeDegrees = GraphDegrees(dB, nodeNum);
	for (int i = 0; i < nodeNum; i++)
	{
		if (nodeDegrees[i] == pair<int, int>(1, 1))
		{
			int nodeV = i, nodeW;
			string isolatedStr = (*patternStrsNoRepeat)[nodeV];
			while (true)
			{
				for (int j = 0; j < dB.size(); j++)
				{
					if (dB[j].first == nodeV)
					{
						nodeW = dB[j].second;
						break;
					}
				}
				if (nodeW>=i && nodeDegrees[nodeW] == pair<int, int>(1, 1))
				{// nodeW>=i is to make sure the isolatedStr not repeat with the former nodes
					isolatedStr = isolatedStr + (*patternStrsNoRepeat)[nodeW].back();
				}
				else
				{
					break;
				}

				if (nodeW == i)
				{
					allPaths.push_back(isolatedStr);
					break;
				}

				nodeV = nodeW;
			}

		}
		else // if v is not a 1-in-1-out node
		{
			int nodeV = i;
			if (nodeDegrees[nodeV].second > 0) // if out(v) > 0
			{
				for (int j = 0; j < dB.size(); j++)
				{
					if (dB[j].first == nodeV)
					{
						int nodeW = dB[j].second;
						string nonBranchingPath = (*patternStrsNoRepeat)[nodeV] + (*patternStrsNoRepeat)[nodeW].back();
						while (nodeDegrees[nodeW] == pair<int, int>(1, 1))
						{
							int nodeU;
							for (int m = 0; m < dB.size(); m++)
							{
								if (dB[m].first == nodeW)
								{
									nodeU = dB[m].second;
									break;
								}
							}
							nonBranchingPath = nonBranchingPath + (*patternStrsNoRepeat)[nodeU].back();
							nodeW = nodeU;
						}
						allPaths.push_back(nonBranchingPath);
					}
				}
			}
		}
	}
	// for each isolated cycle Cycle in Graph


	return allPaths;
}

vector<string> ContigGeneration(vector<string>* Patterns)
{
	// dB ¡û DeBruijn(Patterns)
	vector<string> patternStrsNoRepeat;
	vector<pair<int,int>> dB = deBruijnGraphPatterns(Patterns, &patternStrsNoRepeat);
	// get branches of nodes
	vector<string> contigs = GetBranches(dB, &patternStrsNoRepeat);

	return contigs;
}