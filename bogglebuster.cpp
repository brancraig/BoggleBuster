/* Brandon Craig | bracraig "at" pdx "dot" edu 
 * CS441 | Fall 2017 | Portland State University */

#include "bogglebuster.h"

bogglebuster::bogglebuster(void) : gridgraph() {}

bogglebuster::bogglebuster(char * characters, const unsigned int & rows, const unsigned int & columns) : gridgraph(rows, columns) 
{
	init(characters);


}

bogglebuster::~bogglebuster(void){}

void bogglebuster::init(char * characters)
{
	vertex ** current = gridArray;
	while(current < END)
	{
		(*current)->set_value(*characters);
		++current;
		++characters;
	}
	return;
}

void bogglebuster::display_characters(void)
{
	vertex ** current = gridArray;
	while(current < END)
	{
		cout << (*current)->get_value() << " ";
		
		if((*current)->get_column_pos() == row_size - 1)
		       cout << endl;	
		
		++current;
	}
	cout << endl;
	return;
}

void bogglebuster::solve(void)
{
	vertex ** current = gridArray;
	string empty_string;
	//int count = 1;
	while(current < END)
	{
		//cout << "vertex " << count << endl;
		solve1(*current, empty_string, dict);
		++current;
		//++count;
	}
		
	//cout << "Sorting words by length." << endl;
	//dict.sort_found_words();

	cout << "Found words." << endl;
	dict.list_found_words();

}

void bogglebuster::solve1(vertex * current_vertex, string test_word, Substringary & dict)
{
	if(current_vertex->get_visited())
	{
		//cout << "visited" << endl;
		return;
	}
	//cout << "not visited" << endl;

	current_vertex->set_visited(true);

	test_word.append(1, current_vertex->get_value());
	//cout << to_test << endl;
	
	if(!dict.find_substring(test_word))
	{
		current_vertex->set_visited(false);
		return;
	}

	if(test_word.length() > 1 && dict.find_word(test_word))
		dict.insert_found_word(test_word);
	
	current_vertex->expand((void (*)(vertex *, string, Substringary &))(&solve1), test_word, dict);

	current_vertex->set_visited(false);
	return;
	
}


