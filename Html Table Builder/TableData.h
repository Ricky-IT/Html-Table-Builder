#pragma once
#include <string>
#include <iostream>
#include <fstream>

#include "ConsoleMessage.h"

class TableData
{
public:
	TableData();
	~TableData();

	std::string PlainData;

	//read plaindata from input file
	bool ReadDataFromFile(std::string);

protected:
	ConsoleMessage msg;
};

