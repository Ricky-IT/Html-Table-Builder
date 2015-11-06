//----------------------------------------------------
// Html Table Builder
// by @_RickyIT
// 
// Read and rewrite Html tables
//---------------------------------------------------

#include <iostream>
#include "ConsoleMessage.h"
#include "TableData.h"

std::string get_trimmed_string(std::string str)
{
	int s = str.find_first_not_of(" \t");
	int e = str.find_last_not_of(" \t");

	// if do find real content
	if (s != -1 && e != -1)
		return str.substr(s, e - s + 1);

	return "";
}

std::string GetInputFileName()
{
	std::string name;
	std::cout << "Where is the html table located? Insert file name. [Default: input.txt]"<<std::endl;
	std::getline(std::cin, name);
	//se la stringa non e' bianca
	if (get_trimmed_string(name).length() > 0)
	{
		return get_trimmed_string(name);
	}
	else
	{
		return "input.txt";
	}
}

int main()
{
	ConsoleMessage messager;
	messager.WelcomeMessage();
	TableData data;

	if (data.ReadDataFromFile(GetInputFileName()))
	{
	    
	}

	std::cout << "Press a key (a-z, 0-9) and enter to exit";
	char c;
	std::cin >> c;
	return 0;
}