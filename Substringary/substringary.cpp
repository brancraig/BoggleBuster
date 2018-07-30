/* Brandon Craig */


#include "substringary.h"

/*
int main()
{
	
	Substringary test;
	return 0;

}
*/

Substringary::Substringary(string file_name)
{
	char input[50];
	
	ifstream file_in;
	file_in.open(file_name);

	if(file_in.is_open())
	{
		while(file_in && !file_in.eof())
		{
			file_in.get(input, 50, '\n');
			file_in.ignore(50, '\n');
			string word(input);			
			insert_substring(word);
			insert_word(word);
		}
	}
	else
	{
		cout << "File not opened" << endl;
	}

	cout << "Dictionary contains " << substrings.size() << " substrings." << endl;
	cout << "Dictionary contains " << words.size() << " words." << endl;
}


Substringary::~Substringary(){}

void Substringary::insert_substring(string to_add)
{
	int length = to_add.length();
	for(int end = 1; end <= length; ++end)
	{
		//cout << to_add.substr(0,end) << endl;
		string substring(to_add.substr(0,end));
		substrings.insert(pair<string, int>(substring, substring.length()));
	}

	return;
}


void Substringary::insert_word(string to_add)
{
	words.insert(pair<string,int>(to_add, to_add.length()));
	return;
}


void Substringary::display_all_substrings(void)
{
	map<string, int>::iterator it = substrings.begin();
	map<string, int>::iterator end = substrings.end();
	int count = 0;
	while(it != end)
	{
		cout << it->first << endl;
		++it;
	}
	cout << count << " substrings displayed." << endl;
}



bool Substringary::find_substring(string to_find)
{
	return substrings.find(to_find) != substrings.end();
}


bool Substringary::find_word(string to_find)
{
	return words.find(to_find) != words.end();
}

void Substringary::display_all_words(void)
{
	map<string, int>::iterator it = words.begin();
	map<string, int>::iterator end = words.end();
	while(it != end)
	{
		cout << it->first << endl;
		++it;
	}
}


void Substringary::insert_found_word(string to_add)
{

	found_words.push_front(to_add);
	return;
}


void Substringary::list_found_words()
{
	list<string>::iterator it = found_words.begin();
	list<string>::iterator end = found_words.end();
	while(it != end)
	{
		cout << *it << endl;
		++it;
	}
	return;
}

void Substringary::sort_found_words()
{
	found_words.sort(compare_length);
	return;
}


bool Substringary::compare_length(const string & first, const string & second)
{
	return first.length() > second.length();	
}
