#include "Html_Writer.h"

using namespace Html;
using namespace std;

//genera file contente tutti i dati recuperati
void Html_Writer::SaveCleanData(const vector<string>& layout, const vector<vector<string>>& table)
{
	ofstream CleanFile;
	CleanFile.open("CleanData.txt");
	CleanFile << "//Output File of Html Table builder\n";
	CleanFile << "//\n";
	CleanFile << "//Warning: always check your data before using it!!!\n";
	CleanFile << "//\n";
	CleanFile << "Table layout:\n";
	string ly;
	for (auto e : layout)
	{
		ly += e + "  |  ";
	}
	CleanFile << ly << endl;

	ly = "";
	CleanFile << "Table data:\n";
	for (auto line : table)
	{
		for (auto item : line)
		{
			ly += item + "  |  ";
		}
		CleanFile << ly << endl;
		ly = "";
	}

	CleanFile.close();

	cout << "**LOG** Clean data was wrote into CleanData.txt" << endl;
}

//valuta il nuovo layout inserito ## h - tag html / l - layout / n - layout nuovo / o - layout vecchio / t - testo ##
void Html_Writer::EvaluateLayout(const string& target, vector<vector<Element>>& LayInfo)
{
	vector<string> nwLay;
	Html_Reader::SplitString(target, nwLay, true);
	bool text = false;
	Element temp{ "", 'o' };
	vector<Element> line;

	for (auto item : nwLay)
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


	cout << "**DEBUG** New Layout Info" << endl;
	for (auto line : LayInfo)
	{
		for (auto item : line)
		{
			cout << "-" << item.value << "  Type: " << item.type << "-   ";
		}
		cout << endl << endl;
	}

}

//scrive il file output.html
void  Html_Writer::WriteOutPut(vector<vector<Element>>& LayInfo, vector<vector<string>>& data, vector<string>& Olay)
{
	cout << "**LOG** Table result is going to written in output.html" << endl;
	ofstream Output;
	Output.open("Output.html");
	Output << "<html><head><title>Html Builed Table</title></head><body>" << endl << endl;
	Output << "<h3 align=center>Output File of Html Table Builder</h3>";
	Output << "<h4 align=center style=\"color:red;\"><strong>WARNING: always check your data before using it, look at CleanData.txt for all data used to build this table!!!</strong></h4><br>";
	Output << "<br><br>";
	Output << "<table>" << endl;
	string templ{ "" };

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
									//cout << "POS:" << pos << endl;
								}


							}
						}
						else
						{
							pos = -2;
							//cout << "Empty column" << endl;
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

	Output << "</table>" << endl;
	Output << endl << endl << "</body></html>";
	Output.close();
	cout << "**LOG** Table result has been written in output.html" << endl;
}
