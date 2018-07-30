/* Brandon Craig | bracraig "at" pdx "dot" edu 
 * CS441 | Fall 2017 | Portland State University */


#include "gridgraph.h"

/* FUNCTION: Default constructor for the graph when no arguments are given.
 * ARGUMENTS: Uses global constants as test_stringeters (Set in 'gridgraph.h') 
 * RETURN: Returns no values.
 */
gridgraph::gridgraph(int rows_in_grid, int columns_in_grid)
{
    row_size = columns_in_grid;
    column_size = rows_in_grid;
    graph_init();
}


/* FUNCTION: Constructor for the graph when the size of the grid (rows by columns) is given.
 * ARGUMENTS: the number of rows and the number of columns. 
 * RETURN: Returns no values.
 */
gridgraph::gridgraph(const unsigned int & rows_in_grid, const unsigned int & columns_in_grid)
{
    row_size = columns_in_grid;
    column_size = rows_in_grid;
    graph_init();
}


/* FUNCTION: Constructor for abstract base vertex.
 * ARGUMENTS: the position of the vertex along the array of vertices, and its position (x, y) in the grid.
 * RETURN: Returns no values.
 */
vertex::vertex(const unsigned int & pos, const unsigned int & x, const unsigned int & y)
{
    position = pos;
    row_pos = x;
    column_pos = y;
    visited = false;
    character = '\0';
}


/* FUNCTION: Constructor for a corner vertex.
 * ARGUMENTS: the position of the vertex along the array of vertices, and its position (x, y) in the grid.
 * RETURN: Returns no values.
 */
corner::corner(const unsigned int & pos, const unsigned int & x, const unsigned int & y) : vertex(pos,x,y)
{}


/* FUNCTION: Constructor for a side vertex.
 * ARGUMENTS: the position of the vertex along the array of vertices, and its position (x, y) in the grid.
 * RETURN: Returns no values.
 */
side::side(const unsigned int & pos, const unsigned int & x, const unsigned int & y) : vertex(pos,x,y)
{}


/* FUNCTION: Constructor for a center vertex.
 * ARGUMENTS: the position of the vertex along the array of vertices, and its position (x, y) in the grid.
 * RETURN: Returns no values.
 */
center::center(const unsigned int & pos, const unsigned int & x, const unsigned int & y) : vertex(pos,x,y)
{}



void gridgraph::graph_init()
{
    array_length = row_size * column_size;
    gridArray = new vertex*[array_length];
    END = (gridArray + array_length);

    vertex ** current = gridArray;
    unsigned int count = 0;
    //cout << "row size: " << row_size << " column size: " << column_size << endl;
    for(unsigned int row = 0; row < column_size; ++row)
        for(unsigned int column = 0; column < row_size; ++column, ++count, ++current){
	    //cout << '(' << row << ", " << column  << ")\n";
            *current = map_to_grid(count, row, column);
	}

    current = gridArray;
    while(current < END)
    {
        (**current).init(row_size, column_size, gridArray);
        ++current;
    }
}

vertex * gridgraph::map_to_grid(const unsigned int & position, const unsigned int & row_position, const unsigned int & column_position)
{
    unsigned int adjacencies = 4;
    
    //cout << position << " " << row_position << " " << row_size << " " << column_position << " " << column_size << endl;
    
    if(row_position == 0 || row_position == column_size - 1)
        --adjacencies;

    if(column_position == 0 || column_position == row_size - 1)
        --adjacencies;

    if(adjacencies == 3)
        return new side(position, row_position, column_position);

    if(adjacencies == 4)
        return new center(position, row_position, column_position);

    if(adjacencies == 2)
        return new corner(position, row_position, column_position);


    return NULL;
}


/*
int vertex::map_to_array(const unsigned int & x, const unsigned int & y, const unsigned int & row_size)
{
    return y + (row_size * x);
}
*/

void corner::init(const unsigned int & row_size, const unsigned int & y_size, vertex ** grid) 
{
	   	
   if(row_pos == 0){ //top
        if(column_pos == 0)         //left
        {
            vertical_adj = *(grid + position + row_size);
            horizontal_adj = *(grid + position + 1);
	    diagonal_adj = *(grid + position + row_size + 1);
        } else {               //right
            vertical_adj = *(grid + position + row_size);
            horizontal_adj = *(grid + position - 1);
	    diagonal_adj = *(grid + position + row_size - 1);
        }
   }else{       //bottom
       if(column_pos == 0)           //left
       {                   
           vertical_adj = *(grid + position - row_size);
           horizontal_adj = *(grid + position + 1);
	   diagonal_adj = *(grid + position - row_size + 1);
       }else{                 //right
           vertical_adj = *(grid + position - row_size);
           horizontal_adj = *(grid + position - 1);
	   diagonal_adj = *(grid + position - row_size - 1);
       }
   }
}


void side::init(const unsigned int & row_size, const unsigned int & y_size, vertex ** grid) 
{

    if(row_pos == 0) //top side
    {
        pi_radian1st = *(grid + position + 1); //top next right
        pi_radian2nd = *(grid + position - 1); //top next left
	pi_radian3rd = *(grid + position + row_size - 1); //diagonal down-left
        pi_radian4th = *(grid + position + row_size); //below this side
	pi_radian5th = *(grid + position + row_size + 1); //diagonal down-right
    }
    else if(column_pos == 0) //left side
    {
        pi_radian1st = *(grid + position + 1); //side next right
	pi_radian2nd = *(grid + position - row_size + 1); //diagonal up-right
        pi_radian3rd = *(grid + position - row_size); //above this side
        pi_radian4th = *(grid + position + row_size); //below this side
	pi_radian5th = *(grid + position + row_size + 1); //diagonal down-right

    }
    else if(row_pos == y_size - 1) // bottom side
    {
        pi_radian1st = *(grid + position + 1); //bottom next right
	pi_radian2nd = *(grid + position - row_size + 1); //diagonal up-right
        pi_radian3rd = *(grid + position - row_size); //above this side
	pi_radian4th = *(grid + position - row_size - 1); //diagonal up-left
        pi_radian5th = *(grid + position - 1); //bottom next left
    }
    else if(column_pos == row_size - 1) // right side; 
    {
        pi_radian1st = *(grid + position - row_size); //above this side
	pi_radian2nd = *(grid + position - row_size - 1); //diagonal up-left
        pi_radian3rd = *(grid + position - 1); //left of this side
	pi_radian4th = *(grid + position + row_size - 1); //diagonal down-left
        pi_radian5th = *(grid + position + row_size); //below this side
    }
    else{}
}

void center::init(const unsigned int & row_size, const unsigned int & y_size, vertex ** grid) 
{
    right =      *(grid + position + 1);
    up_right =   *(grid + position - row_size + 1);
    up =         *(grid + position - row_size);
    up_left =    *(grid + position - row_size - 1);
    left =       *(grid + position - 1);
    down_left =  *(grid + position + row_size - 1);
    down =       *(grid + position + row_size);
    down_right = *(grid + position + row_size + 1);
}


void vertex::set_value(char value)
{
	character = value;
	return;
}

char vertex::get_value(void)
{
	return character;
}


unsigned int vertex::get_row_pos(void) const
{
    return row_pos;
}
        
unsigned int vertex::get_column_pos(void) const
{
    return column_pos;
}



unsigned int vertex::get_position(void) const
{
    return position;
}



gridgraph::~gridgraph()
{
    vertex ** temp = gridArray;
    if(gridArray)
    {
        while(temp < END)
        {
            delete *temp;
            ++temp;
        }
        delete [] gridArray;
        gridArray = NULL;
    }
    row_size = 0;
    column_size = 0;
    array_length = 0;
    return;
}

corner::~corner()
{}

side::~side()
{}

center::~center()
{}

vertex::~vertex()
{}

void gridgraph::display_as_grid(void) const
{
    cout << endl;
    vertex ** temp = gridArray;
    //unsigned int to_display;
    for(unsigned int i = 0; i < column_size; ++i)
    {
        for(unsigned int j = 0; j < row_size; ++j)
        {
	
	    cout << '(' << (*temp)->get_row_pos() << ", " << (*temp)->get_column_pos()	<< ')' << '\t';
            ++temp;
        }
        cout << endl << endl;
    }
    cout << endl;
    return;
}





void gridgraph::display_vertices(void) const
{
    vertex ** start = gridArray;
    while(start < END)
    {
        for(unsigned int i = 0; i < row_size; ++i, ++start){
            (*start)->display();
            cout << endl;
        }
    }
    cout << endl;
}


void corner::display()
{
	cout << position << '\t'
	     << "corner\t" << '(' << row_pos << ", " << column_pos << ')' << " -> " 
	     << "((" << vertical_adj->get_row_pos()   << ", " << vertical_adj->get_column_pos()   << ')'  << ", " 
	     << '('  << horizontal_adj->get_row_pos() << ", " << horizontal_adj->get_column_pos() << ')' << ", "
	     << '('  << diagonal_adj->get_row_pos() << ", " << diagonal_adj->get_column_pos() << "))"
	     << endl;
}

void side::display()
{
	cout << position << '\t'
	     << "side\t" << '(' << row_pos << ", " << column_pos << ')' << " -> " 
	     << "((" << pi_radian1st->get_row_pos() << ", " << pi_radian1st->get_column_pos() << ')'  << ", " 
	     << '('  << pi_radian2nd->get_row_pos() << ", " << pi_radian2nd->get_column_pos() << ')'  << ", "
	     << '('  << pi_radian3rd->get_row_pos() << ", " << pi_radian3rd->get_column_pos() << ')'  << ", " 
	     << '('  << pi_radian4th->get_row_pos() << ", " << pi_radian4th->get_column_pos() << ')'  << ", " 
	     << '('  << pi_radian5th->get_row_pos() << ", " << pi_radian5th->get_column_pos() << "))" << endl;
}

void center::display()
{
    cout << position << '\t'
	 << "center\t" << '(' << row_pos << ", " << column_pos << ')' <<  " -> " 
	 << "((" << right->get_row_pos() << ", " << right->get_column_pos() << ')' << ", "
	 << '('  << up_right->get_row_pos()    << ", " << up_right->get_column_pos()    << ')' << ", "
	 << '('  << up->get_row_pos()    << ", " << up->get_column_pos()    << ')' << ", "
	 << '('  << up_left->get_row_pos()    << ", " << up_left->get_column_pos()    << ')' << ", "
	 << '('  << left->get_row_pos()  << ", " << left->get_column_pos()  << ')' << ", "
	 << '('  << down_left->get_row_pos()  << ", " << down_left->get_column_pos()  << ')' << ", "
	 << '('  << down->get_row_pos()  << ", " << down->get_column_pos()  << ')' << ", "
	 << '('  << down_right->get_row_pos()  << ", " << down_right->get_column_pos()  << "))" << endl;
}


void vertex::set_visited(bool to_set)
{
	visited = to_set;
	return;
}

bool vertex::get_visited(void)
{
	return visited;
}


void vertex::expand(void (*function)(vertex *, PROTOTYPE_ARGUMENTS ), FUNCTION_CALL_ARGUMENTS){}

void corner::expand(void (*function)(vertex *, PROTOTYPE_ARGUMENTS), FUNCTION_CALL_ARGUMENTS)
{

	function(vertical_adj, test_string, dict);
	function(horizontal_adj, test_string, dict);
	function(diagonal_adj, test_string, dict);
	return;
}

void side::expand(void (*function)(vertex *, PROTOTYPE_ARGUMENTS), FUNCTION_CALL_ARGUMENTS)
{
	function(pi_radian1st, test_string, dict);
	function(pi_radian2nd, test_string, dict);
	function(pi_radian3rd, test_string, dict);
	function(pi_radian4th, test_string, dict);
	function(pi_radian5th, test_string, dict);
	return;
}

void center::expand(void (*function)(vertex *, PROTOTYPE_ARGUMENTS), FUNCTION_CALL_ARGUMENTS)
{
	function(right, test_string, dict);
	function(up_right, test_string, dict);
	function(up, test_string, dict);
	function(up_left, test_string, dict);
	function(left, test_string, dict);
	function(down_left, test_string, dict);
	function(down, test_string, dict);
	function(down_right, test_string, dict);
	return;
}
/* FUNCTION:
 * ARGUMENTS:
 * RETURN:
 */

