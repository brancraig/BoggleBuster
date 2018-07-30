/* Brandon Craig | bracraig "at" pdx "dot" edu 
 * CS441 | Fall 2017 | Portland State University */

#pragma once
#include "./2D-Square-Graph-w-Diagonals/gridgraph.h"
#include "./Substringary/substringary.h"


class bogglebuster : public gridgraph
{

	public:
		bogglebuster(void);
		bogglebuster(char * characters, const unsigned int & rows, const unsigned int & columns);
		~bogglebuster(void);
		
		void display_characters(void);

		void solve(void);
		static void solve1(vertex *, string, Substringary & dict);


	private:
		void init(char * characters);
		Substringary dict;

};

