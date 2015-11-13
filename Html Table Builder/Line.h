#pragma once
#include <string>
#include <iostream>
#include <vector>

#include "ConsoleMessage.h"
#include "Helper.h"

class Line
{
public:
	Line();
	Line(std::string line ,int lineNumber);
	~Line();

	std::vector<std::string> Cells;

	bool isLayout = false;
	int LineNumber = -1;

	enum  ReadMode {Normal, Clean};
	//get all data in the line
	std::string GetCleanDataString();
private:
	ConsoleMessage msg;
	//read line and get its content divided into cells
	void DecodeLine(std::string line);

	//remove html line tag <tr> and </tr>
	std::string RemoveLineTags(std::string line);

	//check if the line is a layout line or not
	bool CheckIfLayout(const std::string& line);

	//read line and recover cells content
	std::vector<std::string> GetLineContent(const std::string& line, ReadMode rm);

	//get cells content keeping html tags inside
	std::vector<std::string> NormalRead(const std::string& line);



};

