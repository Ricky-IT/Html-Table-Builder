#include "Html_Reader.h"

using namespace Html;

// analizza un tag e trova di che tipo e' e restituisci l'opposto
string Html_Reader::CloseTag(const string& target)
{
	bool found = false;

	for (auto tag : Costants::KnownTags)
	{
		if (target.find(tag) != string::npos)
		{
			found = true;
			return "</" + tag;
		}
	}

	if (!found)
	{
		cout << "**WARNING** Unknown tag: " << target << endl << "**WARNING** Maybe close tag is: </" << target << ">" << endl;
		return "</" + target;

	}

}
	//riduce la stringa al blocco interessato da analizzare
	string Html_Reader::targetString(const string& begin, const string& FC, int& lung, bool advanced)
	{

		string closeT = Html_Reader::CloseTag(begin); // restituisce il tag di chiusura opposto a quello inserito

		int InitPos = FC.find(begin);
		int EndPos = FC.find(closeT);

		//valutazione dei risultati delle ricerche
		if (InitPos == string::npos)
		{
			cout << "**ERROR** can't find: " << begin << endl;
		}

		if (EndPos == string::npos)
		{
			cout << "**ERROR** can't find: " << closeT << endl;

		}
		if ((EndPos == string::npos || InitPos == string::npos) || (EndPos == string::npos && InitPos == string::npos))
		{
			return "null";
		}

		if (EndPos != string::npos && InitPos != string::npos) // se non ci sono errori copia la stringa da dove hai trovato il primo tag a dove hai trovato il secondo
		{
			string result;
			bool copy = false;
			//	cout << endl << "**DEBUG Code: TargetString** Begin: " << InitPos << " End: " << EndPos << endl << endl;
			for (int i = InitPos + begin.length() + 1; i < EndPos; i++) // nella copia elimina tag di apertura
			{
				if (FC[i] == '<' || advanced)
				{
					copy = true;
				}
				if (copy)
				{
					result += FC[i];
				}
			}

			lung = EndPos - InitPos + closeT.length();

			return result;
		}

}


	// chiede all'utente da che tag vuole che il programma legga
	string Html_Reader::Datakind()
	{
		string target;
		do {
			cout << "Do you want clean data: yes/no" << endl;
			cout << "**NOTE** This means no html tags inside table data! (This fuction is not really stable and can lose data! Its reccommend to use the standard one!)" << endl;
			getline(cin, target);

			if (target == "yes" || target == "no")
				break;
			//cout<<"-"<<target<<"-"<<endl;
		} while (true);

		if (target == "yes")
		{
			cout << "Using default separator: <br >" << endl;
			target = "<br >";
		}
		else target = "null";

		return target;
	}

	//legge tutti i dati e li carica in una pseudotabella
	void Html_Reader::CollectData(vector<vector<string>>& table, vector<string>& rows, int lylung)
	{
		vector < string > temp;
		temp.clear();
		table.clear();
		int cont = { 0 };

		string separator;

		separator = Html_Reader::Datakind();

		for (auto line : rows)
		{
			cout << cont << "- ";
			GetDataAdvanced(temp, line, lylung, separator);
			if (temp.size()>0)
				table.push_back(temp);

			temp.clear();
			cont++;
		}
		/*cout << "**DEBUG CollectData** Plain data" << endl;
		for (auto line : table)
		{
		for (auto item : line)
		{
		cout << "-" << item << "-   ";
		}
		cout<<endl;
		}*/

	}


	//legge una riga e cerca tutti i dati fuori dai tag (< >)
	void Html_Reader::GetData(vector<string>& WTP, const string& data)
	{
		string temp{ "" };
		int timer{ 0 };
		bool write = true;
		for (int i = 0; i < data.length(); i++)
		{
			if (data[i] == '<')
			{
				write = false;
			}
			// controlla che se è presente <td></td> aggiunge un dato vuoto
			if (data[i] == '<' && data[i + 1] == 't' && data[i + 2] == 'd' && data[i + 3] == '>' && data[i + 4] == '<' && data[i + 5] == '/' && data[i + 6] == 't' && data[i + 7] == 'd' && data[i + 8] == '>')
			{
				WTP.push_back("");
			}


			if (write)
			{
				temp += data[i];

				if (data[i + 1] == '<')
				{
					bool space = true;
					/*for (auto el : temp.value)
					{
					if (!isspace(el))
					{
					space = false;
					}


					}*/

					if (temp.find_first_not_of(' ') != string::npos)
					{
						space = false;
					}

					if (!space) // controlla che la stringa non sia solo spazi
					{
						WTP.push_back(temp);
						//cout<<"**GetData** Got: -"<<temp.value<<" from: "<<data<<endl;
						temp = "";
					}
					else
					{
						temp = "";
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
	int Html_Reader::GetLayout(vector<string>& lay, const string& ct)
	{
		int lung{ 0 };
		string lyLine = Html_Reader::targetString("tr", ct, lung, false);
		cout << endl << "**DEBUG** LayoutLine: " << lyLine << endl << endl;

		if (lyLine.find("td") != string::npos)
		{
			cout << "**WARNING** Cant find layout! Using 1st line as layout!" << endl;

		}

		GetData(lay, lyLine);

		cout << "**DEBUG** GetLayout (Elements: " << lay.size() << ")" << endl;
		for (auto s : lay)
		{
			cout << "-" << s << "-" << "  ";
		}
		cout << endl << endl;

		return lung;
	}



	void Html_Reader::SplitString(const string& tar, vector<string>& WTP, bool bar_split)
	{
		string temp;
		stringstream ss{ tar };
		if (!bar_split)
		{
			while (ss >> temp)
			{
				WTP.push_back(temp);
			}
		}
		if (bar_split)
		{
			while (getline(ss, temp, '|'))
			{
				WTP.push_back(temp);
			}
		}

	}

	//sostituisce la stringa tosub nella stringa target
	void Html_Reader::replaceAll(string& str, const string& from, const string& to) {
		if (from.empty())
			return;
		size_t start_pos = 0;
		while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
			str.replace(start_pos, from.length(), to);
			start_pos += to.length();
		}
	}

	//restituisce il numeri di righe e le righe
	int Html_Reader::getRows(string& target, vector<string>& WTP)
	{

		replaceAll(target, "</tr>", "</tr|");

		vector<string> split;
		SplitString(target, split, true);
		string temp{};

		int rows = split.size();
		WTP = split;

		cout << "**DEBUG** Rows: " << split.size() << endl;
		/*for (auto s : WTP)
		{
		cout << "-" << s << "-  "<<endl;
		}
		cout << endl << endl;
		*/
		return rows;
	}

	//versione piu avanzata della getdata gia presente
	void Html_Reader::GetDataAdvanced(vector<string>& WTP, const string& data, int lylung, const string& separator)
	{
		int lung;
		//cout << "**Riga**: " << data<<endl;
		vector<string> temp;
		string row = Html_Reader::targetString("tr", data, lung, false);
		replaceAll(row, "</td>", "</td|");
		vector<string> split;
		SplitString(row, split, true);
		cout << "**DATA** Elements: " << split.size() << endl;
		for (auto e : split)
		{
			string t;

			if (separator != "null")
			{
				t = GetCleanData(e, separator);
			}
			else
			{
				t = Html::Html_Reader::targetString("td", e, lung, true);
			}

			//cout << "puched: " << t << endl;
			if (t == "null")
				cout << "**ERROR** argument line not found. To prevent furute errors this line will not be read!" << endl;
			else
				temp.push_back(t);
		}

		if (temp.size() != lylung)
		{
			cout << "**ERROR** Line size not match with layout, skipping line to prevent errors!" << endl;
			cout << data << endl;
		}
		else
		{
			WTP = temp;
		}


	}

	//legge un segmento di stringa e ene restituisce il contenuto pulito
	string Html_Reader::GetCleanData(const string& data, const string& separator)
	{
		string temp{ "" };
		string line;
		bool write = false;
		int ct{ 0 };


		for (int i = 0; i < data.length(); i++)
		{
			if (data[i] == '<')
			{
				write = false;
			}
			// controlla che se è presente <td></td> aggiunge un dato vuoto
			if (data[i] == '<' && data[i + 1] == 't' && data[i + 2] == 'd' && data[i + 3] == '>' && data[i + 4] == '<' && data[i + 5] == '/' && data[i + 6] == 't' && data[i + 7] == 'd' && data[i + 8] == '>')
			{
				line += "";
			}


			if (write)
			{
				temp += data[i];

				if (data[i + 1] == '<')
				{
					bool space = true;
					/*for (auto el : temp.value)
					{
					if (!isspace(el))
					{
					space = false;
					}


					}*/

					if (temp.find_first_not_of(' ') != string::npos)
					{
						space = false;
					}

					if (!space) // controlla che la stringa non sia solo spazi
					{
						if (ct<1)
							line += temp;
						else
							line += separator + temp;

						//cout<<"**GetData** Got: -"<<temp.value<<" from: "<<data<<endl;
						temp = "";

						ct++;
					}
					else
					{
						temp = "";
					}
				}
			}

			if (data[i] == '>')
			{
				write = true;
			}

		}

		return line;
	}