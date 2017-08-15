#include "screen.h"

// 0 represents the top-left screen element
const string::size_type TOP_LEFT = 0;

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
	// do not wrap around
	if ( row() == 1 ) // at top?
		cerr << "Screen::up - Cannot wrap around in a vertical direction" << endl;
	else
		_cursor -= _width;

	return;
}

void Screen::down()
{   // move _cursor down one row of screen
	// do not wrap around
	if ( row() == _height ) // at bottom?
		cerr << "Screen::down - Cannot wrap around in a vertical direction" << endl;
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

void Screen::set( const string& s )
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
			_screen.at(offset + iy) = local[ local_pos++ ];
	}

	_height = h;
	_width = w;
	// _cursor remains unchanged

	return;
}

void Screen::display() const
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

string::size_type Screen::remainingSpace() const
{   // includes current position
	auto size = _width * _height;
	return(size - _cursor);
}

string::size_type Screen::row() const
{   // return current row
	return (_cursor + _width)/_width;
}

