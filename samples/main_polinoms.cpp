#include <iostream>
#include <string>
#include "../include/polinom.h"

int main()
{
	int chooseOperation;
	std::string polinom;
	std::string polinom_right;
	std::cout << "             PROGRAMM FOR OPERATION WITH POLINOMS             " << std::endl;
	std::cout << "--------------------------------------------------------------" << std::endl;
	std::cout << "RULES FOR ENTERING YOUR POLINOM:\n1) Dont use space\n2) Entering variables in xyz order\n3) Dnt entering null monom" << std::endl;
	std::cout << "Enter your polinoms:" << std::endl;
	std::cin >> polinom;
	std::cout << "Enter your second polinoms:" << std::endl;
	std::cin >> polinom_right;
	std::cout << "Choose operation:\n1 - '+'\n2 - '-'\n3 - '*'(with const number)\n4 - '*'(with polinom)\nEnter number:" << std::endl;
	std::cin >> chooseOperation;
	try
	{
		Polinoms userPolinom1(polinom);
		Polinoms userPolinom2(polinom);
		switch (chooseOperation)
		{
		case(1):
		{
			std::cout << userPolinom1 << "+" << userPolinom2 << "=\n" << userPolinom1 + userPolinom2 << std::endl;
		}
		case(2):
		{
			std::cout << userPolinom1 << "-" << userPolinom2 << "=\n" << userPolinom1 - userPolinom2 << std::endl;
		}
		case(3):
		{
			double alpha;
			std::cout << "enter a number:" << std::endl;
			std::cin >> alpha;
			std::cout << userPolinom1 << "*" << alpha << "=\n" << userPolinom1 * alpha << std::endl;
		}
		case(4):
		{
			std::cout << userPolinom1 << "*" << userPolinom2 << "=\n" << userPolinom1 * userPolinom2 << std::endl;
		}
		default:
		{
			std::cout << "uncorrect choose";
			break;
		}
		}
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}	
}