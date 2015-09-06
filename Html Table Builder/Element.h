#pragma once

#include "iostream"
#include "string"

class Element
{
public:

	std::string value;
	char type;

	Element(std::string val, char t);


	void push(char item);

	void cleardata();
};

