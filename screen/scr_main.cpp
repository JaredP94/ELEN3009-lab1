// Exercising the Screen class
#include "screen.h"
#include <iostream>

using namespace std;

int main()
{
	Screen myScreen{6,6};
	myScreen.clear(' ');
	myScreen.move(1,1);
	myScreen.set("******");
	myScreen.move(1,4);
	myScreen.set('*');
	myScreen.down();
	myScreen.set('*');
	myScreen.down();
	myScreen.set('*');
	myScreen.down();
	myScreen.set('*');
	myScreen.down();
	myScreen.set('*');
	myScreen.move(6,2);
	myScreen.set("***");
	myScreen.display(); // Prints a 'J' on the screen
	
	cout << endl;
	myScreen.reSize(8,8);
	myScreen.clear(' ');
	myScreen.square(3,3,5);
	myScreen.display(); // Displays an empty square
	
	cout << endl;
	myScreen.clear(' ');
	myScreen.square(9,2,5);
	myScreen.display(); // Test for start position error
	
	cout << endl;
	myScreen.clear(' ');
	myScreen.square(4,2,5);
	myScreen.display(); // Test for length error

	return 0;
}

