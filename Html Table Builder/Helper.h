#pragma once
#include<string>
#include<iostream>
#include<vector>

static class Helper
{
public:
	//Find all references (pos) into another string
	static std::vector<int> FindAllInString(std::string stringtoFind, const std::string& text);

	//replace string into a text
	static std::string ReplaceString(std::string text, const std::string& from, const std::string& to);

	//replace all string into a text
	static std::string ReplaceAllString(std::string text, const std::string& from, const std::string& to);

	//split text
	static std::vector<std::string> SplitText(std::string text, const std::string& separator);

	
	static void PrintStringList(const std::vector<std::string> list);

};

