#include "TableData.h"



TableData::TableData()
{
}


TableData::~TableData()
{
}

bool TableData::ReadDataFromFile(std::string InputFileName)
{
	int linesRead = 0;
	msg.Log("Trying to read file: " + InputFileName);
	try
	{
		std::string line;
		std::ifstream fileToRead(InputFileName);

		if (!fileToRead) throw std::exception();

		while (std::getline(fileToRead,line) )
		{
			PlainData += line;
			linesRead++;
		}
		
	}
	catch (std::exception e)
	{
		msg.LogError("Can't find file: " + InputFileName+"\n");
		return false;
	}

	msg.Message("File read sucessfully!\nLines read: " + std::to_string(linesRead));
	return true;
}

void TableData::Analyze()
{
	msg.Log("Searching for tables...");
	try
	{
		int begin =-1, end=-1;
		SearchTableInPlainData(begin,end);
		PlainData = SelectTable(begin, end, PlainData);


	}
	catch (std::exception e)
	{
		msg.LogError(e.what());
	}
}

void TableData::SearchTableInPlainData(int& beginpos, int& endpos)
{
	std::vector<int> ref;

	ref = Helper::FindAllInString("<table", PlainData);
	if (ref.size() > 1)
	{
		throw std::exception("Sorry this programm can't handle more than one table at a time.\nRemove one and retry!");
	}
	if (ref.size() == 1)
	{
		beginpos = ref[0];
		if (PlainData.find("</table") != std::string::npos)
			endpos = PlainData.find("</table");
		else
			throw std::exception("Unable to find </table>");

		msg.Message("Found <table> tag at char: " + std::to_string(beginpos) + ". Found </table> at char: " + std::to_string(endpos));
		return;
	}

	msg.LogWarning("No <table> tag found, searching for <tbody>");

	ref = Helper::FindAllInString("<tbody", PlainData);
	if (ref.size() > 1)
	{
		throw std::exception("Sorry this programm can't handle more than one table at a time. Remove one and retry!");
	}

	if (ref.size() == 1)
	{
		beginpos = ref[0];
		if (PlainData.find("</tbody") != std::string::npos)
			endpos = PlainData.find("</tbody");
		else
			throw std::exception("Unable to find </tbody>");

		msg.Message("Found <tbody> tag at char: " + std::to_string(beginpos) + ". Found </tbody> at char: " + std::to_string(endpos));
		return;
	}

	msg.LogWarning("No <tbody> tag found");
	throw std::exception("At the moment custom tags are not supported!\n Execution aborted because no <table> or <tbody>  was found");

}

std::string TableData::SelectTable(int& begin, int& end, std::string& table)
{
	std::string temp = table.substr(begin, end - begin);
	//remove initial tag
	int pos = temp.find(">", 0);
	temp = temp.substr(pos + 1, temp.length() - pos - 1);
	

	msg.Log("Selected: " + std::to_string(end - begin -pos) + " characters");
	msg.Log("Selected table: " + temp);
	return temp;
}