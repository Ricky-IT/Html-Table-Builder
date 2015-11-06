#include "Helper.h"


std::vector<int> Helper::FindAllInString(std::string StringToFind, const std::string& Text)
{   
	std::vector<int> references;

	size_t pos = Text.find(StringToFind, 0);
	while (pos != std::string::npos)
	{
			references.push_back(pos);
			pos = Text.find(StringToFind, pos+ 1);
	}

	return references;
}
