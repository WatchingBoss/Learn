#include <iostream>
#include <string>
#include <cctype>
#include <vector>

void
upChar()
{
	std::string s("word");

	std::cout << "Enter lowercase sentence: ";
	std::getline(std::cin, s);

	for(char &c : s)
		c = std::toupper(c);
	
	std::cout << s << "\n";
}

void
vect()
{
	std::vector<unsigned> scores(11, 0);
	unsigned grade;
	while(std::cin >> grade)
	{
		if(grade <= 100)
			++scores[grade/10];
	}
	for(int i = 0; i < 11; i++)
		std::cout << scores[i] << " ";
	std::cout << std::endl;

}

void
upFChar()
{
	std::string s("word");

	std::cout << "Enter lowercase sentence: ";
	std::getline(std::cin, s);

	if(s.begin() != s.end())
	{
		auto it = s.begin();
		*it = toupper(*it);
	}

	std::cout << s << "\n";
}


int
main()
{
	vect();
    
    return(0);
}
