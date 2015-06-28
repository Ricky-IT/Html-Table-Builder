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
	Tag t{ "table", 'h' };
	kT.push_back(t);

	t = Tag{ "/table", 'h' };
	kT.push_back(t);

	t = Tag{ "tr", 'h' };
	kT.push_back(t);

	t = Tag{ "/tr", 'h' };
	kT.push_back(t);

	t = Tag{ "th", 'h' };
	kT.push_back(t);

	t = Tag{ "/th", 'h' };
	kT.push_back(t);

	t = Tag{ "td", 'h' };
	kT.push_back(t);

	t = Tag{ "/td", 'h' };
	kT.push_back(t);

	t = Tag{ "/tbody", 'h' };
	kT.push_back(t);

	t = Tag{ "tbody", 'h' };
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
		cout << "Insert the target tag (no < >) where the program have to began to read:"<<endl;
		cout << "**NOTE** If there is a <tbody> tag, use it istead of <table> (using <table> may cause some data los!)" << endl;
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



void SplitString(const string& tar, vector<string>& WTP, bool comma_split)
{
	string temp;
	stringstream ss{ tar};
	if (!comma_split)
	{
		while (ss >> temp)
		{
			WTP.push_back(temp);
		}
	}
	if (comma_split)
	{
		while (getline(ss, temp, ';')) 
		{
			WTP.push_back(temp);
		}
	}
}

//restituisce il numeri di righe e le righe
int getRows(const string& target, vector<string>& WTP)
{
	vector<string> split;
	SplitString(target, split, false);
	string temp{};

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
	CleanFile << "//\n";
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


// chiede all'utente da che tag vuole che il programma legga
string AskNewLayout(vector<string>& layCurrent)
{
	string target;
	do {
		cout << "Current Layout: ";
		for (auto e : layCurrent)
		{
			cout << e << " ";
		}
		cout << endl;

		cout << endl<<"Insert a new layout:" << endl;
		cout << "**NOTE** Layout MUST be: <new layout name>=<old layout name>(+\"Text\"+<another old layout name>+\"More Text\"). Use *none to create a empty column); and so on!" << endl;
		cout << "**NOTE** In new layout you MUST NOT use spaces!!" << endl;
		getline(cin, target);
	} while (target.find("<") != string::npos && target.find(">") != string::npos && target.find(";") != string::npos);

	return target;
}

//valuta il nuovo layout inserito ## h - tag html / l - layout / n - layout nuovo / o - layout vecchio / t - testo ##
void EvaluateLayout(const string& target, vector<vector<Tag>>& LayInfo)
{
	vector<string> nwLay;
	SplitString(target, nwLay, true);
	bool text = false;
	Tag temp{"",'o'};
	vector<Tag> line;

	for (auto item: nwLay)
	{
		for (int i = 0; i < item.length(); i++)
		{
			if (item[i] == '\"')
			{
				text = !text;
				//cout << "Text: " << text << endl;
			}
			

			if (text)
			{
				temp.type = 't';
			}


			if (item[i] != '\"' && item[i] != '+' && item[i] != '=')
			{
				temp.push(item[i]);
				//cout << "Temp.push: " <<item[i] << endl;
			}

			if (item[i] == '=')
			{
				temp.type = 'n';
				line.push_back(temp);
				//cout << "Pushed: " << temp.value << endl;
				temp.cleardata();
				temp.type = 'o';

			}

			if (item[i] == '+' || i + 1 >= item.length())
			{
				line.push_back(temp);
				//cout << "pushed 2: " << temp.value << endl;
				temp.cleardata();
				temp.type = 'o';

			}

		}
		//cout << "Push LINE" << endl;
		LayInfo.push_back(line);
		line.clear();
	}


	cout << "**DEBUG New Layout Info**" << endl;
	for (auto line : LayInfo)
	{
		for (auto item : line)
		{
			cout << "-" << item.value <<"  Tipo: "<< item.type<< "-   ";
		}
		cout << endl<<endl;
	}

}

//scrive il file output.html
void  WriteOutPut(vector<vector<Tag>>& LayInfo, vector<vector<string>>& data, vector<string>& Olay)
{
	ofstream Output;
	Output.open("Output.html");
	Output << "<html><head><title>Html Builed Table</title></head><body>"<<endl<<endl;
	Output << "<table>" << endl;
	string templ{};

	for (auto el : LayInfo)
	{
		Output << "<th>" + el[0].value + "</th>" << endl;
	}

	for (int i = 0; i < data.size(); i++)
	{
		Output << "<tr>" << endl;
		for (auto line : LayInfo) // per ogni elemento del nuovo layout
		{
			templ += "<td>";
			for (auto el : line) // leggi ogni linea
			{

				//cout << "Lunghezza: " << line.size() << endl;

				if (el.type != 'n')
				{
					
					//cout << "NewLine" << endl;
					if (el.type == 't') // se nella line ec'e un testo aggiungilo
					{
						templ += el.value;
						//cout << "Aggiunto testo: " << el.value<<endl;
					}
					if (el.type == 'o') // se nella linea c'e un richiamo al vecchio layout
					{
						int pos{ -1 };
						if (el.value != "*none")
						{
							for (int j = 0; j < Olay.size(); j++) // cercalo nel vecchio layout
							{
								if (Olay[j] == el.value) // se lo trovi ricardati la sua posizione
								{
									pos = j;
								}


							}
						}
						else
						{
							pos = -2;
							cout << "Empty column" << endl;
						}

						if (pos != -1 && pos != -2)
						{
							templ += data[i][pos];
							//cout << "Aggiunto " << data[i][pos] << endl;
						}
						if (pos == -1)
						{
							cout << "**ERROR** Cant find reference: " << el.value << endl;
						}
					}


				}

			}
			templ += "</td>\n";
			//cout << "Riga a fine ciclo linea: "<<templ << endl;
		}
		Output << templ;
		Output << "</tr>" << endl;
		templ = "";
	}

	Output <<"</table>" << endl;
	Output << endl << endl << "</body></html>";
	Output.close();
	cout << "Table result has been written in output.html" << endl;
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

	vector<vector<Tag>> LayInfo;

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
		string newLay = AskNewLayout(layout);
		EvaluateLayout(newLay, LayInfo);

		WriteOutPut(LayInfo,Table,layout);


	}


	char c;
	cout << "Press a button to exit (letter/number + escape) ";
	cin >> c;

}
