#pragma once
#include "Costants.h";
#include "Html_Reader.h"
#include "Element.h"

using namespace std;

namespace Html
{
	class Html_Writer
	{
	public:
		static void EvaluateLayout(const string& target, vector<vector<Element>>& LayInfo);

		static void  WriteOutPut(vector<vector<Element>>& LayInfo, vector<vector<string>>& data, vector<string>& Olay);

		static void SaveCleanData(const vector<string>& layout, const vector<vector<string>>& table);

	};
}

