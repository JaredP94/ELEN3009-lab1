// complex.cpp
// Multiplying complex numbers

#include <iostream>
#include <complex> // required for the complex class
#include <cmath> // required for square root
#include <string> // required for use of string variables

using complexVal = std::complex<float>;

void menu();
void quadratic(complexVal a, complexVal b, complexVal c);

int main()
{
    int a, b, c;
	
	while (true)
	{
		menu();
		std::cout << "Enter coefficients of quadratic equation: " << std::endl;
		std::cout << "a: ";
		std::cin >> a;
		std::cout << "b: ";
		std::cin >> b;
		std::cout << "c: ";
		std::cin >> c;
		std::cout << std::endl;

		quadratic(a, b, c);
	}

    return 0;
}

void menu() //Function definition to give user program options
{
	std::string choice;
	
	std::cout << "Please select your desired option: \n" << "go: Run Program \n" << "q: Quit Program \n" << std::endl;
	std::cin >> choice;
	std::cout << std::endl;
	
	if (choice == "q") exit(0);
}

void quadratic(complexVal a, complexVal b, complexVal c) //Function definition to implement quadratic formula
{
	auto x1 = (-b + sqrt(pow(b,2) - 4.0f*a*c)) / (a*2.0f);
	auto x2 = (-b - sqrt(pow(b,2) - 4.0f*a*c)) / (a*2.0f);
	
	std::cout << "First root: " << x1.real() << " + " << x1.imag() << "j" << std::endl;
	std::cout << "Second root: " << x2.real() << " + " << x2.imag() << "j" << std::endl << std::endl;
}

//Exercise 3.1: Attempting to increment (int operation) a float which has both real and imaginary component. Will most likely increment real component only