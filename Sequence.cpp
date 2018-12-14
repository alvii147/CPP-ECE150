#include <iostream>

using namespace std;

bool arithmeticSequence(int const x[], int size)
{
	if(size < 1)
	{
		return false;
	}
	int d = x[1] - x[0];
	for(int i = 2; i < size; i++)
	{
		if(x[i] - x[i-1] != d)
		{
			return false;
		}
	}
	return true;
}

#ifndef MARMOSET_TESTING

int main()
{
	return 0;
}

#endif