#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

//was (vector<char *>, char)
bool IsIgnore(vector<string> ignore, vector<string> titles, string word)
{
	for (int i=0; i<ignore.size(); i++)
	{
		if (word == ignore[i]) return true;
	}
	for (int i=0; i<titles.size(); i++)
	{
		if (word == titles[i]) return true;
	}
	return false;
}

int main()
{
	char textLine[1000], outLine[1000];
	//char* token;
	fstream inFile("data.txt", ios::in);
	vector<string> toIgnore, titles;
	bool ignoreWords = true, indexed;
	string inLine, token;
	int tokenCount = 0, lastItr = -1;
	string outLines[100];

	while (!inFile.eof())
	{

		if (ignoreWords)
		{
			inFile >> textLine;
			if (textLine[0] == ':' && textLine[1] == ':')
			{
				ignoreWords = false;
				inFile.ignore();
			}
			else
			{
				toIgnore.push_back(textLine);
			}
		}
		else
		{
			getline(inFile, inLine);
			transform(inLine.begin(),inLine.end(),inLine.begin(),::tolower);
			istringstream counter(inLine);

			tokenCount = 0;
			while(counter>>token)
			{
				if (!IsIgnore(toIgnore, titles, token)) tokenCount++;
			}

			lastItr = 0;
			titles.clear();
			istringstream iss(inLine);
			for (int i=0; iss >> token; i++ )
			{
				if (!IsIgnore(toIgnore, titles, token))
				{
					outLines[i] = inLine;
					int outItr = outLines[i].find(token, max(lastItr, 0));
					lastItr = outItr + token.length();
					transform(token.begin(),token.end(),&outLines[i][outItr],::toupper);
					titles.push_back(token);

					cout << outLines[i] << endl;
					//titles.push_back(outLines[i]);
				}
				else
				{
					i--;
				}
			}
		}
	}

	return 0;
}
