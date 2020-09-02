#include "functions.h"

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