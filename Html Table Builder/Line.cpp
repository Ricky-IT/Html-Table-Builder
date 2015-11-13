#include "Line.h"

Line::Line()
{
}


Line::~Line()
{
}

Line::Line(std::string line, int lineNumber)
{
	LineNumber = lineNumber+1;
	DecodeLine(line);
}

void Line::DecodeLine(std::string line)
{
	try
	{
		if (line.find("<tr") != std::string::npos) // check if there are html tags that delimit the line
		{
			line = RemoveLineTags(line);
		}

		isLayout = CheckIfLayout(line);
		Cells = GetLineContent(line, ReadMode::Normal); //todo: add suppot for clean reading

	}
	catch(std::exception e)
	{
		msg.LogError(e.what());
	}
}

std::string Line::RemoveLineTags(std::string line)
{
	int begin = line.find(">") + 1; // finds first tag end
	int end = line.find("</tr");
	line = line.substr(begin, end - begin);
	//msg.Log("Line: " + std::to_string(LineNumber) + " Delta chars: " + std::to_string(end - begin) + " \nLine Content: " + line);
	return line;
}

bool Line::CheckIfLayout(const std::string& line)
{
	if (line.find("<th") != std::string::npos)
	{
		msg.Log("Line: " + std::to_string(LineNumber) + " is layout!");
		return true;
	}
	else
		return false;
}

std::vector<std::string> Line::GetLineContent(const std::string& input, ReadMode rm)
{
	std::vector<std::string> Content;

	if (rm == ReadMode::Normal)
	{	
		Content = NormalRead(input);
		//Helper::PrintStringList(Content);
	}


	msg.Log("Line " + std::to_string(LineNumber) + " has " + std::to_string(Content.size()) + " cells");
	return Content;
}

std::vector<std::string> Line::NormalRead(const std::string& input)
{
	std::vector<std::string> Content;

	std::vector<int> Begins;
	std::vector<int> Ends;

	if (isLayout)
	{
		Begins = Helper::FindAllInString("<th", input);
		Ends = Helper::FindAllInString("</th", input);
	}
	else
	{
		Begins = Helper::FindAllInString("<td", input);
		Ends = Helper::FindAllInString("</td", input);
	}

	for (int i = 0; i < Ends.size(); i++)
	{
		std::string temp = input.substr(Begins[i], Ends[i] - Begins[i]); // isolate a cell
		int bPos = temp.find(">");
		temp = temp.substr(bPos+1, temp.length() - bPos); // remove the init tag
		Content.push_back(temp);
	}

	return Content;
}

std::string Line::GetCleanDataString()
{
	std::string res;
	if (isLayout)
		res += "Layout: ";
	for (auto el : Cells)
	{
		res += " | " + el + " | ";
	}
	if (isLayout)
		res += "\n\n";
	return res;
}

