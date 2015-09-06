#pragma once
#include "Costants.h"

using namespace std;
namespace Html
{

	static class  Html_Reader
	{
	public:
		static string CloseTag(const string& target);

		static string targetString(const string& begin, const string& FC, int& lung, bool advanced);

		static void CollectData(vector<vector<string>>& table, vector<string>& rows, int lylung);

		static void GetData(vector<string>& WTP, const string& data);

		static void replaceAll(string& str, const string& from, const string& to);

		static int getRows(string& target, vector<string>& WTP);

		static int GetLayout(vector<string>& lay, const string& ct);

		static void GetDataAdvanced(vector<string>& WTP, const string& data, int lylung, const string& separator);

		static string GetCleanData(const string& data, const string& separator);

		static void Html_Reader::SplitString(const string& tar, vector<string>& WTP, bool bar_split);

	private:
		static string Datakind();
	};
}

