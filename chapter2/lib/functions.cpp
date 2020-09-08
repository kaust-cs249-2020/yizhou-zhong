#include "functions.h"
#include "mathtool.h"
#include <cstdlib>
#include <iostream>

bool showcout = false;

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