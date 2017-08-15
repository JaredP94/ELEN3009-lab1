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

	return 0;
}

