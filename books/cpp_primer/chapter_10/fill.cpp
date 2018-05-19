#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
	std::vector <std::string> sVector;

	for(int i = 0; i < 10; ++i)
		sVector.push_back("hello");

	for(int i = 0; i < 10; ++i)
		std::cout << sVector[i] << std::endl;
	
	std::fill(sVector.begin(), sVector.end(), "it is fill algorithm");

	for(int i = 0; i < 10; ++i)
		std::cout << sVector[i] << std::endl;

	for(int i = 0; i < 10; ++i)
		sVector.at(i) = "it is at function";

	for(int i = 0; i < 10; ++i)
		std::cout << sVector[i] << std::endl;

	return(0);
}
