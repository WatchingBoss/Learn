#include <iostream>
#include <vector>

int main()
{
	std::vector<int> iVector;

	std::cout << "size: " << iVector.size() << "\n"
			  << "capacity: " << iVector.capacity() << std::endl;

	for(int i = 0; i < 20; ++i)
	{
		iVector.push_back(i);

		std::cout << "size: " << iVector.size() << "\n"
				  << "capacity: " << iVector.capacity() << std::endl;		
	}

	return(0);
}

/*
 * 	We can see that when size == capasity, capasity *= 2;
 */


