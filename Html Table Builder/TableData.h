#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "ConsoleMessage.h"
#include "Helper.h"


class TableData
{
public:
	TableData();
	~TableData();

	std::string PlainData;

	//read plaindata from input file
	bool ReadDataFromFile(std::string);
	//begin analyzing the content of plain data
	void Analyze();

protected:
	ConsoleMessage msg;
	//search open tag of the html table
	void SearchTableInPlainData(int&, int&);
	//select the table chars and remove the open and close tag
	std::string SelectTable(int&, int&, std::string& table);

	std::vector<std::string> OldLayout;


};

