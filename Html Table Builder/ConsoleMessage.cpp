#include "ConsoleMessage.h"

ConsoleMessage::ConsoleMessage()
{
}


ConsoleMessage::~ConsoleMessage()
{
}

void ConsoleMessage::WelcomeMessage()
{
	ColoredMessage("************************************\n",Color::blue);
	ColoredMessage("*        Html Table Builder\n", Color::green);
	ColoredMessage("*           ver. 1.0.2\n", Color::green);
	ColoredMessage("*           by Rickyit\n", Color::yellow);
	ColoredMessage("*       twitter.com/_RickyIT\n", Color::yellow);
	ColoredMessage("************************************\n\n", Color::blue);
	LogFileSpace();
}

void ConsoleMessage::Message(std::string message)
{
	ColoredMessage(message + "\n", Color::green);
	WriteOnLogFile("DONE: "+message + "\n");
}

void ConsoleMessage::Log(std::string message)
{
	std::string output = "LOG: " + message + "\n";
	std::cout << output;
	WriteOnLogFile(output);
}

void ConsoleMessage::LogWarning(std::string message)
{
	std::string output = "WARNING: " + message + "\n";
	ColoredMessage(output, Color::yellow);
	WriteOnLogFile(output);
}

void ConsoleMessage::LogError(std::string message)
{
	std::string output = "ERROR: " + message + "\n";
	ColoredMessage(output, Color::red);
	WriteOnLogFile(output);
}

void ConsoleMessage::WriteOnLogFile(std::string message)
{
	try
	{
		std::ofstream logstream(LogFileName, std::fstream::in | std::fstream::out | std::fstream::app);
		logstream << message;
		logstream.close();
	}
	catch (std::exception e)
	{
		ColoredMessage("ERROR: can't open/create log file!\n",Color::red);
	}
}

void ConsoleMessage::LogFileSpace()
{
	try
	{
		std::ofstream logstream(LogFileName, std::fstream::in | std::fstream::out | std::fstream::app);
		logstream << std::endl << std::endl;
		logstream.close();
	}
	catch (std::exception e)
	{
		ColoredMessage("ERROR: can't open/create log file!\n", Color::red);
	}
}

void ConsoleMessage::ColoredMessage(std::string Message, Color color)
{
	#if _WIN32
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	//set color based on requested
	switch (color)
	{
	case ConsoleMessage::red:
		SetConsoleTextAttribute(h, 4);
		break;
	case ConsoleMessage::yellow:
		SetConsoleTextAttribute(h, 14);
		break;
	case ConsoleMessage::green:
		SetConsoleTextAttribute(h, 10);
		break;
	case ConsoleMessage::blue:
		SetConsoleTextAttribute(h, 9);
		break;
	}
	std::cout << Message;
	//reset default message color
	SetConsoleTextAttribute(h, 7);
	#else
	switch (color)
	{
	case ConsoleMessage::red:
		printf(RED  "%s"  DEFAULT, Message.c_str());
		break;
	case ConsoleMessage::yellow:
		printf(YELLOW  "%s"  DEFAULT, Message.c_str());
		break;
	case ConsoleMessage::green:
		printf(GREEN  "%s"  DEFAULT, Message.c_str());
		break;
	case ConsoleMessage::blue:
		printf(BLUE  "%s"  DEFAULT, Message.c_str());
		break;
	}
	#endif	
}
