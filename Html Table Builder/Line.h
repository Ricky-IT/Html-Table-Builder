#pragma once
#include <string>
#include <iostream>
#include <vector>

#include "ConsoleMessage.h"

class Line
{
public:
	Line();
	Line(std::string,int);
	~Line();

	std::vector<std::string> Cells;

	bool isLayout = false;
	int LineNumber = -1;
private:
	ConsoleMessage msg;
	//read line and get its content divided into cells
	void DecodeLine(std::string);

	//remove html line tag <tr> and </tr>
	std::string RemoveLineTags(std::string);

	//check if the line is a layout line or not
	bool CheckIfLayout(const std::string&);

};

