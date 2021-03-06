#ifndef SCREEN_H
#define SCREEN_H

#include <string>
#include <iostream>
using namespace std;

enum class Direction{HOME, FORWARD, BACK, UP, DOWN, END};

// The unsigned integral type which is used to store the number of
// characters in a string is nested within the string class, so it
// is accessed using "string::size_type".
// The range of string::size_type is guaranteed to be large enough to store the maximum
// *size* of any string that can be held by the string class as well as any index into
// the string.

class Screen {
public:
	// Screen's constructor
	Screen( string::size_type height = 8, string::size_type width = 40, char bkground = '#');

	// get the Screen's height
	string::size_type height() const { return _height; }
	// get the Screen's width
	string::size_type width() const { return _width; }

	// place the cursor at the top-left corner of the screen
	void home() { _cursor = 0;  return; }
	// place the cursor at the bottom-right corner of the screen
	void end() { _cursor = _width * _height - 1; return; }
	// move the cursor one position to the right
	void forward();
	// move the cursor one position to the left
	void back();
	// move the cursor up one row
	void up();
	// move the cursor down one row
	void down();
	// move the cursor to the specified row and column
	void move(string::size_type row, string::size_type col);
	// move the cursor in a specified direction
	void move(Direction dir); // not a necessity for clients of Screen to still correctly operate since it overloads the original move() function - does offer more intuitive control to the user

	// get the character at the cursor's current position
	char get() const { return _screen[_cursor]; }
	// get the character at the specified row and column
	char get(string::size_type row, string::size_type col);

	// write a character on the screen at the current cursor position
	void set( char ch );
	// write a string of characters on the screen starting at the current cursor position
	void set( const string& s );
	// overwrite the entire screen with the specified character
	void clear( char bkground = '#');

	// resize the screen
	void reSize( string::size_type height, string::size_type width, char bkground = '#');
	// display the screen
	void display() const;
	// check whether the specified co-ordinates lie within the screen
	bool checkRange(string::size_type row, string::size_type col) const;
	// draw empty square with border outline
	void square(int x_pos, int y_pos, int length);

private:
	// private member functions
	string::size_type remainingSpace() const;
	string::size_type row() const;

	// private data members
	// (preceding each name with an underscore is a naming convention - not a requirement)

	// number of Screen rows
	string::size_type _height;
	// number of Screen columns
	string::size_type _width;
	// position of the Screen's cursor
	string::size_type _cursor;
	// the Screen's data is stored as a string
	string _screen;
};


#endif

//Exercise 4.5:
//The square member forms part of the Screen class, which requires access to the private members in order to perform correct implementation - i.e error checking is impossible without access to the private variables width and height and thus the square would most likely not even appear as a square.
//This function should not form part of the Screen class responsibility as the class is meant to act as a rendering class (presentation layer)

//Exercise 4.6:
//A more intuitive solution may be the implementation of a 2D array - it's much simpler to understand the code structure in this way and allows for new editors to easily modify code thanks to it's general applicability across programming languages. Position system then becomes more intuitive.
//A classes interface should not be changed as an existing codebase may no longer function as it did before. The interface and base functionality should remain to ensure compatibility, whilst changing the implementation may allow for enhanced functionality, better performance, or a simpler framework to understand.