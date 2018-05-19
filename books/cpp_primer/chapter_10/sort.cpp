/*
 * Using library algorithm sort()
 */
#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
	std::vector <std::string> names = {"Johnny", "Katrin", "Antony",
									   "Montherat", "Boris", "Cindy"};

	std::sort(names.begin(), names.end());

	std::cout << "Sorted names: \n";
	for (auto word = names.cbegin(); word != names.cend(); ++word)
		std::cout << *word << "\n";
	std::cout << std::endl;
}
