#include <iostream>

using namespace std;

int firstUpper(char const* s)
{
	int i = 0;
	while(s[i])
	{
		if(s[i] >= 'A' && s[i] <= 'Z')
		{
			return i;
		}
		i++;
	}
	return -1;
}

int firstDigit(char const* s)
{
	int i = 0;
	while(s[i])
	{
		if(s[i] >= '1' && s[i] <= '9')
		{
			return i;
		}
		i++;
	}
	return -1;
}

#ifndef MARMOSET_TESTING

int main()
{
	return 0;
}

#endif