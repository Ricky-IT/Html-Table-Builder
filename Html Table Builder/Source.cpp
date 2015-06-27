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
		cout << "**LOG Code: ReadFile**Begin reading INPUT.TXT" << endl;
		ifstream f(path);
		string line{ "" };

		while (getline(f, line))
		{
			result += line;
		}
		cout << "**LOG Code: ReadFile**INPUT.TXT sucessfully read"<<endl;
	}
	else
	{
		cout << "**ERROR Code: ReadFile** File input.txt doesn't exist! Create it and fill it with html code to use!" << endl;
		result = "null";
	}

	return result;

}

// chiede all'utente da che tag vuole che il programma legga
string AskTarget()
{
	string target;
	do {
		cout << "Insert the target tag (no < >) where the program have to began to read: ";
		getline(cin, target);
	} while (target.find("<") != string::npos && target.find(">") != string::npos);

	return target;
}

// analizza un tag e trova di che tipo e' e restituisci l'oppsto
string CloseTag(const string& target, const vector<Tag>& list) 
{
	bool found = false;

	for (auto t : list)
	{
		if (target.find(t.value) != string::npos)
		{ 
			found = true;
			return "</" + t.value + ">";
		}
	}

	if (!found)
	{
		cout << "**ERROR Code: CloseTag** Unknown tag: " << target << endl<< "Maybe close tag is: </"<<target<<">"<<endl;
		return "</" + target + ">";
		
	}
}


//riduce la stringa al blocco interessato da analizzare
string targetString(const string& begin, const vector<Tag>& kt, const string& FC)
{   

	string closeT = CloseTag(begin, kt); // restituisce il tag di chiusura opposto a quello inserito

	int InitPos = FC.find(begin);
	int EndPos = FC.find(closeT);

	//valutazione dei risultati delle ricerche
	if (InitPos == string::npos)
	  {
		  cout << "**ERROR Code: TargetString** can't find: " << begin << endl;
	  }

	if (EndPos == string::npos)
	{
		cout << "**ERROR Code: TagetString** can't find: " << begin << endl;

	}
	if ((EndPos == string::npos || InitPos == string::npos) || (EndPos == string::npos && InitPos == string::npos))
	{
		return "null";
	}

	if (EndPos != string::npos && InitPos != string::npos) // se non ci sono errori copia la stringa da dove hai trovato il primo tag a dove hai trovato il secondo
	{
		string result;
		bool copy = false;
		cout << endl << "**DEBUG Code: TargetString** Begin: " << InitPos << " End: " << EndPos << endl << endl;
		for (int i = InitPos + begin.length() +1 ; i < EndPos; i++) // nella copia elimina tag di apertura
		{
			if (FC[i] == '<')
			{
				copy = true;
			}
			if (copy)
			{
				result += FC[i];
			}
		}
		return result;
	}
}


int main()
{
	vector<Tag> KnownTags;
	string FileContent;
	string TBegin{};
	string Content;

	DefineTableTags(KnownTags);

	FileContent = ReadFile();
	cout<<endl<<"**DEBUG** Content: " << FileContent<<endl<<endl;

	if (FileContent != "null")
	{
		TBegin = AskTarget();
		Content = targetString(TBegin, KnownTags, FileContent);
		if (Content != "null")
		{
			cout << endl << "**DEBUG** TargetList: " << Content << endl << endl;
			FileContent= "";
		}

	}


	char c;
	cout << "Press a button to exit (letter/number + escape) ";
	cin >> c;

}
