#pragma once

#include "iostream"
#include "string"

class Tag
{
public:

	std::string value;
	char type;

	Tag(std::string val, char ty);

	~Tag();

	void push(char item);

	void cleardata();
};

