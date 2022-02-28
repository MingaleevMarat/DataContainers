#include <iostream>

long long int factorial(unsigned int  n)
{
	/*unsigned long long int result = 1;
	for (unsigned short int i = 1; i <= n; i++)
		result *= i;
	return result;*/
	/*if (n <= 1)
		return 1;
	return n * factorial(n - 1);*/
	return n <= 1 ? 1 : n * factorial(n - 1);
}

double pow(double a, unsigned int n)
{
	/*double result = 1;
	for (unsigned short int i = 0; i < n; ++i)
		result *= a;
	return result;*/
	/*if (n==0)
		return 1;
	return a*pow(a,n-1);*/
	return !n ? 1 : a * pow(a, n - 1);
	// !n - n==0
}
void main()
{
	unsigned  int n;
	std::cout << "Enter the number to count factorial: ";
	std::cin >> n;
	std::cout << "Factorial: " << factorial(n) << std::endl;
	
	std::cout << "Enter base of degree: ";
	double base;
	std::cin >> base;
	std::cout << "Enter exponent of degree: ";
	unsigned int exponent;
	std::cin >> exponent;
	std::cout << "Degree: " << pow(base, exponent) << std::endl;
}