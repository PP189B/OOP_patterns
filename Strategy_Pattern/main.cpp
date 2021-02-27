#include <iostream>
#include "ducks.hpp"

#define STEP_BY_STEP

void print_field(char **field, int size)
{
	for (int i = 0; i <= size + 1; i++)
		std::cout << '-';
	std::cout << std::endl;

	for (int i = 0; i < size; i++)
	{
		std::cout << 9 - i % 10 << '|';
		for (int j = 0; j < size; j++)
			std::cout << field[size - 1 - i][j];
		std::cout << std::endl;
	}

	for (int i = 0; i <= size + 1; i++)
		std::cout << '-';
	std::cout << "\n  ";
	for (int i = 0; i < size; i++)
		std::cout << i % 10;
	std::cout << std::endl;
}

char **create_field(int size)
{
	char **out;

	if (!(out = new char*[size]))
		throw std::bad_alloc();
	for (int i = 0; i < size; i++)
		if (!(out[i] = new char[size]))
			throw std::bad_alloc();
	
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			out[i][j] = ' ';

	return out;
}

void free_field(char **field, int size)
{
	for (int i = 0; i < size; i++)
		delete[] field[i];
	delete[] field;
}

void test(char **field, int size)
{
	/* init ducks */
	std::cout << "\nInit ducks\n=====\n";
	std::cout << "D at {0, 0}\tR at {0, 2}\tG at {0, 6}\trubber at {0, 9}" << std::endl;

	Duck d1(field, size, {0, 0});
	RedDuck d2(field, size, {0, 2});
	GreenDuck d3(field, size, {0, 6});
	RubberDuck d4(field, size, {0, 9});
	
	print_field(field, size);
#ifdef STEP_BY_STEP
	std::cout << "\nPress enter for next test." << std::endl;
	std::cin.get();
#endif


	/* busy pos */
	std::cout << "\nInit duck at busy place\n=====\n";
	std::cout << "new duck at {0, 0}" << std::endl;
	try
	{
		Duck d2(field, size, {0, 0});
	}
	catch (const std::exception &e)
	{
		std::cerr << "R -> {0, 0} : " << e.what() << std::endl;
	}
	print_field(field, size);
#ifdef STEP_BY_STEP
	std::cout << "\nPress enter for next test." << std::endl;
	std::cin.get();
#endif


	/* swim */
	std::cout << "\nSwimming\n=====\n";
	std::cout << "D to {0, 3}\trubber to {0, 0}\tG to {0, 5}" << std::endl;
	
	d1.swim(3);
	d4.swim(0);
	d3.swim(5);

	print_field(field, size);
#ifdef STEP_BY_STEP
	std::cout << "\nPress enter for next test." << std::endl;
	std::cin.get();
#endif


	/* flying */
	std::cout << "\nFlying\n=====\n";
	std::cout << "D flying 3 times\tR flying 1 time\t\tG flying 1 time\t\trubber flying 1 time" << std::endl;
	try
	{
		d1.fly(); d1.fly(); d1.fly();
		d2.fly();
		d3.fly();
	}
	catch (const std::exception &e)
	{
		std::cerr << "Problems with simple ducks : " << e.what() << std::endl;
	}
	try
	{
		d4.fly();
	}
	catch (const std::exception &e)
	{
		std::cerr << "Flying rubber duck: " << e.what() << std::endl;
	}
	print_field(field, size);
}

int main()
{
	const int size = 20;
	char **field = create_field(size);
	print_field(field, size);
	
	test(field, size);

	free_field(field, size);
	
	return 0;
}
