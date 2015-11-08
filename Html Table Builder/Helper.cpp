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

	if (references.size() == 0)
	{
		std::string error = "No reference found for: " + StringToFind ;
		throw std::exception(error.c_str());
	}

	return references;
}

std::string Helper::ReplaceString(std::string text, const std::string& from, const std::string& to)
{
	size_t start_pos = text.find(from);
	if (start_pos == std::string::npos)
		return false;
	text.replace(start_pos, from.length(), to);
	return text;
}

std::string Helper::ReplaceAllString(std::string text, const std::string& from, const std::string& to)
{
	size_t start_pos = 0;
	while ((start_pos = text.find(from, start_pos)) != std::string::npos) {
		text.replace(start_pos, from.length(), to);
		start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
	}
	return text;
}


std::vector<std::string> Helper::SplitText(std::string text, const std::string& separator)
{
	std::vector<std::string> SplitText;
	std::vector<int> separatorsPos = FindAllInString(separator, text);
	int startpos = 0;
	for (int i = 0; i < separatorsPos.size() - 1; i++)
	{
		SplitText.push_back(text.substr(startpos, separatorsPos[i] - startpos));
		startpos = separatorsPos[i] + separator.length();
	}

	return SplitText;

}

void Helper::PrintStringList(const std::vector<std::string> list)
{
	std::cout << std::endl;
	for (auto s : list)
	{
		std::cout << " -" << s << "- ";
	}
	std::cout << std::endl;
}
