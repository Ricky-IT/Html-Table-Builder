#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "ConsoleMessage.h"
#include "Helper.h"
#include "Line.h"


class TableData
{
public:
	TableData();
	~TableData();

	std::string PlainData;
	std::vector<Line> Table;

	//read plaindata from input file
	bool ReadDataFromFile(std::string InputFileName);
	//begin analyzing the content of plain data
	void Analyze();

protected:
	ConsoleMessage msg;
	//search open tag of the html table
	void SearchTableInPlainData(int& beginpos, int& endpos);
	//select the table chars and remove the open and close tag
	std::string SelectTable(int& beginpos, int& endpos, std::string& table);

	std::vector<std::string> OldLayout;


};

