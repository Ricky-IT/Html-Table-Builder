#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

#if _WIN32
#include <Windows.h>
#else
#include <stdio.h>
#define RED  "\x1b[31m"
#define GREEN  "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE  "\x1b[34m"
#define DEFAULT  "\x1b[0m"
#endif

class ConsoleMessage
{
public:
	ConsoleMessage();
	~ConsoleMessage();
    
	//Print welcome message
	void WelcomeMessage();

	//print red error message with ERROR: prefix. This also writes the message to a log file. Auto-add \n
	void LogError(std::string);

	//print yellow error message with WARNING: prefix. This also writes the message to a log file. Auto-add \n
	void LogWarning(std::string);

	//print default error message with LOG: prefix. This also writes the message to a log file. Auto-add \n
    void Log(std::string);

	//green message
	void Message(std::string);

private:

	std::string LogFileName = "Log.txt";

	void WriteOnLogFile(std::string);

	//Available colors
	enum Color {red, yellow, green, blue};
	//Print colored message
	void ColoredMessage(std::string, Color);

	//Setup log file
	void LogFileSpace();
};

