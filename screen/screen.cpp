#include "screen.h"

// 0 represents the top-left screen element
const string::size_type TOP_LEFT = 0; // const - Case 1: integer datatype large enough to represent any possible string size which cannot be changed due to const declaration

// Screen's constructor
Screen::Screen(string::size_type height, string::size_type width, char bkground):
	_height{height},// initialises _height with height
	_width{width},  // initialises _width with width
	_cursor{TOP_LEFT},		// initialises _cursor to the starting position
	_screen(height * width, bkground)	// size of _screen is height * width
										// all positions initialized with
										// character value of bkground
{ /* all the work is done with the member initialization list */ }

void Screen::forward()
{   // advance _cursor one screen element
	++_cursor;

	// wrap around if the _cursor is at the end of the screen
	if ( _cursor == _screen.size()) home();

	return;
}

void Screen::back()
{   // move _cursor backward one screen element
	// check for top of screen; wrap around
	if ( _cursor == TOP_LEFT )
		end();
	else
		--_cursor;

	return;
}

void Screen::up()
{   // move _cursor up one row of screen
	// wrap around if the _cursor is at the start of the screen
	// check for top of screen; wrap around
	if ( _cursor == TOP_LEFT ) end();
	else if ( row() == 1) _cursor = _screen.size() - ( _width - _cursor % _width ) - 1;
	else _cursor -= _width;

	return;
}

void Screen::down()
{   // move _cursor down one row of screen
	// wrap around if the _cursor is at the end of the screen
	if ( _cursor == _screen.size() - 1 ) home();
	else if ( row() == _height) _cursor = ( _cursor % _width ) + 1;
	else
		_cursor += _width;

	return;
}

void Screen::move( string::size_type row, string::size_type col )
{   // move _cursor to absolute position
	// valid screen position?
	if ( checkRange( row, col ) )
	{
		// row location
		auto row_loc = (row-1) * _width;
		_cursor = row_loc + col - 1;
	}

	return;
}

void Screen::move(Direction dir)
{
	Direction _home = Direction::HOME;
	Direction _forward = Direction::FORWARD;
	Direction _back = Direction::BACK;
	Direction _up = Direction::UP;
	Direction _down = Direction::DOWN;
	Direction _end = Direction::END;
	
	if (dir == _home) home();
	else if (dir == _forward) forward();
	else if (dir == _back) back();
	else if (dir == _up) up();
	else if (dir == _down) down();
	else if (dir == _end) end();
	else return;
}

char Screen::get( string::size_type row, string::size_type col )
{
	// position _cursor
	move( row, col );
	// the other get() member function
	return get();
}

void Screen::set( char ch )
{
	if ( ch == '\0' )
		cerr << "Screen::set warning: " << "null character (ignored).\n";
	else _screen[_cursor] = ch;

	return;
}

void Screen::set( const string& s ) // const - Case 2: string variable which is passed by reference and is to be kept constant within function scope
{   // write string beginning at current _cursor position
	auto space = remainingSpace();
	auto len = s.size();
	if ( space < len ) {
		cerr << "Screen::set - Truncating, "
			<< "space available: " << space
			<< ", string length: " << len
			<< endl;
		len = space;
	}

	_screen.replace( _cursor, len, s );
	_cursor += len - 1;

	return;
}

void Screen::clear( char bkground )
{   // reset the cursor and clear the screen
	_cursor = TOP_LEFT;
	// assign the string
	_screen.assign(
		// with size() characters
		_screen.size(),
		// of value bkground
		bkground
		);

	return;
}

void Screen::reSize( string::size_type h, string::size_type w, char bkground )
{   // can only *increase* a screen's size to height h and width w
	// remember the content of the screen
	string local{_screen};
	auto local_pos = TOP_LEFT;

	// replaces the string to which _screen refers
	_screen.assign(      // assign the string
		h * w,           // with h * w characters
		bkground         // of value bkground
		);

	// copy content of old screen into the new one
	for ( string::size_type ix = 0; ix < _height; ++ix )
	{ // for each row
		string::size_type offset = w * ix; // row position
		for ( string::size_type iy = 0; iy < _width; ++iy )
			// for each column, assign the old value
			_screen.at(offset + iy) = local[ local_pos++ ]; // .at() method: Returns a reference to the character at specified position on the screen
	}

	_height = h;
	_width = w;
	// _cursor remains unchanged

	return;
}

void Screen::display() const // const - Case 3: const used to create a read-only function which cannot modify the object for which it is called
{
	for ( string::size_type ix = 0; ix < _height; ++ix )
	{ // for each row
		string::size_type offset = _width * ix; // row position
		for ( string::size_type iy = 0; iy < _width; ++iy )
			// for each column, write element
			cout << _screen[ offset + iy ];
		cout << endl;
	}
	return;
}

bool Screen::checkRange( string::size_type row, string::size_type col ) const
{   // validate coordinates
	if (row < 1 || row > _height || col < 1 || col > _width)
	{
		cerr << "Screen coordinates ("<< row << ", " << col << " ) out of bounds.\n";
		return false;
	}
	return true;
}

void Screen::square(int x_pos, int y_pos, int length) // assumes user will enter positive values
{
	// error checking:
	// positioning check
	if (checkRange(x_pos, y_pos) == false) return;
	// horizontal length check
	if ( (unsigned)x_pos + length > _width )
	{
		cout << "Horizontal dimension is too large \n";
		return;
	}
	// vertical length check
	if ( (unsigned)y_pos + length > _height)
	{
		cout << "Vertical dimension is too large \n";
		return;
	}
	// square creation
	move(x_pos,y_pos + 1);
	int x_adjust = 2;
	int j_adjust = 1;
	for (int i = 0; i < length - x_adjust; i++)
	{
		set('*');
		forward();
	}
	for (int j = 0; j < length - j_adjust; j++)
	{
		set('*');
		down();
	}
	for (int k = length; k > 1; k--)
	{
		set('*');
		back();
	}
	for (int m = length; m > 0; m--)
	{
		set('*');
		up();
	}
	return;
 }

string::size_type Screen::remainingSpace() const
{   // includes current position
	auto size = _width * _height;
	return(size - _cursor);
}

string::size_type Screen::row() const
{   // return current row
	return (_cursor + _width)/_width;
}

