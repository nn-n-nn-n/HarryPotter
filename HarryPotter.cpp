#include <iostream>
#include <vector>
#include <algorithm> // эта библиотека нужна для функции transform
#include <fstream>
#include <set>
//#include <string>

using namespace std;

vector<vector<string>> SentencesParser(const string& text)	// основная функция парсинга
{
	vector<vector<string>> result;
	vector<string> words;
	size_t pos = FindPunctionMark(text);
	size_t pos1 = string::npos;
	size_t startPos = 0;
	string sentence;
	while (pos != string::npos)
	{
		sentence = text.substr(startPos, pos - pos1);
		if (IsLetter(sentence))
		{
			words = DivisionWords(sentence);
			result.push_back(words);
		}
		startPos = pos;
		pos = FindPunctionMark(text);
		if (pos != string::npos)
			sentence.erase(pos, 1);
	}

	return result;
}


bool IsLetter(const string& l)	// функция проверки является ли символ буквой
								// для латинских букв можно использовать isalpha()
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

size_t FindPunctionMark(const string& text, size_t startPos = 0)	// функция поиска конца предложения
{
	set<char> delimiters{'.','!','?',';',':','(',')'};
	for (size_t i = startPos; i < text.length(); i++)
	{
		if (delimiters.count(text[i]) > 0)
			return i;
	}
	return string::npos;
}

vector<string> DivisionWords(const string& sentence)	// функция разделения предложений на слова
{
	vector<string> res;
	string word;
	size_t pos = 0;
	size_t pos1 = string::npos;
	size_t startPos = 0;
	if (!sentence.empty())
	{
		pos = sentence.find(' ', pos);
		if (pos != string::npos)
		{
			word = sentence.substr(startPos, pos - pos1);	// получаем первое число
			res.push_back(word);
		}
		while (pos != string::npos)		// цикл для получения остальных чисел в векторе
		{
			pos = sentence.find(' ', pos);
			if (pos != string::npos)
			{
				word = sentence.substr(pos + 1, pos - pos1);
				res.push_back(word);
				pos1 = pos;
				pos++;
			}
			else
				break;	// выход из цикла, когда вектор достиг конца
		}
	}
	return res;
}

int main()
{
	ifstream txt{ "HarryPotterText.txt" };
	string source;
	while (txt)
	{
		txt >> source;
	}
	transform(source.begin(), source.end(), source.begin(), tolower);	// перевод строки в нижний регистр
	SentencesParser(source);
}
