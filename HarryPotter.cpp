#include <iostream>
#include <vector>
#include <algorithm> // эта библиотека нужна для функции transform
#include <fstream>

using namespace std;

vector<vector<string>> SentencesParser(string text)
{
	vector<vector<string>> result;



	return result;
}

bool IsLetter(string l)
{
	if ((l >= "A" && l <= "Z") || (l >= "a" && l <= "z")
		|| (l >= "А" && l <= "Я")
		|| (l >= "а" && l <= "я")
		|| (l == "ё")
		|| (l == "Ё")
		|| (l == "\'"))
		return true;
	return false;
}


int main()
{
	string source;
	transform(source.begin(), source.end(), source.begin(), tolower);	// перевод строки в нижний регистр
}
