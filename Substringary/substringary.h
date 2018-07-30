/* Brandon Craig */

#pragma once
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <cstring>
#include <list>

using namespace std;

class Substringary
{
	public:
		//Substringary(string="../../../../usr/share/dict/words");
		Substringary(string="words_alpha.txt");
		~Substringary();

		void insert_substring(string);
		void insert_word(string);
		void display_all_substrings(void);
	
		bool find_substring(string);
		bool find_word(string);
		void display_all_words(void);

		void insert_found_word(string);
		void list_found_words();
		void sort_found_words();
		static bool compare_length(const string & first, const string & second);

	private:
		map<string, int> substrings;
		map<string, int> words;
		list<string> found_words;
};



