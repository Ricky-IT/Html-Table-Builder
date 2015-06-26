//
//  Main.cpp
//  Html Table Builder
//
//  Created by Paola Montanaro on 26/06/15.
//
//

#include "iostream"
#include "string"
#include "vector"
#include "Tag.h"
#include "fstream"

using namespace std;



//definisce tutti i tag html che riguardano le tabelle
void DefineTableTags(vector<Tag>& kT)
{
	Tag t{ "table", 't' };
	kT.push_back(t);

	t = Tag{ "/table", 't' };
	kT.push_back(t);

	t = Tag{ "tr", 't' };
	kT.push_back(t);

	t = Tag{ "/tr", 't' };
	kT.push_back(t);

	t = Tag{ "th", 't' };
	kT.push_back(t);

	t = Tag{ "/th", 't' };
	kT.push_back(t);

	t = Tag{ "td", 't' };
	kT.push_back(t);

	t = Tag{ "/td", 't' };
	kT.push_back(t);

}

//legge il file input.txt
string ReadFile()
{
	string result;
	string path{ "input.txt" };


	if (ifstream(path))
	{
		cout << "Begin reading INPUT.TXT" << endl;
		ifstream f(path);
		string line{ "" };

		while (getline(f, line))
		{
			result += line;
		}
		cout << "INPUT.TXT sucessfully read";
	}
	else
	{
		cout << "Error: File input.txt doesn't exist! Create it and fill it with html code to use!" << endl;
		result = "null";
	}

	return result;

}

// chiede all'utente da che tag vuole che il programma legga
string AskTarget()
{
	string target;
	do {
		cout << "Insert the target tag where the program have to began to read: ";
		getline(cin, target);
	} while (target.find("<") == string::npos || target.find(">") == string::npos);

	return target;
}


int main()
{
	vector<Tag> KnownTags;
	string FileContent;
	string TBegin{};

	DefineTableTags(KnownTags);

	FileContent = ReadFile();
	TBegin = AskTarget();

}
