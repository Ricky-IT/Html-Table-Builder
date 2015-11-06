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

	msg.Message("File read sucessfully!\nLines read: " + linesRead);
	return true;
}