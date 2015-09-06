//***********************************************************************************************************************
//
//  Html Table Builder
//  Developed by _Ricky
//
//  Desc: Read html code from input.txt (next to exe file) analize it and create a new html table
//
//  **WARNING**
//  Sub tables are not supported!
//
//***********************************************************************************************************************

//#include "ctype.h"
#include "Costants.h";
#include "Element.h"

#include "Html_Reader.h";
#include "Html_Writer.h";

using namespace std;
using namespace Html;

//legge il file input.txt
string ReadFile()
{
	string result;
	string path{ "input.txt" };	

	if (ifstream(path))
	{
		cout << "**** Begin reading INPUT.TXT" << endl;
		ifstream f(path);
		string line{ "" };

		while (getline(f, line))
		{
			result += line;
		}
		cout << "**LOG** INPUT.TXT sucessfully read" << endl;
	}
	else
	{
		cout << "**ERROR** File input.txt doesn't exist! Create it and fill it with html code to use!" << endl;
		result = "null";
	}

	return result;

}

// chiede all'utente da che tag vuole che il programma legga
string AskTarget()
{
	string target;
	do {
		cout << "Insert the target tag (no < >) where the program have to began to read:" << endl;
		cout << "**NOTE** If there is a <tbody> tag, use it istead of <table> (using <table> may cause some data los!)" << endl;
		getline(cin, target);
	} while (target.find("<") != string::npos && target.find(">") != string::npos);

	return target;
}

// chiede all'utente da che tag vuole che il programma legga
string AskNewLayout(vector<string>& layCurrent)
{
	string target;
	do {
		cout << endl << "Current Layout: (- make you understand where a layout name ends or begins)";
		for (auto e : layCurrent)
		{
			cout << "-" << e << "- ";
		}
		cout << endl;

		cout << endl << "Insert a new layout:" << endl;
		cout << "**NOTE** Layout MUST be: <new layout name>=<old layout name>(+\"Text\"+<another old layout name>+\"More Text\"). Use \'*none\' to create a empty column)| and so on!" << endl;
		cout << "**NOTE** In new layout you MUST NOT use spaces and \'+\'!! (except for old layout names!)" << endl;
		getline(cin, target);
	} while (target.find("|") == string::npos);

	return target;
}


int main()
{


	string FileContent;
	string TBegin{};
	string Content;
	vector<string> layout;
	vector<vector<string>> Table;
	vector<string> rows;

	vector<vector<Element>> LayInfo;


	FileContent = ReadFile();
	//cout<<endl<<"**DEBUG** Content: " << FileContent<<endl<<endl;

	if (FileContent != "null")
	{
		TBegin = AskTarget();
		int l;
		Content = Html_Reader::targetString(TBegin, FileContent, l, false);
		if (Content != "null")
		{
			//cout << endl << "**DEBUG** TargetList: " << Content << endl << endl;
			FileContent = "";
			int endlayout = Html_Reader::GetLayout(layout, Content);
			Content = Content.substr(endlayout);
			cout << endl << endl << "**DEBUG** Data only (deleted: " << endlayout << ")"; // << Content << endl << endl;
		}

		int righe = Html_Reader::getRows(Content, rows);
		cout << "**DEBUG** Rows:" << righe << endl << endl;

		Html_Reader::CollectData(Table, rows, layout.size());

		Html_Writer::SaveCleanData(layout, Table);
		string newLay = AskNewLayout(layout);
		Html_Writer::EvaluateLayout(newLay, LayInfo);

		Html_Writer::WriteOutPut(LayInfo, Table, layout);


	}


	char c;
	cout << "Press a button to exit (letter/number + escape) ";
	cin >> c;

}
