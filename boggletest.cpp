/* Brandon Craig | bracraig "at" pdx "dot" edu 
 * CS441 | Fall 2017 | Portland State University */

#include "bogglebuster.h"


int main(int argc, char ** argv)
{

	cout << argc << " total arguments found." << endl;
	if(argc != 4)
	{
		cout << "Incorrect number of arguments. Exiting." << endl;
		return 0;
	}
	
	cout << "Executable name:" << argv[0] <<endl;
	
	cout << "Grid Dimension Arguments: " << argv[1] << ' ' << argv[2] << endl;

	cout << "letters for each tile: " << argv[3] << endl;

	unsigned int rows = (unsigned int) atoi(argv[1]);
	unsigned int columns = (unsigned int) atoi(argv[2]);

	if(rows * columns != strlen(argv[3]))
	{
		cout << "Incorrect number of arguments to fill grid. Exiting." << endl;
		return 0;
	}

	bogglebuster bb(argv[3], rows, columns);
	
	bb.display_characters();
	bb.solve();

	return 0;
}
