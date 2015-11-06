#include "Line.h"

Line::Line()
{
}


Line::~Line()
{
}

Line::Line(std::string line, int lineNumber)
{
	DecodeLine(line);
	LineNumber = lineNumber;
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
	msg.Log("Line: " + std::to_string(LineNumber) + " Delta chars: " + std::to_string(end - begin) + " Line Content: " + line);
	return line;
}

bool Line::CheckIfLayout(const std::string& line)
{
	if (line.find("<th") != std::string::npos)
		return true;
	else
		return false;
}
