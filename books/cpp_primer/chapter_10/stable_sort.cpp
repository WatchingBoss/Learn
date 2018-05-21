/*

 * Here we sort first words for lenght, then for alphabet

 */

#include <iostream>
#include <algorithm>
#include <vector>

bool isShorter(const std::string &s1, const std::string &s2)
{
	return s1.size() < s2.size();
}

int main()
{
	std::vector <std::string> words = {"slippery", "godly", "drop", "unusual",
									   "coast", "hook", "whistle", "piquant",
									   "splendid", "toothbrush", "salt", "lighten",
									   "annoy", "half", "far", "jealous", "scene",
									   "loose", "pinch", "pat"};

	stable_sort(words.begin(), words.end(), isShorter);

	for(const auto &s : words)
		std::cout << s << "   ";
	std::cout << std::endl;

	return(0);
}
