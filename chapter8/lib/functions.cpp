#include "functions.h"
#include "mathtool.h"
#include <cstdlib>
#include <iostream>

class TREE
{
public:
	TREE(bool weightflag = false)
	{
		this->N = 0;
		this->bidirectional = true;
		this->weightisfloat = weightflag;
	}

	void HalfLink(int a, int b, int weight=1)
	{
		if (!Belong2PepValues(a, this->nodes))
		{
			this->nodes.push_back(a);
		}
		map<int, vector<PAIR>>::iterator edgeIter;
		edgeIter = this->edges.find(a);
		if (edgeIter==this->edges.end())
		{
			vector<PAIR> tmp = vector<PAIR>(1, PAIR(b, weight));
			this->edges.insert(pair<int, vector<PAIR>>(a, tmp));
		}
		else
		{
			vector<PAIR> tmp = edgeIter->second;
			for (int i = 0; i < tmp.size();i++)
			{
				if (tmp[i].first == b)
				{
					tmp.erase(tmp.begin() + i);
					i--;
				}
			}
			tmp.push_back(PAIR(b, weight));
			edgeIter->second = tmp;
		}
	}

	void HalfLink(int a, int b, float weight)
	{
		if (!Belong2PepValues(a, this->nodes))
		{
			this->nodes.push_back(a);
		}
		map<int, vector<pair<int, float>>>::iterator edgeIter;
		edgeIter = this->edgesfloat.find(a);
		if (edgeIter == this->edgesfloat.end())
		{
			vector<pair<int, float>> tmp = vector<pair<int, float>>(1, pair<int, float>(b, weight));
			this->edgesfloat.insert(pair<int, vector<pair<int, float>>>(a, tmp));
		}
		else
		{
			vector<pair<int, float>> tmp = edgeIter->second;
			for (int i = 0; i < tmp.size(); i++)
			{
				if (tmp[i].first == b)
				{
					tmp.erase(tmp.begin() + i);
					i--;
				}
			}
			tmp.push_back(pair<int, float>(b, weight));
			edgeIter->second = tmp;
		}
	}

	void Link(int start, int end, int weight=1)
	{
		this->HalfLink(start, end, weight);
		if (this->bidirectional)
		{
			this->HalfLink(end, start, weight);
		}
	}

	void Link(int start, int end, float weight)
	{
		this->HalfLink(start, end, weight);
		if (this->bidirectional)
		{
			this->HalfLink(end, start, weight);
		}
	}

	void HalfUnlink(int a, int b)
	{
		if (this->weightisfloat)
		{
			map<int, vector<pair<int, float>>>::iterator edgeIter;
			edgeIter = this->edgesfloat.find(a);
			vector<pair<int, float>> links = edgeIter->second;
			for (int i = 0; i < links.size(); i++)
			{
				if (links[i].first == b)
				{
					links.erase(links.begin() + i);
					i--;
				}
			}
			if (links.size() < edgeIter->second.size())
			{
				edgeIter->second = links;
			}
		}
		else
		{
			map<int, vector<PAIR>>::iterator edgeIter;
			edgeIter = this->edges.find(a);
			vector<PAIR> links = edgeIter->second;
			for (int i = 0; i < links.size(); i++)
			{
				if (links[i].first == b)
				{
					links.erase(links.begin() + i);
					i--;
				}
			}
			if (links.size() < edgeIter->second.size())
			{
				edgeIter->second = links;
			}
		}
	}

	void Unlink(int i, int k)
	{
		this->HalfUnlink(i, k);
		if (this->bidirectional)
		{
			this->HalfUnlink(k, i);
		}
	}

	int NumNodes()
	{
		return this->nodes.size();
	}

	void RemoveBackwardLinks(int root)
	{
		if (weightisfloat)
		{
			this->bidirectional = false;
			map<int, vector<pair<int, float>>>::iterator edgeIter;
			edgeIter = edgesfloat.find(root);
			vector<pair<int, float>> tmp = edgeIter->second;
			for (int i = 0; i < tmp.size(); i++)
			{
				int child = tmp[i].first;
				this->HalfUnlink(child, root);
				this->RemoveBackwardLinks(child);
			}
		}
		else
		{
			this->bidirectional = false;
			map<int, vector<PAIR>>::iterator edgeIter;
			edgeIter = edges.find(root);
			vector<PAIR> tmp = edgeIter->second;
			for (int i = 0; i < tmp.size(); i++)
			{
				int child = tmp[i].first;
				this->HalfUnlink(child, root);
				this->RemoveBackwardLinks(child);
			}
		}
	}

	void NodesSort()
	{
		sort(this->nodes.begin(), this->nodes.end());
	}

public:
	vector<int> nodes;
	map<int, vector<PAIR>> edges;
	map<int, vector<pair<int, float>>> edgesfloat;
	bool bidirectional;
	int N;
	bool weightisfloat;
};

class NODETREE
{
public:
	NODETREE()
	{
		this->N = 0;
		this->bidirectional = true;
	}

	void HalfLink(NODE a, NODE b, float weight=1.0f)
	{
		if (!Belong2Nodes(a, this->nodes))
		{
			this->nodes.push_back(a);
		}
		map<NODE, vector<pair<NODE, float>>>::iterator edgeIter;
		edgeIter = this->edges.find(a);
		if (edgeIter == this->edges.end())
		{
			vector<pair<NODE, float>> tmp = vector<pair<NODE, float>>(1, pair<NODE, float>(b, weight));
			this->edges.insert(pair<NODE, vector<pair<NODE, float>>>(a, tmp));
		}
		else
		{
			vector<pair<NODE, float>> tmp = edgeIter->second;
			for (int i = 0; i < tmp.size(); i++)
			{
				if (tmp[i].first.index == b.index
					&& tmp[i].first.label == b.label)
				{
					tmp.erase(tmp.begin() + i);
					i--;
				}
			}
			tmp.push_back(pair<NODE, float>(b, weight));
			edgeIter->second = tmp;
		}
	}

	void Link(NODE start, NODE end, float weight = 1.0f)
	{
		this->HalfLink(start, end, weight);
		if (this->bidirectional)
		{
			this->HalfLink(end, start, weight);
		}
	}

	//void HalfUnlink(NODE a, NODE b)
	//{
	//	map<NODE, vector<pair<NODE, float>>>::iterator edgeIter;
	//	edgeIter = this->edges.find(a);
	//	vector<pair<NODE, float>> links = edgeIter->second;
	//	for (int i = 0; i < links.size(); i++)
	//	{
	//		if (links[i].first.index == b.index &&
	//			links[i].first.label == b.label)
	//		{
	//			links.erase(links.begin() + i);
	//			i--;
	//		}
	//	}
	//	if (links.size() < edgeIter->second.size())
	//	{
	//		edgeIter->second = links;
	//	}
	//}

	//void Unlink(NODE i, NODE k)
	//{
	//	this->HalfUnlink(i, k);
	//	if (this->bidirectional)
	//	{
	//		this->HalfUnlink(k, i);
	//	}
	//}

	//int NumNodes()
	//{
	//	return this->nodes.size();
	//}

	//void RemoveBackwardLinks(NODE root)
	//{
	//	this->bidirectional = false;
	//	map<NODE, vector<pair<NODE, float>>>::iterator edgeIter;
	//	edgeIter = edges.find(root);
	//	vector<pair<NODE, float>> tmp = edgeIter->second;
	//	for (int i = 0; i < tmp.size(); i++)
	//	{
	//		NODE child = tmp[i].first;
	//		this->HalfUnlink(child, root);
	//		this->RemoveBackwardLinks(child);
	//	}
	//}

	//void NodesSort()
	//{
	//	sort(this->nodes.begin(), this->nodes.end());
	//}

public:
	vector<NODE> nodes;
	map<NODE, vector<pair<NODE, float>>> edges;
	bool bidirectional;
	int N;
};

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

StrFreqTable FrequencyTable(string* Text, int k)
{
	int n = Text->length();
	StrFreqTable freMap;
	StrFreqTable::iterator freMapIte;
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
		StrFreqTable freqMap = FrequencyTable(&window, k);
		StrFreqTable::iterator iterFreMap;
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
	StrFreqTable freqMap;
	StrFreqTable::iterator iterFreqMap;
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
	StrFreqTable freqMap;
	StrFreqTable::iterator iterFreqMap;
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
		{// for each isolated cycle Cycle in Graph
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
				if (nodeW >= i && nodeDegrees[nodeW] == pair<int, int>(1, 1))
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

string ProteinTranslation(string rnaStr, GeneticCodeTable* codeTable)
{
	string peptide;
	GeneticCodeTable::iterator tableIter;

	int len = rnaStr.length();
	int n = len / 3;
	for (int i = 0; i < n;i++)
	{
		string subStr = rnaStr.substr(i*3, 3);
		tableIter = codeTable->find(subStr);
		peptide = peptide + tableIter->second;
	}


	return peptide;
}

string DNA2RNA(string dnaStr)
{
	int len = dnaStr.length();
	string rnaStr = dnaStr;
	for (int i = 0; i < len; i++)
	{
		if (dnaStr[i]=='T')
		{
			rnaStr[i] = 'U';
		}
	}
	return rnaStr;
}

vector<string> PeptideEncoding(string dnaStr, string peptide, GeneticCodeTable* codeTable)
{
	vector<string> subStrs;
	GeneticCodeTable::iterator tableIter;
	int pepLen = peptide.length();
	int k = 3 * pepLen;
	int dnaLen = dnaStr.length();
	for (int i = 0; i < dnaLen-k+1; i++)
	{
		string dnaSubStr = dnaStr.substr(i, k);
		string rnaSubStr = DNA2RNA(dnaSubStr);
		string dnaRevSub = TeverseComplement(&dnaSubStr);
		string rnaRveSub = DNA2RNA(dnaRevSub);
		bool flag = false;
		for (int j = 0; j < pepLen;j++)
		{
			string mer = rnaSubStr.substr(3 * j, 3);
			tableIter = codeTable->find(mer);
			if (tableIter->second != string(1, peptide[j]))
			{
				break;
			}
			if (j == pepLen - 1)
			{
				flag=true;
			}
		}
		if (flag)
		{
			subStrs.push_back(dnaSubStr);
			continue;
		}
		flag = false;
		for (int j = 0; j < pepLen; j++)
		{
			string mer = rnaRveSub.substr(3 * j, 3);
			tableIter = codeTable->find(mer);
			if (tableIter->second != string(1, peptide[j]))
			{
				break;
			}
			if (j == pepLen - 1)
			{
				flag=true;
			}
		}
		if (flag)
		{
			subStrs.push_back(dnaSubStr);
		}
	}
	return subStrs;
}

vector<int> LinearSpectrum(string peptide, IntegerMassTable* massTable)
{
	vector<int> prefixMass(1, 0);
	IntegerMassTable::iterator massIter;
	int pepLen = peptide.length();
	for (int i = 0; i < pepLen; i++)
	{
		char s = peptide[i];
		massIter = massTable->find(s);
		prefixMass.push_back(prefixMass[i] + massIter->second);
	}
	vector<int> linearSpec(1,0);
	for (int i = 0; i < pepLen; i++)
	{
		for (int j = i + 1; j <= pepLen; j++)
		{
			linearSpec.push_back(prefixMass[j] - prefixMass[i]);
		}
	}
	sort(linearSpec.begin(), linearSpec.end());

	return linearSpec;
}

vector<int> TheoreticalSpectrum(string peptide, IntegerMassTable* massTable)
{
	vector<int> spec1 = LinearSpectrum(peptide, massTable);
	int specMax = spec1[spec1.size()-1];
	if (peptide.length()>1)
	{
		string midPeptide = peptide.substr(1, peptide.length() - 2);
		vector<int> spec2 = LinearSpectrum(midPeptide, massTable);
		for (int i = 1; i < spec2.size();i++)
		{
			spec1.push_back(specMax - spec2[i]);
		}
	}
	sort(spec1.begin(), spec1.end());

	return spec1;
}

int PepMass(string peptides, IntegerMassTable* massTable)
{
	int mass = 0, len = peptides.size();
	IntegerMassTable::iterator massIter;
	for (int i = 0; i < len; i++)
	{
		massIter = massTable->find(peptides[i]);
		mass += massIter->second;
	}
	return mass;
}

vector<string> GetCandidate(int pepLen, vector<int> pepValues, IntegerMassTable* massTable)
{
	vector<string> peptide;
	IntegerMassTable::iterator massIter;
	if (pepLen <=0)
	{
		return peptide;
	}
	else if (pepLen==1)
	{
		for (massIter = massTable->begin(); massIter != massTable->end(); massIter++)
		{
			if (Belong2PepValues(massIter->second, pepValues))
			{
				peptide.push_back(string(1, massIter->first));
			}
		}
		return peptide;
	}
	else
	{
		vector<string> prePeptide = GetCandidate(pepLen - 1, pepValues, massTable);
		for (int i = 0; i < prePeptide.size(); i++)
		{
			for (massIter = massTable->begin(); massIter != massTable->end(); massIter++)
			{
				string temStr = string(1, massIter->first) + prePeptide[i];
				if (Belong2PepValues(PepMass(temStr, massTable), pepValues))
				{
					peptide.push_back(temStr);
				}
			}
		}
		return peptide;
	}
}

//bool SameSpec(vector<int> specInt, vector<int> specInt2)
//{
//	bool specsAreSame = false;
//	if (specInt.size() != specInt2.size())
//	{
//		return specsAreSame;
//	}
//	for (int i = 0; i < specInt.size();i++)
//	{
//		if (specInt[i] != specInt2[i])
//		{
//			return specsAreSame;
//		}
//	}
//	specsAreSame = true;
//	return specsAreSame;
//}

string Pep2PepNumStr(string peptides, IntegerMassTable* massTable)
{
	string pepNumStr;
	int len = peptides.length();
	IntegerMassTable::iterator massIter;
	for (int i = 0; i < len; i++)
	{
		massIter = massTable->find(peptides[i]);
		pepNumStr = pepNumStr + to_string(massIter->second);
		if (i!=len-1)
		{
			pepNumStr = pepNumStr + '-';
		}
	}
	return pepNumStr;
}

vector<string> CyclopeptideSequencing(vector<int> specInt, IntegerMassTable* massTable)
{
	int specLen = specInt.size();
	int peptidesLen = (1 + sqrt(4 * specLen - 7)) / 2;
	
	vector<string> candidatePeptides = GetCandidate(peptidesLen, specInt, massTable);
	vector<string> finalPepNumStr;
	for (long i = 0; i < candidatePeptides.size();i++)
	{
		if (PepMass(candidatePeptides[i], massTable) == specInt[specLen - 1])
		{
			vector<int> candidateSpecInt = TheoreticalSpectrum(candidatePeptides[i], massTable);
			if (candidateSpecInt == specInt)
			{
				string pepNumStr = Pep2PepNumStr(candidatePeptides[i], massTable);
				if (!Belong2Patterns(pepNumStr, finalPepNumStr))
				{
					finalPepNumStr.push_back(pepNumStr);
				}
			}
		}
	}

	return finalPepNumStr;
}

int Score(string peptide, vector<int> specInt, IntegerMassTable* massTable)
{
	int pepScore=0;
	vector<int> specIntCopy = specInt;
	vector<int> cyclicSpec = TheoreticalSpectrum(peptide, massTable);
	for (int i=0; i < cyclicSpec.size();i++)
	{
		int speNum = cyclicSpec[i];
		int idx;
		if (Belong2PepValues(speNum, specIntCopy, idx))
		{
			specIntCopy.erase(specIntCopy.begin() + idx);
			pepScore++;
		}
	}

	return pepScore;
}

int LinearScore(string peptide, vector<int> specInt, IntegerMassTable* massTable)
{
	int pepScore = 0;
	vector<int> specIntCopy = specInt;
	vector<int> cyclicSpec = LinearSpectrum(peptide, massTable);
	for (int i = 0; i < cyclicSpec.size(); i++)
	{
		int speNum = cyclicSpec[i];
		int idx;
		if (Belong2PepValues(speNum, specIntCopy, idx))
		{
			specIntCopy.erase(specIntCopy.begin() + idx);
			pepScore++;
		}
	}
	return pepScore;
}

vector<string> Trim(vector<string> leaderboard, vector<int> specInt, int N, IntegerMassTable* massTable)
{
	vector<string> highScorePeptides;
	int len = leaderboard.size();
	vector<int> linearScores(len, 0);

	for (int j = 0; j < len; j++)
	{
		string peptide = leaderboard[j];
		linearScores[j] = LinearScore(peptide, specInt, massTable);
	}
	vector<int>	linearScoresSorted = linearScores;
	vector<string> leaderboardCopy = leaderboard;
	sort(linearScoresSorted.rbegin(), linearScoresSorted.rend());
	for (int i = 0; i < len; i++)
	{
		int score = linearScoresSorted[i];
		for (int j = 0; j < linearScores.size();j++)
		{
			if (score == linearScores[j])
			{
				highScorePeptides.push_back(leaderboardCopy[j]);
				linearScores.erase(linearScores.begin() + j);
				leaderboardCopy.erase(leaderboardCopy.begin() + j);
				break;
			}
		}
	}
	for (int j = N; j < len;j++)
	{
		if (linearScoresSorted[j] < linearScoresSorted[N-1])
		{
			for (int i = j; i < len;i++)
			{
				highScorePeptides.erase(highScorePeptides.begin() + j);
			}
			return highScorePeptides;
		}
	}
	return highScorePeptides;
}

vector<string> Expand(vector<string> peptides,
	vector<int> spec,
	IntegerMassTable* massTable)
{
	vector<string> expandedPep;
	IntegerMassTable::iterator massIter;
	int len = peptides.size();
	for (int i = 0; i < len;i++)
	{
		for (massIter = massTable->begin(); massIter != massTable->end(); massIter++)
		{
			string tmppep = peptides[i] + massIter->first;
			
			if (Belong2PepValues(PepMass(tmppep, massTable), spec))
			{
				expandedPep.push_back(tmppep);
			}
		}
	}
	return expandedPep;
}

vector<string> Expand(vector<string> peptides,
	vector<int> spec,
	IntegerMassTable* massTable,
	vector<int> aminoList)
{
	vector<string> expandedPep;
	IntegerMassTable::iterator massIter;
	int len = peptides.size();
	for (int i = 0; i < len; i++)
	{
		for (massIter = massTable->begin(); massIter != massTable->end(); massIter++)
		{
			if (Belong2PepValues(massIter->second, aminoList))
			{
				string tmppep = peptides[i] + massIter->first;

				if (Belong2PepValues(PepMass(tmppep, massTable), spec))
				{
					expandedPep.push_back(tmppep);
				}
			}
			
		}
	}
	return expandedPep;
}

string LeaderboardCyclopeptideSequencing(vector<int> specInt, int N, IntegerMassTable* massTable)
{
	vector<string> leaderboard(1, "");
	string leaderpeptide;
	int parentMass = specInt.back();

	while (leaderboard.size() > 0)
	{
		leaderboard = Expand(leaderboard, specInt, massTable);
		for (int i = 0; i < leaderboard.size(); i++)
		{
			string peptide = leaderboard[i];
			if (PepMass(peptide, massTable) == parentMass)
			{
				int a = Score(leaderpeptide, specInt, massTable);
				if (Score(peptide, specInt, massTable) > Score(leaderpeptide, specInt, massTable))
				{
					leaderpeptide = peptide;
				}
			}
			else if (PepMass(peptide, massTable) > parentMass)
			{
				leaderboard.erase(leaderboard.begin() + i);
				i--;
			}
		}
		leaderboard = Trim(leaderboard, specInt, N, massTable);
	}

	string leaderPepValStr;
	IntegerMassTable::iterator massIter;
	for (int i = 0; i < leaderpeptide.length(); i++)
	{
		massIter = massTable->find(leaderpeptide[i]);
		leaderPepValStr = leaderPepValStr + to_string(massIter->second);
		if (i != leaderpeptide.length() - 1)
		{
			leaderPepValStr = leaderPepValStr + '-';
		}
	}

	return leaderPepValStr;
}

string LeaderboardCyclopeptideSequencing(vector<int> specInt, 
	int N, IntegerMassTable* massTable, 
	vector<int> aminoList)
{
	vector<string> leaderboard(1, "");
	string leaderpeptide;
	int parentMass = specInt.back();

	while (leaderboard.size()>0)
	{
		leaderboard = Expand(leaderboard, 
			specInt, 
			massTable, 
			aminoList);
		for (int i = 0; i < leaderboard.size();i++)
		{
			string peptide = leaderboard[i];
			if (PepMass(peptide, massTable) == parentMass)
			{
				int a = Score(leaderpeptide, specInt, massTable);
				if (Score(peptide, specInt, massTable) > Score(leaderpeptide, specInt, massTable))
				{
					leaderpeptide = peptide;
				}
			}
			else if (PepMass(peptide, massTable) > parentMass)
			{
				leaderboard.erase(leaderboard.begin() + i);
				i--;
			}
		}
		leaderboard = Trim(leaderboard, specInt, N, massTable);
	}

	string leaderPepValStr;
	IntegerMassTable::iterator massIter;
	for (int i = 0; i < leaderpeptide.length();i++)
	{
		massIter = massTable->find(leaderpeptide[i]);
		leaderPepValStr = leaderPepValStr + to_string(massIter->second);
		if (i != leaderpeptide.length()-1)
		{
			leaderPepValStr = leaderPepValStr + '-';
		}
	}

	return leaderPepValStr;
}

vector<int> SpectralConvolution(vector<int> specInt)
{
	vector<int> speConvol;
	int len = specInt.size();

	for (int m = 0; m < len; m++)
	{
		for (int n = 0; n < len;n++)
		{
			int diff = specInt[m] - specInt[n];
			if (diff>0)
			{
				speConvol.push_back(diff);
			}
		}
	}

	return speConvol;
}

bool Belong2Vector(int a, CountTable aVec, int& idx)
{
	for (int i = 0; i < aVec.size();i++)
	{
		if (aVec[i].first == a)
		{
			idx = i;
			return true;
		}
	}
	return false;
}

CountTable CountedConvol(vector<int> specInt)
{
	vector<int> convolution = SpectralConvolution(specInt);
	CountTable counted;

	int len = convolution.size();
	for (int i = 0; i < len;i++)
	{
		int d = convolution[i];
		if (57<=d && d<=200)
		{
			int idx;
			if (Belong2Vector(d, counted, idx))
			{
				counted[idx].second += 1;
			}
			else
			{
				counted.push_back(pair<int,int>(d,1));
			}
		}
	}
	sort(counted.begin(), counted.end(), cmp());

	return counted;
}

string  ConvolutionCycPepSeq(int M, int N, vector<int> specInt, IntegerMassTable* massTable)
{
	CountTable counted = CountedConvol(specInt);
	vector < int > convolution;

	for (int i = 0; i < M; i++)
	{
		convolution.push_back(counted[i].first);
	}

	for (int i = M; i < counted.size();i++)
	{
		if (counted[i].second == counted[M].second)
		{
			convolution.push_back(counted[i].first);
		}
	}

	string  leaderPeptide = LeaderboardCyclopeptideSequencing(specInt, N, massTable, convolution);
	return leaderPeptide;
}

int DPChange(int money, vector<int> coins)
{
	vector<int> minCoinNumArray(1, 0);
	for (int m = 1; m <= money;m++)
	{
		minCoinNumArray.push_back(INT_MAX);
		for (int n = 0; n < coins.size();n++)
		{
			int coin = coins[n];
			if (m>=coin)
			{
				if (minCoinNumArray[m - coin] + 1 < minCoinNumArray[m])
				{
					minCoinNumArray[m] = minCoinNumArray[m - coin] + 1;
				}
			}
		}
	}

	return minCoinNumArray[money];
}

int ManhattanTourist(int n, int m, vector<vector<int>> downMat, vector<vector<int>> rightMat)
{
	vector<vector<int>> pathLenMat(n+1, vector<int>(m+1, 0));
	for (int i = 1; i < n + 1;i++)
	{
		pathLenMat[i][0] = pathLenMat[i - 1][0] + downMat[i - 1][0];
	}
	for (int j = 1; j < m + 1;j++)
	{
		pathLenMat[0][j] = pathLenMat[0][j - 1] + rightMat[0][j - 1];
	}
	for (int i = 1; i < n + 1;i++)
	{
		for (int j = 1; j < m + 1;j++)
		{
			pathLenMat[i][j] = findMaxOf2(pathLenMat[i - 1][j] + downMat[i - 1][j], pathLenMat[i][j - 1] + rightMat[i][j - 1]);
		}
	}

	return pathLenMat[n][m];
}

vector<string> LcsBackTrack(string v, string w)
{
	int vLen = v.length();
	int wLen = w.length();
	vector<string> backTrack(vLen, string(wLen, ' '));
	vector<vector<int>> pathLenMat(vLen+1, vector<int>(wLen+1, 0));
	for (int i = 1; i < vLen + 1;i++)
	{
		for (int j = 1; j < wLen + 1;j++)
		{
			int match = 0;
			if (v.at(i-1)==w.at(j-1))
			{
				match = 1;
			}
			vector<int> tmp;
			tmp.push_back(pathLenMat[i - 1][j]);
			tmp.push_back(pathLenMat[i][j - 1]);
			tmp.push_back(pathLenMat[i - 1][j - 1] + match);
			int idx;
			pathLenMat[i][j] = findMax(tmp, 3, idx);
			
			switch (idx)
			{
			case 0:
				backTrack[i - 1].at(j - 1) = 'd';
				break;
			case 1:
				backTrack[i - 1].at(j - 1) = 'r';
				break;
			default:
				backTrack[i - 1].at(j - 1) = 'c';
			}
		}
	}
	return backTrack;
}

string OutputLCS(vector<string> backTrack, string v, int i, int j)
{
	if (i <= 0 || j <= 0)
	{
		return "";
	}
	if ('d' == backTrack[i - 1].at(j - 1))
	{
		return OutputLCS(backTrack, v, i - 1, j);
	}
	else if ('r' == backTrack[i - 1].at(j - 1))
	{
		return OutputLCS(backTrack, v, i, j - 1);
	}
	else
	{
		return OutputLCS(backTrack, v, i - 1, j - 1) + v.at(i - 1);
	}
}

string LongestComSubSeq(string s, string t)
{
	int sLen = s.length();
	int tLen = t.length();
	vector<string> backTrack = LcsBackTrack(s, t);
	return OutputLCS(backTrack, s, sLen, tLen);
}

vector<int> TopologicalOrdering(vector<int> nodes, CountTable adjList)
{
	NodeDegreeChart degrees = GraphDegrees(adjList, nodes.size());
	vector<int> candidates;
	vector<int> chosenList;
	for (int i = 0; i < degrees.size();i++)
	{
		if (degrees[i].first == 0)
		{
			candidates.push_back(i);
		}
	}

	CountTable adjListCopy = adjList;

	while (candidates.size()!=0)
	{
		int idx = RandIdx(0, candidates.size() - 1);
		int candidate = candidates[idx];
		candidates.erase(candidates.begin() + idx);
		chosenList.push_back(candidate);

		for (int i = 0; i < adjListCopy.size(); i++)
		{
			if (adjListCopy[i].first == candidate)
			{
				int b = adjListCopy[i].second;
				adjListCopy.erase(adjListCopy.begin() + i);
				NodeDegreeChart degreeTmp = GraphDegrees(adjListCopy, nodes.size());
				if (degreeTmp[b].first == 0)
				{
					candidates.push_back(b);
				}
				i--;
			}
		}
	}

	vector<int> chosenListNode;

	if (adjListCopy.size()>0)
	{
		 //"the input graph is not a DAG"
	}
	else
	{
		for (int i = 0; i < chosenList.size();i++)
		{
			chosenListNode.push_back(nodes[chosenList[i]]);
		}
	}
	return chosenListNode;
}

vector<int> LongestPathinDag(int graphStartNode, int graphEndNode, 
	vector<int> nodes, vector<int> weightList, CountTable adjList, int& longestPathLen)
{
	vector<int> topoOrdering = TopologicalOrdering(nodes, adjList);
	// delete start node and nodes before it
	for (int i = 0; i < topoOrdering.size();i++)
	{
		int tmp = topoOrdering[i];
		topoOrdering.erase(topoOrdering.begin() + i);
		if (tmp==graphStartNode)
		{
			break;
		}
		i--;
	}
	// initial s and backtrack
	NodeWeightMap sMap;
	NodeWeightMap::iterator iterS;
	for (int i = 0; i < nodes.size();i++)
	{
		sMap.insert(PAIR(nodes[i], -1));
	}
	iterS = sMap.find(graphStartNode);
	iterS->second = 0;

	NodeWeightMap backTrackMap;
	NodeWeightMap::iterator iterBack;
	for (int i = 0; i < topoOrdering.size();i++)
	{
		int node = topoOrdering[i];
		backTrackMap.insert(PAIR(node, -1));

		NodeWeightMap saMap;
		NodeWeightMap::iterator iterSa;

		// Sb = max[all predessesors a of b(Sa + weight from a to b)
		for (int j = 0; j < adjList.size();j++)
		{
			if (nodes[adjList[j].second] == node)
			{
				saMap.insert(PAIR(nodes[adjList[j].first], weightList[j]));
			}
		}
		for (iterSa = saMap.begin(); iterSa != saMap.end();iterSa++)
		{
			iterS = sMap.find(iterSa->first);
			iterSa->second = iterS->second + iterSa->second;
		}
		// find the max weight in map sa
		PAIR maxPairTmp=PAIR(0, -1);
		for (iterSa = saMap.begin(); iterSa != saMap.end(); iterSa++)
		{
			if (iterSa->second > maxPairTmp.second)
			{
				maxPairTmp.first = iterSa->first;
				maxPairTmp.second = iterSa->second;
			}
		}
		iterS = sMap.find(node);
		iterBack = backTrackMap.find(node);
		iterBack->second = maxPairTmp.first;
		iterS->second = maxPairTmp.second;
	}
		
	vector<int> longestPath(1, graphEndNode);
	while (longestPath[0] != graphStartNode)
	{
		iterBack = backTrackMap.find(longestPath[0]);
		longestPath.insert(longestPath.begin(), iterBack->second);
	}

	iterS = sMap.find(graphEndNode);
	longestPathLen = iterS->second;

	return longestPath;
}

vector<string> GlobalAlignProblem(string strV, string strW,
	string scoringChar, vector<vector<int>> scoringMat, int sigma, int& scoreMax)
{
	int vLen = strV.length();
	int wLen = strW.length();
	vector<vector<int>> pathLenMat(vLen+1, vector<int>(wLen+1, 0));
	vector<string> backTrack(vLen+1, string(wLen+1, ' '));
	for (int i = 1; i < vLen + 1; i++)
	{
		pathLenMat[i][0] = -i*sigma;
	}
	for (int i = 1; i < wLen + 1; i++)
	{
		pathLenMat[0][i] = -i*sigma;
	}

	for (int i = 1; i < vLen + 1;i++)
	{
		for (int j = 1; j < wLen + 1;j++)
		{
			int idx1 = scoringChar.find(strV.at(i-1));
			int idx2 = scoringChar.find(strW.at(j-1));
			int match = scoringMat[idx1][idx2];
			vector<int> tmp;
			tmp.push_back(pathLenMat[i-1][j]-sigma);
			tmp.push_back(pathLenMat[i][j-1]-sigma);
			tmp.push_back(pathLenMat[i - 1][j - 1] + match);
			int idxTmp;
			pathLenMat[i][j] = findMax(tmp, 3, idxTmp);
			switch (idxTmp)
			{
			case 0:
				backTrack[i][j] = 'd';
				break;
			case 1:
				backTrack[i][j] = 'r';
				break;
			default:
				backTrack[i][j] = 'c';
			}

		}
	}
	scoreMax = pathLenMat[vLen][wLen];

	string strVback = strV, strWback = strW;
	int i = vLen, j = wLen;
	while (i!=0 && j!=0)
	{
		if (backTrack[i][j]=='d')
		{
			i--;
			strWback = strWback.substr(0, j) + string(1, '-') + strWback.substr(j, strWback.length() - j);
		}
		else if (backTrack[i][j] == 'r')
		{
			j--;
			strVback = strVback.substr(0, i) + string(1, '-') + strVback.substr(i, strVback.length() - i);
		}
		else
		{
			i--;
			j--;
		}
	}
	for (int m = 0; m < i;m++)
	{
		strWback = string(1, '-') + strWback;
	}
	for (int n = 0; n < j;n++)
	{
		strVback = string(1, '-') + strVback;
	}

	vector<string> outputStr;
	outputStr.push_back(strVback);
	outputStr.push_back(strWback);
	return outputStr;
}

vector<string> LoaclAlignProblem(string strV, string strW,
	string scoringChar, vector<vector<int>> scoringMat, int sigma, int& scoreMax)
{
	int vLen = strV.length();
	int wLen = strW.length();
	vector<vector<int>> pathLenMat(vLen + 1, vector<int>(wLen + 1, 0));
	vector<string> backTrack(vLen + 1, string(wLen + 1, ' '));

	for (int i = 1; i < vLen + 1;i++)
	{
		for (int j = 1; j < wLen + 1;j++)
		{
			int idx1 = scoringChar.find(strV.at(i - 1));
			int idx2 = scoringChar.find(strW.at(j - 1));
			int match = scoringMat[idx1][idx2];
			vector<int> tmp;
			tmp.push_back(pathLenMat[i - 1][j] - sigma);
			tmp.push_back(pathLenMat[i][j - 1] - sigma);
			tmp.push_back(pathLenMat[i - 1][j - 1] + match);
			tmp.push_back(0);
			int idxTmp;
			pathLenMat[i][j] = findMax(tmp, 4, idxTmp);
			switch (idxTmp)
			{
			case 0:
				backTrack[i][j] = 'd';
				break;
			case 1:
				backTrack[i][j] = 'r';
				break;
			case 2:
				backTrack[i][j] = 'c';
				break;
			default:
				backTrack[i][j] = 'T';
			}
		}
	}

	int i, j;
	scoreMax = findMaxOfMat(pathLenMat, i, j);
	string strVback = strV.substr(0, i);
	string strWback = strW.substr(0, j);
	while (backTrack[i][j]!='T' && i != 0 && j != 0)
	{
		if (backTrack[i][j] == 'd')
		{
			i--;
			strWback = strWback.substr(0, j) + string(1, '-') + strWback.substr(j, strWback.length() - j);
		}
		else if (backTrack[i][j] == 'r')
		{
			j--;
			strVback = strVback.substr(0, i) + string(1, '-') + strVback.substr(i, strVback.length() - i);
		}
		else
		{
			i--;
			j--;
		}
	}

	strVback = strVback.substr(i, strVback.length()-i);
	strWback = strWback.substr(j, strWback.length() - j);
	vector<string> outputStr;
	outputStr.push_back(strVback);
	outputStr.push_back(strWback);
	return outputStr;
}

int EditDistanceProblem(string strV, string strW)
{
	int vLen = strV.length();
	int wLen = strW.length();
	vector<vector<int>> editDisMat(vLen + 1, vector<int>(wLen + 1, 0));
	for (int i = 1; i < vLen + 1;i++)
	{
		editDisMat[i][0] = i;
	}
	for (int i = 1; i < wLen + 1;i++)
	{
		editDisMat[0][i] = i;
	}

	for (int i = 1; i < vLen + 1;i++)
	{
		for (int j = 1; j < wLen + 1;j++)
		{
			if (strV.at(i-1)==strW.at(j-1))
			{
				editDisMat[i][j] = editDisMat[i - 1][j - 1];
			}
			else
			{
				vector<int> tmp;
				tmp.push_back(editDisMat[i - 1][j] + 1);
				tmp.push_back(editDisMat[i][j - 1] + 1);
				tmp.push_back(editDisMat[i - 1][j - 1] + 1);
				editDisMat[i][j] = findMin(tmp, 3);
			}
		}
	}
	return editDisMat[vLen][wLen];
}

vector<string> FittingAlignmentProblem(string strV, string strW, int& scoreMax)
{
	int vLen = strV.length();
	int wLen = strW.length();
	vector<vector<int>> scoreMat(vLen + 1, vector<int>(wLen + 1, 0));
	vector<string> backTrack(vLen + 1, string(wLen + 1, ' '));
	for (int i = 1; i < vLen + 1;i++)
	{
		for (int j = 1; j < wLen + 1;j++)
		{
			int match = -1;
			if (strV.at(i-1)==strW.at(j-1))
			{
				match = 1;
			}
			vector<int> tmp;
			tmp.push_back(scoreMat[i - 1][j] - 1);
			tmp.push_back(scoreMat[i][j - 1] - 1);
			tmp.push_back(scoreMat[i - 1][j - 1] + match);
			int idxTmp;
			scoreMat[i][j] = findMax(tmp, 3, idxTmp);
			switch (idxTmp)
			{
			case 0:
				backTrack[i][j] = 'd';
				break;
			case 1:
				backTrack[i][j] = 'r';
				break;
			default:
				backTrack[i][j] = 'c';
			}
		}
	}

	int j = wLen;
	int i;
	scoreMax = findMaxOfCol(scoreMat, j, i);

	string strVback = strV.substr(0, i);
	string strWback = strW.substr(0, j);

	while (i!=0 && j!=0)
	{
		if (backTrack[i][j]=='d')
		{
			i--;
			strWback = strWback.substr(0, j) + string(1, '-') + strWback.substr(j, strWback.length() - j);
		}
		else if (backTrack[i][j]=='r')
		{
			j--;
			strVback = strVback.substr(0, i) + string(1, '-') + strVback.substr(i, strVback.length() - i);
		}
		else
		{
			i--;
			j--;
		}
	}

	strVback = strVback.substr(i, strVback.length() - i);
	vector<string> outputStr;
	outputStr.push_back(strVback);
	outputStr.push_back(strWback);
	return outputStr;
}

vector<string> OverlapAlignmentProblem(string strV, string strW, int& scoreMax)
{
	PAIR idxScoreMax = PAIR(-1, -1);
	scoreMax = INT_MIN;
	int vLen = strV.length();
	int wLen = strW.length();
	vector<vector<int>> scoreMat(vLen + 1, vector<int>(wLen + 1, 0));
	vector<string> backTrack(vLen + 1, string(wLen + 1, ' '));
	for (int i = 1; i < vLen + 1; i++)
	{
		for (int j = 1; j < wLen + 1; j++)
		{
			int match = -2;
			if (strV.at(i - 1) == strW.at(j - 1))
			{
				match = 1;
			}
			vector<int> tmp;
			tmp.push_back(scoreMat[i - 1][j] - 2);
			tmp.push_back(scoreMat[i][j - 1] - 2);
			tmp.push_back(scoreMat[i - 1][j - 1] + match);
			int idxTmp;
			scoreMat[i][j] = findMax(tmp, 3, idxTmp);

			if (i==vLen || j==wLen)
			{
				if (scoreMat[i][j]>=scoreMax)
				{
					scoreMax = scoreMat[i][j];
					idxScoreMax.first = i;
					idxScoreMax.second = j;
				}
			}

			switch (idxTmp)
			{
			case 0:
				backTrack[i][j] = 'd';
				break;
			case 1:
				backTrack[i][j] = 'r';
				break;
			default:
				backTrack[i][j] = 'c';
			}
		}
	}

	int i = idxScoreMax.first;
	int j = idxScoreMax.second;
	string strVback = strV.substr(0, i);
	string strWback = strW.substr(0, j);

	while (i != 0 && j != 0)
	{
		if (backTrack[i][j] == 'd')
		{
			i--;
			strWback = strWback.substr(0, j) + string(1, '-') + strWback.substr(j, strWback.length() - j);
		}
		else if (backTrack[i][j] == 'r')
		{
			j--;
			strVback = strVback.substr(0, i) + string(1, '-') + strVback.substr(i, strVback.length() - i);
		}
		else
		{
			i--;
			j--;
		}
	}

	strVback = strVback.substr(i, strVback.length() - i);
	strWback = strWback.substr(j, strWback.length() - j);

	vector<string> outputStr;
	outputStr.push_back(strVback);
	outputStr.push_back(strWback);
	return outputStr;
}

vector<string> AffineGapPenaltiesProblem(string strV, string strW,
	string scoringChar, vector<vector<int>> scoringMat, int& scoreMax)
{
	int gapOpening = 11, gapExtension=1;
	int vLen = strV.length();
	int wLen = strW.length();
	vector<vector<int>> lowerMat(vLen + 1, vector<int>(wLen + 1, 0));
	vector<vector<int>> upperMat(vLen + 1, vector<int>(wLen + 1, 0));
	vector<vector<int>> midMat(vLen + 1, vector<int>(wLen + 1, 0));
	vector<string> backTrack(vLen + 1, string(wLen + 1, ' '));

	for (int i = 1; i < vLen + 1; i++)
	{
		for (int j = 1; j < wLen + 1;j++)
		{
			int idx1 = scoringChar.find(strV.at(i - 1));
			int idx2 = scoringChar.find(strW.at(j-1));
			int match = scoringMat[idx1][idx2];
			lowerMat[i][j] = findMaxOf2(lowerMat[i - 1][j] - gapExtension, midMat[i - 1][j] - gapOpening);
			upperMat[i][j] = findMaxOf2(upperMat[i][j - 1] - gapExtension, midMat[i][j - 1] - gapOpening);
			vector<int> tmp;
			tmp.push_back(lowerMat[i][j]);
			tmp.push_back(upperMat[i][j]);
			tmp.push_back(midMat[i - 1][j - 1] + match);
			int idxTmp;
			midMat[i][j] = findMax(tmp, 3, idxTmp);
			switch (idxTmp)
			{
			case 0:
				backTrack[i][j] = 'd';
				break;
			case 1:
				backTrack[i][j] = 'r';
				break;
			default:
				backTrack[i][j] = 'c';
			}
		}
	}

	scoreMax = midMat[vLen][wLen];
	int i = vLen;
	int j = wLen;
	string strVback = strV;
	string strWback = strW;
	while (i!=0 && j!=0)
	{
		if (backTrack[i][j]=='d')
		{
			i--;
			strWback = strWback.substr(0, j) + string(1, '-') + strWback.substr(j, strWback.length() - j);
		}
		else if (backTrack[i][j]=='r')
		{
			j--;
			strVback = strVback.substr(0, i) + string(1, '-') + strVback.substr(i, strVback.length() - i);
		}
		else
		{
			i--;
			j--;
		}
	}
	vector<string> outputStrs;
	outputStrs.push_back(strVback);
	outputStrs.push_back(strWback);
	return outputStrs;
}

vector<string> MultipleLstCommonSubseqProblem(string strV, string strW, string strU, int& scoreMax)
{
	int matches = 1, miasmatches = 0, sigma=0;
	
	int vLen = strV.length();
	int wLen = strW.length();
	int uLen = strU.length();

	vector<vector<vector<int>>> scoreMat(vLen + 1, vector<vector<int>>(wLen + 1, vector<int>(uLen+1, 0)));
	vector<vector<vector<int>>> backTrackInt(vLen + 1, vector<vector<int>>(wLen + 1, vector<int>(uLen + 1, 0)));

	for (int i = 1; i < vLen + 1;i++)
	{
		for (int j = 1; j < wLen + 1;j++)
		{
			for (int k = 1; k < uLen + 1;k++)
			{
				int m = (strV.at(i - 1) == strW.at(j - 1) && strW.at(j - 1) == strU.at(k - 1)) ? matches : -miasmatches;
				vector<int> tmp;
				tmp.push_back(scoreMat[i - 1][j][k] - sigma);
				tmp.push_back(scoreMat[i][j - 1][k] - sigma);
				tmp.push_back(scoreMat[i][j][k - 1] - sigma);
				tmp.push_back(scoreMat[i - 1][j][k - 1]);
				tmp.push_back(scoreMat[i][j - 1][k - 1] - sigma);
				tmp.push_back(scoreMat[i - 1][j - 1][k]);
				tmp.push_back(scoreMat[i - 1][j - 1][k - 1] + m);
				scoreMat[i][j][k] = findMax(tmp, 7, backTrackInt[i][j][k]);
			}
		}
	}
	scoreMax = scoreMat[vLen][wLen][uLen];
	int i = vLen, j = wLen, k = uLen;
	string strVback = strV;
	string strWback = strW;
	string strUback = strU;
	while (i!=0&&j!=0&&k!=0)
	{
		switch (backTrackInt[i][j][k])
		{
		case 0:
			i--;
			strWback = strWback.substr(0, j) + string(1, '-') + strWback.substr(j, strWback.length() - j);
			strUback = strUback.substr(0, k) + string(1, '-') + strUback.substr(k, strUback.length() - k);
			break;
		case 1:
			j--;
			strVback = strVback.substr(0, i) + string(1, '-') + strVback.substr(i, strVback.length() - i);
			strUback = strUback.substr(0, k) + string(1, '-') + strUback.substr(k, strUback.length() - k);
			break;
		case 2:
			k--;
			strVback = strVback.substr(0, i) + string(1, '-') + strVback.substr(i, strVback.length() - i);
			strWback = strWback.substr(0, j) + string(1, '-') + strWback.substr(j, strWback.length() - j);
			break;
		case 3:
			i--;
			k--;
			strWback = strWback.substr(0, j) + "-" + strWback.substr(j, strWback.length() - j);
			break;
		case 4:
			j--;
			k--;
			strVback = strVback.substr(0, i) + "-" + strVback.substr(i, strVback.length() - i);
			break;
		case 5:
			i--;
			j--;
			strUback = strUback.substr(0, k) + "-" + strUback.substr(k, strUback.length() - k);
		default:
			i--;
			j--;
			k--;
			break;
		}
	}
	vector<int> tmp2;
	tmp2.push_back(i); tmp2.push_back(j); tmp2.push_back(k);
	int maxLen = findMax(tmp2, 3);

	for (int m = i; m < maxLen;m++)
	{
		strVback = "-" + strVback;
	}
	for (int m = j; m < maxLen;m++)
	{
		strWback = "-" + strWback;
	}
	for (int m = k; m < maxLen;m++)
	{
		strUback = "-" + strUback;
	}

	vector<string> outputStr;
	outputStr.push_back(strVback);
	outputStr.push_back(strWback);
	outputStr.push_back(strUback);
	return outputStr;
}

vector<PAIR> MidEdgeLinearSpaceProblem(string strV, string strW,
	string scoringChar, vector<vector<int>> scoringMat, int sigma)
{
	int vLen = strV.length();
	int wLen = strW.length()/2;

	vector<vector<int>> scoreMat(vLen + 1, vector<int>(wLen + 1, 0));
	vector<string> backTrack(vLen + 1, string(wLen + 1, ' '));
	for (int i = 1; i < vLen + 1; i++)
	{
		scoreMat[i][0] = scoreMat[i-1][0]-sigma;
	}
	for (int j = 1; j < wLen + 1; j++)
	{
		scoreMat[0][j] = scoreMat[0][j-1]-sigma;
	}
	for (int i = 1; i < vLen + 1;i++)
	{
		for (int j = 1; j < wLen + 1;j++)
		{
			int idx1 = scoringChar.find(strV.at(i - 1));
			int idx2 = scoringChar.find(strW.at(j - 1));
			int match = scoringMat[idx1][idx2];
			vector<int> tmp;
			tmp.push_back(scoreMat[i - 1][j] - sigma);
			tmp.push_back(scoreMat[i][j - 1] - sigma);
			tmp.push_back(scoreMat[i - 1][j - 1] + match);
			int idxTmp;
			scoreMat[i][j] = findMax(tmp, 3, idxTmp);
			switch (idxTmp)
			{
			case 0:
				backTrack[i][j] = 'r';
				break;
			case 1:
				backTrack[i][j] = 'd';
				break;
			default:
				backTrack[i][j] = 'c';
				break;
			}
		}
	}

	int j = wLen;
	int i;
	findMaxOfCol(scoreMat, j, i);
	vector<PAIR> outputPairs;
	outputPairs.push_back(PAIR(i, j));
	switch (backTrack[i][j])
	{
	case 'r':
		outputPairs.push_back(PAIR(i+1, j));
		break;
	case 'd':
		outputPairs.push_back(PAIR(i, j + 1));
		break;
	default:
		outputPairs.push_back(PAIR(i+1, j + 1));
		break;
	}

	return outputPairs;
}

vector<string> LinearSpaceAlignment(string strV, string strW,
	string scoringChar, vector<vector<int>> scoringMat,
	int sigma, int& score)
{
	/*int lenV = strV.length();
	int lenW = strW.length();
	vector<vector<int>> s(lenV + 1, vector<int>(lenW+1, 0));
	vector<string> backTrack(lenV + 1, string(lenW + 1, ' '));

	for (int i = 1; i < lenV + 1;i++)
	{
		s[i][0] = s[i - 1][0]-sigma;
	}
	for (int j = 1; j < lenW;j++)
	{
		s[0][j] = s[0][j - 1] - sigma;
	}

	for (int i = 1; i < lenV + 1;i++)
	{
		for (int j = 1; j < lenW + 1;j++)
		{
			int idx1 = scoringChar.find(strV.at(i - 1));
			int idx2 = scoringChar.find(strW.at(j - 1));
			int match = scoringMat[idx1][idx2];
			vector<int> tmp;
			tmp.push_back(s[i - 1][j] - sigma);
			tmp.push_back(s[i][j-1] - sigma);
			tmp.push_back(s[i - 1][j-1] + match);
			int idxTmp;
			s[i][j] = findMax(tmp, 3, idxTmp);
			switch (idxTmp)
			{
			case 0:
				backTrack[i][j] = 'r';
				break;
			case 1:
				backTrack[i][j] = 'd';
				break;
			default:
				backTrack[i][j] = 'c';
				break;
			}
		}
	}
	score = s[lenV][lenW];

	int i = lenV;
	int j = lenW;
	string strVback = strV;
	string strWback = strW;
	while (i!=0 && j!=0)
	{
		if (backTrack[i][j] == 'd')
		{
			i--;
			strWback = strWback.substr(0, j) + string(1, '-') + strWback.substr(j, strWback.length() - j);
		}
		else if (backTrack[i][j] == 'r')
		{
			j--;
			strVback = strVback.substr(0, i) + string(1, '-') + strVback.substr(i, strVback.length() - i);
		}
		else
		{
			i--;
			j--;
		}
	}

	for (int m = i; m < lenV; m++)
	{
		strVback = "-" + strVback;
	}
	for (int m = j; m < lenW; m++)
	{
		strWback = "-" + strWback;
	}
	*/
	vector<string> outputStrs;
	//outputStrs.push_back(strVback);
	//outputStrs.push_back(strWback);
	return outputStrs;
}

string SequenceFormat(vector<int> p)
{
	string a;
	for (int j = 0; j < p.size(); j++)
	{
		if (p[j]>0)
			a.append("+");
		a.append(to_string(p[j]));
		if (j != p.size() - 1)
		{
			a.append(" ");
		}
	}
	return a;
}

vector<string> GreedySorting(vector<int> p, int& dist)
{
	vector<string> outSeq;
	int appRevDist = 0;
	for (int k = 0; k < p.size();k++)
	{
		if (p[k]!=k+1)
		{
			int idx;
			if (Belong2PepValues(k + 1, p, idx))
				;
			else
				Belong2PepValues(-k - 1, p, idx);
			vector<int> pBack=p;
			for (int m = k, n=idx; m < idx + 1;m++,n--)
			{
				p[m] = -pBack[n];
			}
			pBack.clear(); pBack.shrink_to_fit();
			appRevDist++;
			outSeq.push_back(SequenceFormat(p));
		}
		if (p[k]==-(k+1))
		{
			p[k] = -p[k];
			appRevDist++;
			outSeq.push_back(SequenceFormat(p));
		}
	}
	dist = appRevDist;
	return outSeq;
}

int NumberOfBreakpoints(vector<int> p)
{
	int  breakpoints = 0;
	for (int k = 0; k < p.size();k++)
	{
		if (k==0&&p[k]!=1)
		{
			breakpoints++;
		}
		if (k==p.size()-1&&p[k]!=p.size())
		{
			breakpoints++;
		}
		if (k<p.size()-1&&p[k+1]-p[k]!=1)
		{
			breakpoints++;
		}
	}
	return breakpoints;
}

vector<int> ChromosomeToCycle(vector<int> chromosome)
{
	vector<int> nodes = vector<int>(chromosome.size()*2, 0);
	for (int j = 0; j < chromosome.size();j++)
	{
		int i = chromosome[j];
		if (i>0)
		{
			nodes[2 * j] = 2 * i - 1;
			nodes[2 * j + 1] = 2 * i;
		}
		else
		{
			nodes[2 * j] = -2 * i;
			nodes[2 * j + 1] = -2 * i - 1;
		}
	}
	return nodes;
}

vector<int> CycleToChromosome(vector<int> nodes)
{
	vector<int> chromosome = vector<int>(nodes.size()/2, 0);
	for (int j = 0; j < nodes.size() / 2;j++)
	{
		if (nodes[2*j]<nodes[2*j+1])
		{
			chromosome[j] = nodes[2 * j + 1] / 2;
		}
		else
		{
			chromosome[j] = - nodes[2 * j] / 2;
		}
	}
	return chromosome;
}

vector<PAIR> ColoredEdges(vector<vector<int>> genome)
{
	vector<PAIR> coloredEdges;

	for (int i = 0; i < genome.size();i++)
	{
		vector<int> chromosome = genome[i];
		vector<int> nodes = ChromosomeToCycle(chromosome);
		for (int j = 0; j < chromosome.size();j++)
		{
			if (2 * (j + 1)<nodes.size())
			{
				coloredEdges.push_back(PAIR(nodes[2 * j + 1], nodes[2 * (j + 1)]));
			}
			else
			{
				coloredEdges.push_back(PAIR(nodes[2 * j + 1], nodes[0]));
			}
		}
	}

	return coloredEdges;
}

vector<vector<int>> GraphToGenome(vector<PAIR> edges)
{
	vector<vector<int>> cycles(1);
	for (int i = 0; i < edges.size();i++)
	{
		if (edges[i].first>edges[i].second)
		{
			cycles[cycles.size() - 1].push_back(edges[i].first);
			cycles[cycles.size() - 1].insert(cycles[cycles.size() - 1].begin(), edges[i].second);
			cycles.push_back(vector<int>(0));
		}
		else
		{
			cycles[cycles.size() - 1].push_back(edges[i].first);
			cycles[cycles.size() - 1].push_back(edges[i].second);
		}
	}
	cycles.pop_back();

	vector<vector<int>> genome;
	for (int i = 0; i < cycles.size();i++)
	{
		vector<int> nodes = cycles[i];
		genome.push_back(CycleToChromosome(nodes));
	}
	return genome;
}

int TwoBreakDistance(vector<vector<int>> genoP, vector<vector<int>> genoQ)
{
	vector<PAIR> redEdges = ColoredEdges(genoP);
	vector<PAIR> blueEdges = ColoredEdges(genoQ);
	vector<PAIR> allEdges = redEdges;
	for (int i = 0; i < blueEdges.size();i++)
	{
		allEdges.push_back(blueEdges[i]);
	}
	map<int, vector<int>>nodeMaps;
	map<int, vector<int>>::iterator dicIter;

	for (int i = 0; i < allEdges.size();i++)
	{
		int a = allEdges[i].first;
		dicIter = nodeMaps.find(a);
		if (dicIter==nodeMaps.end())
		{
			nodeMaps.insert(pair<int, vector<int>>(a, vector<int>(1, allEdges[i].second)));
		}
		else
		{
			dicIter->second.push_back(allEdges[i].second);
		}

		int b = allEdges[i].second;
		dicIter = nodeMaps.find(b);
		if (dicIter == nodeMaps.end())
		{
			nodeMaps.insert(pair<int, vector<int>>(b, vector<int>(1, allEdges[i].first)));
		}
		else
		{
			dicIter->second.push_back(allEdges[i].first);
		}
	}
	int	cycleCounts = 0;
	int startNode, nextNode, nextNode1;
	while (true)
	{
		vector<int> keyNode;
		for (dicIter = nodeMaps.begin(); dicIter != nodeMaps.end();dicIter++)
		{
			if (dicIter->second.size()>0)
			{
				keyNode.push_back(dicIter->first);
			}
		}
		if (keyNode.size()==0)
		{
			break;
		}
		startNode = keyNode[0];
		dicIter = nodeMaps.find(startNode);
		nextNode = dicIter->second[0];
		dicIter->second.erase(dicIter->second.begin());
		dicIter = nodeMaps.find(nextNode);
		int idx;
		Belong2PepValues(startNode, dicIter->second, idx);
		dicIter->second.erase(dicIter->second.begin()+idx);
		cycleCounts++;
		while (nextNode!=startNode)
		{
			dicIter = nodeMaps.find(nextNode);
			nextNode1 = dicIter->second[0];
			dicIter->second.erase(dicIter->second.begin());
			dicIter = nodeMaps.find(nextNode1);
			Belong2PepValues(nextNode, dicIter->second, idx);
			dicIter->second.erase(dicIter->second.begin()+idx);
			nextNode = nextNode1;
		}
	}
	int dis = redEdges.size()-cycleCounts;
	return dis;
}

vector<PAIR> TwoBreakOnGenomeGraph(vector<PAIR> genomeEdges, int i1, int i2,int i3,int i4)
{
	int n = genomeEdges.size();
	int i = 0;
	while (i<n)
	{
		if (
			(i1 == genomeEdges[i].first ||
			i1 == genomeEdges[i].second)
			&&
			(i2 == genomeEdges[i].first ||
			i2 == genomeEdges[i].second)
			)
		{
			genomeEdges[i] = PAIR(i2, i4);
		}
		else if (
			(i3 == genomeEdges[i].first ||
			i3 == genomeEdges[i].second)
			&&
			(i4 == genomeEdges[i].first ||
			i4 == genomeEdges[i].second)
			)
		{
			genomeEdges[i] = PAIR(i1, i3);
		}
		else
		{
			i++;
		}
	}
	return genomeEdges;
}

vector<PAIR> BlackEdges(int n)
{
	vector<PAIR> edges;
	for (int i = 1; i <= n;i++)
	{
		PAIR edge(2*i-1, 2*i);
		edges.push_back(edge);
	}
	return edges;
}

vector<vector<int>> RedBlueCycles(vector<PAIR> red, vector<PAIR> blue)
{
	vector<vector<int>> cycles;
	int blocks = red.size() + blue.size();
	map<int, int>::iterator itr;
	map<int, int> redAl;
	for (int i = 0; i < red.size();i++)
	{
		redAl.insert(pair<int, int>(red[i]));
		redAl.insert(pair<int, int>(red[i].second, red[i].first));
	}
	map<int, int> blueAl;
	for (int i = 0; i < blue.size();i++)
	{
		blueAl.insert(pair<int, int>(blue[i]));
		blueAl.insert(pair<int, int>(blue[i].second, blue[i].first));
	}
	map<int, char>visited;
	map<int, char>::iterator visitIter;
	for (int node = 1; node < blocks;node++)
	{
		visitIter = visited.find(node);
		if (visitIter==visited.end())
		{
			visited.insert(pair<int, char>(node, 'V'));
			vector<int> cycle(1,node);
			char color = 'R';
			while (true)
			{
				if (color=='R')
				{
					node = redAl[node];
					color = 'B';
				}
				else if (color=='B')
				{
					node = blueAl[node];
					color = 'R';
				}

				if (node==cycle[0])
				{
					cycles.push_back(cycle);
					break;
				}
				cycle.push_back(node);
				visited[node] = 'V';
			}
		}
	}
	return cycles;
}

vector<vector<int>> TwoBreakOnGenome(vector<vector<int>> genome, 
	int i1, int i2, int i3, int i4)
{
	int n = genome[0].size();
	vector<PAIR> bEdges = BlackEdges(n);
	vector<PAIR> cEdges = ColoredEdges(genome);
	cEdges = TwoBreakOnGenomeGraph(cEdges, i1, i2, i3, i4);
	vector<vector<int>> cycles = RedBlueCycles(bEdges, cEdges);

	vector<vector<int>> p;

	for (int i = 0; i < cycles.size();i++)
	{
		vector<int> chromosome = CycleToChromosome(cycles[i]);
		p.push_back(chromosome);
	}

	return p;
}

vector<vector<int>> ColoredEdgesCycles(vector<PAIR> edgesP, vector<PAIR> edgesQ)
{
	int edgeLen = edgesP.size() + edgesQ.size()+1;
	vector<vector<int>> adjMat(edgeLen, vector<int>(2,0));
	vector<int> visited(edgeLen, 0);
	for (int i = 0; i < edgesP.size();i++)
	{
		adjMat[edgesP[i].first][0] = edgesP[i].second;
		adjMat[edgesP[i].second][0] = edgesP[i].first;
	}
	for (int i = 0; i < edgesQ.size();i++)
	{
		adjMat[edgesQ[i].first][1] = edgesQ[i].second;
		adjMat[edgesQ[i].second][1] = edgesQ[i].first;
	}
	vector<vector<int>> cycles;
	for (int visit = 1; visit < edgeLen;visit++)
	{
		if (visited[visit]==1)
		{
			continue;
		}
		visited[visit] = 1;
		int head = visit;
		vector<int> cycle(1, head);
		int color = 0;
		while (true)
		{
			visit = adjMat[visit][color];
			if (visit==head)
			{
				cycles.push_back(cycle);
				break;
			}
			visited[visit] = 1;
			cycle.push_back(visit);
			color = (color + 1) % 2;
		}
	}
	return cycles;
}

vector<vector<vector<int>>> TwoBreakSorting(vector<vector<int>> genoP, vector<vector<int>> genoQ)
{
	vector<PAIR> edgesP;
	vector<PAIR> edgesQ = ColoredEdges(genoQ);
	vector<vector<vector<int>>> sequence;
	sequence.push_back(genoP);
	while (TwoBreakDistance(genoP, genoQ) > 0)
	{
		edgesP = ColoredEdges(genoP);
		vector<vector<int>> Cycles = ColoredEdgesCycles(edgesP, edgesQ);
		for (int i = 0; i < Cycles.size();i++)
		{
			vector<int> cycle = Cycles[i];
			if (cycle.size()>=4)
			{
				genoP = TwoBreakOnGenome(genoP, cycle[0], cycle[1], cycle[2], cycle[3]);
				sequence.push_back(genoP);
				break;
			}
		}
	}
	return sequence;
	//vector<PAIR> blue = ColoredEdges(genoQ);
	//bool noTrivialFlag = true;
	//vector<vector<vector<int>>> sequence;
	//sequence.push_back(genoP);
	//while (noTrivialFlag)
	//{
	//	vector<PAIR> red = ColoredEdges(genoP);
	//	vector<vector<int>> cycles = RedBlueCycles(red, blue);
	//	int cycNum = cycles.size();
	//	for (int i = 0; i < cycNum;i++)
	//	{
	//		vector<int> cycle = cycles[i];
	//		if (cycle.size()>=4)
	//		{
	//			genoP = TwoBreakOnGenome(genoP, cycle[0], cycle[1], cycle[3], cycle[2]);
	//			sequence.push_back(genoP);
	//			break;
	//		}
	//	}
	//	int dis = TwoBreakDistance(genoP, genoQ);
	//	if (dis==0)
	//	{
	//		noTrivialFlag = false;
	//	}
	//}
	//return sequence;
}

vector<PAIR> SharedKmersProblem(int k, string seq1, string seq2)
{
	vector<PAIR> sharedKmers;
	for (int i = 0; i < seq1.length() - k + 1;i++)
	{
		for (int j = 0; j < seq2.length() - k + 1;j++)
		{
			if (seq1.substr(i, k) == seq2.substr(j, k)
				|| TeverseComplement(&(seq1.substr(i, k))) == seq2.substr(j, k))
			{
				sharedKmers.push_back(PAIR(i, j));
			}
		}
	}
	return sharedKmers;
}

int findSumOfCost(map<PAIR, int>& in)
{
	int sum = 0;
	map<PAIR, int>::iterator inIter;
	for (inIter = in.begin(); inIter != in.end();inIter++)
	{
		sum += inIter->second;
	}
	return sum;
}

void DepthFirst(vector<int> nodes, CountTable adjList, vector<int> weightList, vector<int> leaves,
	int leafnode, int leafnextnode, vector<int>& visited, 
	map<PAIR, int>& cost, vector<PATH>& visitPaths)
{
	map<PAIR, int>::iterator costIter;
	if (!Belong2PepValues(leafnextnode, visited))
	{
		visited.push_back(leafnextnode);
		for (int i = 0; i < adjList.size(); i++)
		{
			if (nodes[adjList[i].first] == leafnode &&
				nodes[adjList[i].second] == leafnextnode)
			{
				cost.insert(pair<PAIR, int>(PAIR(leafnode, leafnextnode), weightList[i]));
			}
		}
		if (Belong2PepValues(leafnextnode, leaves))
		{
			PATH onePath;
			onePath.nextNode = leafnextnode;
			onePath.nodeList = vector<int>(visited.begin() + 1, visited.end());
			onePath.costSum = findSumOfCost(cost);
			visitPaths.push_back(onePath);
		}
		for (int i = 0; i < adjList.size();i++)
		{
			if (nodes[adjList[i].first] == leafnextnode)
			{
				int n = nodes[adjList[i].second];
				DepthFirst(nodes, adjList, weightList, leaves,
					leafnextnode, n, visited,
					cost, visitPaths);
			}
		}
		int idx;
		Belong2PepValues(leafnextnode, visited, idx);
		visited.erase(visited.begin()+idx);
		costIter = cost.find(PAIR(leafnode, leafnextnode));
		costIter->second = 0;
	}
	if (visitPaths.size()>0)
	{
		sort(visitPaths.begin(), visitPaths.end(), pathcmp());
	}
}

vector<vector<int>> DistanceBetweenLeaves(int n, 
	vector<int> nodes, vector<int> weightList, CountTable adjList)
{
	vector<vector<int>> disMat(n, vector<int>(n, 0));
	NodeDegreeChart degrees = GraphDegrees(adjList, nodes.size());
	vector<int> leaves;
	for (int i = 0; i < degrees.size();i++)
	{
		if (degrees[i]==PAIR(1, 1))
		{
			leaves.push_back(nodes[i]);
		}
	}
	sort(leaves.begin(), leaves.end());
	for (int i = 0; i < leaves.size();i++)
	{
		int leaf = leaves[i];
		vector<int> visited(leaves.begin(), leaves.begin()+i+1);
		vector<PATH> leafPaths;
		map<PAIR, int> costMap;

		int nextLeaf;
		for (int j = 0; j < adjList.size();j++)
		{
			if (nodes[adjList[j].first] == leaf)
			{
				nextLeaf = nodes[adjList[j].second];
				break;
			}
		}
		DepthFirst(nodes, adjList, weightList, leaves,
			leaf, nextLeaf, visited,
			costMap, leafPaths);
		//
		vector<PATH> totalPath = leafPaths;
		PATH onePath;
		onePath.nextNode = leaf;
		onePath.costSum = 0;
		totalPath.insert(totalPath.begin(), onePath);
		for (int i = 0; i < totalPath.size(); i++)
		{
			disMat[leaf][totalPath[i].nextNode] = totalPath[i].costSum;
			disMat[totalPath[i].nextNode][leaf] = totalPath[i].costSum;
		}
	}

	return disMat;
}

int LimbLengthProblem(int n, int j, vector<vector<int>> disMat)
{
	int limbLen = INT_MAX;

	for (int i = 0; i < n;i++)
	{
		for (int k = i + 1; k < n;k++)
		{
			if (i!=j && k!=j)
			{
				int val = (disMat[i][j] + disMat[k][j] - disMat[i][k]) / 2;
				if (val<limbLen)
				{
					limbLen = val;
				}
			}
		}
	}

	return limbLen;
}

PAIR TwoLeavesCondition(vector<vector<int>> disMat, int n)
{
	for (int i = 0; i < n;i++)
	{
		for (int k = i + 1; k < n;k++)
		{
			if (disMat[i][k]==disMat[i][n-1]+disMat[n-1][k])
			{
				return PAIR(i,k);
			}
		}
	}
}

vector<int> BreathFirst(TREE t, int x, int i, int k)
{
	vector<vector<int>> que(1, vector<int>(1, i));
	vector<int> visited(1, i);
	vector<int> actualPath;
	while (que.size()>0)
	{
		vector<int> path = que[que.size()-1];
		que.pop_back();
		int node = path[path.size() - 1];
		if (!Belong2PepValues(node, visited))
		{
			visited.push_back(node);
		}
		if (node==k)
		{
			actualPath = path;
			break;
		}
		map<int, vector<PAIR>>::iterator edgeIter;
		edgeIter = t.edges.find(node);
		for (int i = 0; i < edgeIter->second.size(); i++)
		{
			PAIR nextnode = edgeIter->second[i];
			if (!Belong2PepValues(nextnode.first, visited))
			{
				vector<int> tmp = path;
				tmp.push_back(nextnode.first);
				que.push_back(tmp);
			}
		}
	}
	int w;
	int cost = 0;
	for (int n = 0; n < actualPath.size() - 1;n++)
	{
		int i = actualPath[n];
		int j = actualPath[n + 1];
		map<int, vector<PAIR>>::iterator edgeIter;
		edgeIter = t.edges.find(i);
		
		for (int m = 0; m < edgeIter->second.size();m++)
		{
			if ((edgeIter->second)[m].first==j)
			{
				w = (edgeIter->second)[m].second;
				break;
			}
		}
		if (cost + w > x)
		{
			vector<int> tmp(4, 0);
			tmp[0] = i;
			tmp[1] = j;
			tmp[2] = x - cost;
			tmp[3] = cost + w - x;
			return tmp;
		}
		cost += w;
	}

	vector<int> breOut;
	return breOut;
}

pair<TREE, int> AdditivePhylogeny(int innerStart, vector<vector<int>> disMat)
{
	int n = disMat.size();
	if (n==2)
	{
		TREE tree;
		tree.Link(0, 1, disMat[0][1]);
		return pair<TREE, int>(tree, innerStart);
	}
	int limb = LimbLengthProblem(n, n - 1, disMat);
	for (int j = 0; j < n - 1;j++)
	{
		disMat[j][n - 1] -= limb;
		disMat[n - 1][j] = disMat[j][n - 1];
	}
	PAIR idx = TwoLeavesCondition(disMat, n);
	int i = idx.first;
	int k = idx.second;
	int x = disMat[i][n - 1];
	for (int j = 0; j < n - 1;j++)
	{
		disMat[j].pop_back();
	}
	disMat.pop_back();

	pair<TREE, int> tmp = AdditivePhylogeny(innerStart, disMat);
	innerStart = tmp.second;
	TREE t = tmp.first;

	vector<int> breOut = BreathFirst(t, x, i, k);
	int v = breOut[0];
	if (breOut[2]!=0)
	{
		v = innerStart;
		innerStart += 1;
		t.Link(breOut[1], v, breOut[3]);
		t.Link(breOut[0], v, breOut[2]);
		t.Unlink(breOut[0], breOut[1]);
	}
	t.Link(v, n - 1, limb);
	return pair<TREE, int>(t, innerStart);
}

vector<string> AdditivePhylogenyProblem(int innerStart, vector<vector<int>> disMat)
{
	vector<string> outStr;
	pair<TREE, int> outPair = AdditivePhylogeny(innerStart, disMat);
	TREE t = outPair.first;
	t.NodesSort();
	for (int i = 0; i < t.nodes.size(); i++)
	{
		int node = t.nodes[i];
		map<int, vector<PAIR>>::iterator edgeIter;
		edgeIter = t.edges.find(node);
		if (edgeIter!=t.edges.end())
		{
			for (int j = 0; j < edgeIter->second.size();j++)
			{
				PAIR edge = (edgeIter->second)[j];
				string tmp = to_string(node) + "->" + to_string(edge.first) + ':' + to_string(edge.second);
				outStr.push_back(tmp);
			}
		}
	}
	return outStr;
}

PAIR ClosestClusters(DMAT d)
{
	vector<vector<float>> dmat = d.mat;
	float minDist = FLT_MAX;
	PAIR index;
	for (int i = 0; i < dmat.size();i++)
	{
		for (int j = 0; j < dmat[0].size();j++)
		{
			if (i!=j)
			{
				if (dmat[i][j]<minDist)
				{
					minDist = dmat[i][j];
					index = PAIR(d.index[i], d.index[j]);
				}
			}
		}
	}
	return index;
}

PAIR ClosestClustersIdx(DMAT d)
{
	vector<vector<float>> dmat = d.mat;
	float minDist = FLT_MAX;
	PAIR index;
	for (int i = 0; i < dmat.size(); i++)
	{
		for (int j = 0; j < dmat[0].size(); j++)
		{
			if (i != j)
			{
				if (dmat[i][j] < minDist)
				{
					minDist = dmat[i][j];
					index = PAIR(i, j);
				}
			}
		}
	}
	return index;
}

float FindMatValue(DMAT d, int i, int j)
{
	int idx1, idx2;
	Belong2PepValues(i, d.index, idx1);
	Belong2PepValues(j, d.index, idx2);
	return d.mat[idx1][idx2];
}

vector<string> UPGMA(int n, vector<vector<int>> disMat)
{
	int inner = n;
	map<int, int> clusters;
	map<int, int>::iterator cluIter;
	map<int, float> age;
	map<int, float>::iterator ageIter;
	map<int, vector<int>> adjList;
	map<int, vector<int>>::iterator adjIter;
	map<PAIR, float> weights;
	map<PAIR, float>::iterator weiIter;
	for (int i = 0; i < n; i++)
	{
		clusters.insert(pair<int, int>(i, 1));
		age.insert(pair<int, float>(i, 0));
		adjList.insert(pair<int, vector<int>>(i, vector<int>(0)));
	}
	DMAT d;
	d.mat = vector<vector<float>>(n, vector<float>(n,0));
	d.index = vector<int>(n, 0);
	for (int i = 0; i < n; i++)
	{
		d.index[i] = i;
		for (int j = 0; j < n;j++)
		{
			d.mat[i][j] = float(disMat[i][j]);
		}
	}

	while (clusters.size() > 1)
	{
		PAIR idx = ClosestClusters(d);
		int i = idx.first;
		int j = idx.second;
		cluIter = clusters.find(i);
		int ci = cluIter->second;
		cluIter = clusters.find(j);
		int cj = cluIter->second;
		int elements_count = ci + cj;
		vector<int> tmp = {i, j};
		adjList.insert(pair<int, vector<int>>(inner, tmp));
		adjIter = adjList.find(i);
		adjIter->second.push_back(inner);
		adjIter = adjList.find(j);
		adjIter->second.push_back(inner);

		weights.insert(pair<PAIR, float>(PAIR(inner, i),0));
		weights.insert(pair<PAIR, float>(PAIR(inner, j), 0));
		weights.insert(pair<PAIR, float>(PAIR(i, inner), 0));
		weights.insert(pair<PAIR, float>(PAIR(j, inner), 0));

		age.insert(pair<int, float>(inner, FindMatValue(d, i, j)/ 2));
		clusters.erase(i);
		clusters.erase(j);

		vector<float> newMatValue;
		for (cluIter = clusters.begin(); cluIter != clusters.end();cluIter++)
		{
			int m = cluIter->first;
			float newDis = (FindMatValue(d, i, m) * ci + FindMatValue(d, j, m) * cj) / elements_count;
			newMatValue.push_back(newDis);
		}
		int tmpIdx;
		Belong2PepValues(i, d.index, tmpIdx);
		d.index.erase(d.index.begin() + tmpIdx);
		d.mat.erase(d.mat.begin() + tmpIdx);
		for (int p = 0; p < d.mat.size();p++)
		{
			d.mat[p].erase(d.mat[p].begin() + tmpIdx);
		}
		Belong2PepValues(j, d.index, tmpIdx);
		d.index.erase(d.index.begin() + tmpIdx);
		d.mat.erase(d.mat.begin() + tmpIdx);
		for (int p = 0; p < d.mat.size(); p++)
		{
			d.mat[p].erase(d.mat[p].begin() + tmpIdx);
		}
		d.index.push_back(inner);
		for (int p = 0; p < newMatValue.size(); p++)
		{
			d.mat[p].push_back(newMatValue[p]);
		}
		newMatValue.push_back(0);
		d.mat.push_back(newMatValue);
		clusters.insert(pair<int, int>(inner, elements_count));
		inner++;
	}

	for (weiIter = weights.begin(); weiIter != weights.end(); weiIter++)
	{
		if (weiIter->second == 0)
		{
			int v = weiIter->first.first;
			int w = weiIter->first.second;
			map<PAIR, float>::iterator tmpIter = weights.find(PAIR(v, w));
			map<int, float>::iterator ageIter1 = age.find(v);
			map<int, float>::iterator ageIter2 = age.find(w);
			tmpIter->second = abs(ageIter1->second - ageIter2->second);
			tmpIter = weights.find(PAIR(w, v));
			tmpIter->second = abs(ageIter1->second - ageIter2->second);
		}
	}

	vector<string> outStr;
	for (weiIter = weights.begin(); weiIter != weights.end(); weiIter++)
	{
		string tmpstr = to_string(weiIter->first.first) +
			"->" + to_string(weiIter->first.second) + ':' +
			to_string(weiIter->second).substr(0, 5);
		outStr.push_back(tmpstr);
	}

	return outStr;
}

vector<float> TotalDistance(DMAT d)
{
	vector<float> dt;
	for (int i = 0; i < d.index.size();i++)
	{
		float sum=0;
		for (int j = 0; j < d.index.size();j++)
		{
			sum += d.mat[i][j];
		}
		dt.push_back(sum);
	}
	return dt;
}

DMAT Dstar(DMAT d, vector<float> td, int num)
{
	DMAT ds=d;
	for (int m = 0; m < d.index.size();m++)
	{
		for (int n = 0; n < d.index.size();n++)
		{
			int i = d.index[m];
			int j = d.index[n];
			if (j>i)
			{
				ds.mat[m][n] = (num - 2)*d.mat[m][n] - td[m] - td[n];
				ds.mat[n][m] = ds.mat[m][n];
			}
			
		}
	}
	return ds;
}

TREE NeighborJoining(DMAT d, vector<int> nodes)
{
	int n = d.index.size();
	if (n==2)
	{
		int k0 = d.index[0];
		int k1 = d.index[1];
		TREE t(true);
		t.Link(k0, k1, d.mat[0][1]);
		return t;
	}
	vector<float> td = TotalDistance(d);
	DMAT ds = Dstar(d, td, n);
	PAIR idx = ClosestClustersIdx(ds);
	int i = idx.first;
	int j = idx.second;
	int iIndex = d.index[i];
	int jIndex = d.index[j];
	float delta = (td[i] - td[j]) / (n - 2);
	float limbLengthi = 0.5*(d.mat[i][j] + delta);
	float limbLengthj = 0.5*(d.mat[i][j] - delta);
	vector<float> m;
	int inner = nodes[nodes.size() - 1] + 1;
	nodes.push_back(inner);
	for (int k = 0; k < d.index.size();k++)
	{
		float tp = 0.5*(d.mat[k][i] + d.mat[k][j] - d.mat[i][j]);
		//m.insert(pair<int, float>(d.index[k], tp));
		m.push_back(tp);
	}
	d.index.push_back(inner);
	if (i<j)
	{
		d.index.erase(d.index.begin() + i);
		d.index.erase(d.index.begin() + j - 1);
		for (int k = 0; k < d.mat.size(); k++)
		{
			d.mat[k].push_back(m[k]);
		}
		m.push_back(0);
		d.mat.push_back(m);

		d.mat.erase(d.mat.begin()+i);
		d.mat.erase(d.mat.begin() + j-1);
		for (int k = 0; k < d.mat.size(); k++)
		{
			d.mat[k].erase(d.mat[k].begin()+i);
			d.mat[k].erase(d.mat[k].begin() + j-1);
		}
	}
	else
	{
		d.index.erase(d.index.begin() + j);
		d.index.erase(d.index.begin() + i - 1);
		for (int k = 0; k < d.mat.size(); k++)
		{
			d.mat[k].push_back(m[k]);
		}
		m.push_back(0);
		d.mat.push_back(m);

		d.mat.erase(d.mat.begin() + j);
		d.mat.erase(d.mat.begin() + i - 1);
		for (int k = 0; k < d.mat.size(); k++)
		{
			d.mat[k].erase(d.mat[k].begin() + j);
			d.mat[k].erase(d.mat[k].begin() + i - 1);
		}
	}

	TREE t = NeighborJoining(d, nodes);
	t.Link(inner, iIndex, limbLengthi);
	t.Link(inner, jIndex, limbLengthj);

	return t;
}

vector<string> NeighborJoiningProblem(int n, vector<vector<int>> disMat)
{
	vector<int> nodes;
	DMAT dmat;
	dmat.mat = vector<vector<float>>(n, vector<float>(n, 0));
	for (int i = 0; i < n; i++)
	{
		nodes.push_back(i);
		for (int j = 0; j < n;j++)
		{
			dmat.mat[i][j] = disMat[i][j];
		}
	}
	dmat.index = nodes;

	TREE t = NeighborJoining(dmat, nodes);
	t.NodesSort();
	vector<string> outStr;
	for (int i = 0; i < t.nodes.size(); i++)
	{
		int node = t.nodes[i];
		map<int, vector<pair<int, float>>>::iterator edgeIter;
		edgeIter = t.edgesfloat.find(node);
		if (edgeIter != t.edgesfloat.end())
		{
			for (int j = 0; j < edgeIter->second.size(); j++)
			{
				pair<int, float> edge = (edgeIter->second)[j];
				string tmp = to_string(node) + "->" + to_string(edge.first) + ':' + to_string(edge.second);
				outStr.push_back(tmp);
			}
		}
	}
	return outStr;
}

NODETREE Format2Tree(int& m, vector<string> treeString)
{
	m = 0;
	NODETREE T;
	map<string, NODE> nodes;
	map<string, NODE>::iterator nodeIter;
	int i = 0; 
	for (int j = 0; j < treeString.size();j++)
	{
		int idx = treeString[j].find("->");
		string a = treeString[j].substr(0, idx);
		string b = treeString[j].substr(idx + 2, treeString[j].length() - idx - 2);
		NODE a_in_node(a);
		NODE b_in_node(b);
		// if a is digits
		if (IsDigits(a))
		{
			nodeIter = nodes.find(a);
			if (nodeIter!=nodes.end())
			{
				a_in_node = nodeIter->second;
			}
			else
			{
				a_in_node = NODE(a);
				nodes.insert(pair<string, NODE>(a, a_in_node));
			}
		}
		else
		{
			if (m==0)
			{
				m = a.length();
			}
			nodeIter = nodes.find(a);
			if (nodeIter != nodes.end())
			{
				a_in_node = nodeIter->second;
			}
			else
			{
				string i_str = to_string(i);
				a_in_node = NODE(i_str, a);
				i++;
				nodes.insert(pair<string, NODE>(a, a_in_node));
			}
		}

		// if b is digits
		if (IsDigits(b))
		{
			nodeIter = nodes.find(b);
			if (nodeIter != nodes.end())
			{
				b_in_node = nodeIter->second;
			}
			else
			{
				b_in_node = NODE(b);
				nodes.insert(pair<string, NODE>(b, b_in_node));
			}
		}
		else
		{
			if (m==0)
			{
				m = b.length();
			}
			nodeIter = nodes.find(b);
			if (nodeIter!=nodes.end())
			{
				b_in_node = nodeIter->second;
			}
			else
			{
				string i_str = to_string(i);
				b_in_node = NODE(i_str, b);
				i++;
				nodes.insert(pair<string, NODE>(b, b_in_node));
			}
		}
		a_in_node.children.push_back(b_in_node);
		b_in_node.parent = vector<NODE>(1,a_in_node);
		T.Link(a_in_node, b_in_node);
	}

	return T;
}

vector<string> SmallParsimony(int n, vector<string> treeString)
{
	int m;
	NODETREE T = Format2Tree(m, treeString);
	//
	vector<string> outStr;
	return outStr;
}