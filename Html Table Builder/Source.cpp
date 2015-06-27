//***********************************************************************************************************************
//  
//  Html Table Builder
//  Developed by _Ricky
//  
//  Desc: Read html code from input.txt (next to exe file) analize it and create a new html table
//
//  **WARNING**
//  This program can't handle images and empty cells!!
//
//***********************************************************************************************************************

#include "iostream"
#include "string"
#include "vector"
#include "Tag.h"
#include "fstream"
#include "sstream"

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
		cout << "**WARNING** Unknown tag: " << target << endl<< "**WARNING** Maybe close tag is: </"<<target<<">"<<endl;
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
		cout << "**ERROR Code: TagetString** can't find: " << closeT << endl;

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


//legge una riga e cerca tutti i dati fuori dai tag (< >)
void GetData(vector<string>& WTP, const string& data)
{
	Tag temp{ "", 'd' };

	bool write;
	for (int i = 0; i < data.length(); i++)
	{
		if (data[i] == '<')
		{
			write = false;
		}

		if (write)
		{
			temp.push(data[i]);

			if (data[i + 1] == '<')
			{
				if (temp.value.find_first_not_of(' ') != string::npos) // controlla che la stringa non sia solo spazi
				{
					WTP.push_back(temp.value);
					temp.cleardata();
				}
				else
				{
					temp.cleardata();
				}
			}
		}

		if (data[i] == '>')
		{
			write = true;
		}

	}
}

// crea la lista di oggetti del layout tabella
int GetLayout(vector<string>& lay, const string& ct, const vector<Tag>& kt)
{
	string lyLine = targetString("tr", kt, ct);
	cout << endl << "**DEBUG** LayoutLine: " << lyLine << endl << endl;

	if (lyLine.find("td") != string::npos)
	{
		cout << "**WARNING GetLayout** Cant find layout! Using 1st line as layout!" << endl;

	}

	GetData(lay, lyLine);

	cout << "**DEBUG GetLayout (Elements: " << lay.size() << ")**" << endl;
	for (auto s : lay)
	{
		cout<<"-"<<s<<"-"<< "  ";
	}
	cout << endl << endl;

	return lyLine.length() + 12;
}



//restituisce il numeri di righe e le righe
int getRows(const string& target, vector<string>& WTP)
{
	vector<string> split;
	string temp;
	stringstream ss{ target };
	while (ss>>temp)
	{
		split.push_back(temp);
	}
	 
	int rows{ 0 };
	bool write = false;
	temp.clear();
	for (auto t : split)
	{
		//cout << "PEZZO: " << t<<endl;

		if (t == "</tr>")
		{
			write = false;
			WTP.push_back(temp);
			temp.clear();

		}
		if (write)
		{
			temp += t;
		}

		if (t.find ("<tr") != string::npos )
		{
			++rows;
			write =true;
		}
	}

	/*cout << "**DEBUG Code: Rows** " << endl;
	for (auto s : WTP)
	{
		cout << "-" << s << "-  ";
	}
	cout << endl << endl;*/

	return rows;
}

//legge tutti i dati e li carica in una pseudotabella
void CollectData(vector<vector<string>>& table,vector<string>& rows)
{
	vector < string > temp ;
	temp.clear();
	table.clear();
	for (auto line : rows)
	{
		GetData(temp, line);
		table.push_back(temp);
		temp.clear();
	}
	cout << "**DEBUG CollectData** Plain data" << endl;
	for (auto line : table)
	{
		for (auto item : line)
		{
			cout << "-" << item << "-   ";
		}
		cout<<endl;
	}

}

//genera file contente tutti i dati recuperati
void SaveCleanData(const vector<string>& layout, const vector<vector<string>>& table)
{
	ofstream CleanFile;
	CleanFile.open("CleanData.txt");
	CleanFile << "//Output File of Html Table builder\n";
	CleanFile << "//Developed by _Ricky\n";
	CleanFile << "//Warning this app can't handle tables with empty cells or images!!\n";
	CleanFile << "//\n";
	CleanFile << "Table layout:\n";
	string ly;
	for (auto e : layout)
	{
		ly += e + "  |  ";
	}
	CleanFile << ly<<endl;

	ly = "";
	CleanFile << "Table data:\n";
	for (auto line : table)
	{
		for (auto item : line)
		{
			ly += item + "  |  ";
		}
		CleanFile << ly<<endl;
		ly = "";
	}

	CleanFile.close();

	cout << "**LOG** Clean data was wrote into CleanData.txt" << endl;
}

int main()
{
	vector<Tag> KnownTags;
	string FileContent;
	string TBegin{};
	string Content;
	vector<string> layout;
	vector<vector<string>> Table;
	vector<string> rows;

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
			int endlayout = GetLayout(layout, Content, KnownTags);
			Content = Content.substr(endlayout);
			cout << endl << endl << "**DEBUG** Data only (deleted: "<< endlayout<<") :"<<Content<<endl<<endl;
		}

		int righe = getRows(Content, rows);
		cout <<"**DEBUG** Rows:" << righe << endl << endl;

		CollectData(Table, rows);

		SaveCleanData(layout, Table);


	}


	char c;
	cout << "Press a button to exit (letter/number + escape) ";
	cin >> c;

}
