#include <iostream>
#include <cstdlib>

using namespace std;

class IsZero { /* ... */ };

void ZeroCheck( int i )
{
	if (i==0)
		throw IsZero();
}

void mmain()
{
	double a;
 
	cout << "Enter a number: ";
	cin >> a;
	try
	{
		ZeroCheck( a );
		cout << "Reciprocal is " << 1.0/a << endl;
	}
	catch ( IsZero )
	{
		cout << "Zero input is not valid" << endl;
		exit(1);
	}
}

void func()
{
	int x = 5, y = 10, s;

	try
	{
		s = x * y;
		if(s == 50)
			throw runtime_error("It is 50");
	}
	catch(runtime_error e)
	{
		cout << e.what() << endl;
	}
}


int main()
{
	func();

	return(0);
}
