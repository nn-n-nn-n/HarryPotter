#include <iostream>
#include <vector>
#include <algorithm> // эта библиотека нужна для функции transform
#include <fstream>
#include <set>

using namespace std;


bool IsLetter(const string& l)	// функция проверки является ли символ буквой
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
	size_t pos = sentence.find(' ');
	size_t startPos = 0;
	if (!sentence.empty())
	{
		while (pos != string::npos)
		{
			word = sentence.substr(startPos, pos - startPos);
			if (word.length() > 0)
				res.push_back(word);
			startPos = pos + 1;
			pos = sentence.find(' ', pos + 1);
		}
		word = sentence.substr(startPos, sentence.length() - startPos);
		if (word.length() > 0)
			res.push_back(word);
	}
	return res;
}

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

void Print(const vector<vector<string>>& vvs)	// функция печати предложений в консоль
{
	for (int i = 0; i < vvs.size(); i++)	// auto i : vvs			 VS пишет, что не может прочитать i
	{
		cout << i << " предложение:" << endl;		// вот здесь		(VS пишет, что не может прочитать i)
		for (int j = 0; j < vvs[i].size(); j++)		// auto j : i
			cout << vvs[i][j] << endl;
	}
}

int main()
{
	ifstream txt{ "HarryPotterText.txt" };
	string source, str;
	while (txt >> str)
		source += str + ' ';
	txt.close();
	transform(source.begin(), source.end(), source.begin(), tolower);	// перевод строки в нижний регистр
	Print(SentencesParser(source));
}
