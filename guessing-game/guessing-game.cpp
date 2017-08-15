#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

void check(int actual, int guess);
void print(std::string result);


int main()
{
	srand(time(0));
	int _userGuess = 0, _iteration = 0, _numTries = 5, _randomValue = std::rand() % 101;;

	print("Enter a number between 1 and 100");

	while ((_iteration < _numTries) && (_userGuess != _randomValue))
	{
		std::cin >> _userGuess;
		check(_randomValue, _userGuess);
		_iteration++;
	}
	
	print("You Lose");

	return 0;
}

void check(int actual, int guess)
{
	if (guess < actual)
		{
			print("Guess Higher");
		}
		else if (guess > actual)
		{
			print("Guess Lower");
		}
		else
		{
			print("You Win");
			exit(0);
		}
}

void print(std::string str)
{
	std::cout << str << std::endl;
}