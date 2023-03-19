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
	std::cout << "RULES FOR ENTERING YOUR POLINOM:\n1) Dont use space and use only ',')\n2) Entering variables in xyz order\n3) Dont entering null monom" << std::endl;
	std::cout << "Enter your polinoms:" << std::endl;
	std::cin >> polinom;
	std::cout << "Enter your second polinoms:" << std::endl;
	std::cin >> polinom_right;
	std::cout << "Choose operation:\n1 - '+'\n2 - '-'\n3 - '*'(with const number)\n4 - '*'(with polinom)\nEnter number:" << std::endl;
	std::cin >> chooseOperation;
	try
	{
		Polinoms userPolinom1(polinom);
		Polinoms userPolinom2(polinom_right);
		switch (chooseOperation)
		{
		case(1):
		{
			userPolinom1.show();
			std::cout << "+";
			userPolinom2.show();
			std::cout << "=\n";
			(userPolinom1 + userPolinom2).show();
			break;
		}
		case(2):
		{
			userPolinom1.show();
			std::cout << "-";
			userPolinom2.show();
			std::cout << "=\n";
			(userPolinom1 - userPolinom2).show();
			break;
		}
		case(3):
		{
			double alpha;
			std::cout << "enter a number:" << std::endl;
			std::cin >> alpha;
			userPolinom1.show();
			std::cout << "*" << alpha;
			std::cout << "=\n";
			(userPolinom1 * alpha).show();
			break;
		}
		case(4):
		{
			userPolinom1.show();
			std::cout << "*";
			userPolinom2.show();
			std::cout << "=\n";
			(userPolinom1 * userPolinom2).show();
			break;
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