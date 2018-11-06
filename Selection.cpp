#include <math.h>

int maxLocation(const int data[], const int numElements)
{
	int max = -2147483648;
	int loc;
	for(int i = 0; i<numElements; i++)
	{
		if(data[i]>=max)
		{
			max = data[i];
			loc = i;
		}
	}
	
	return loc;
}

int selectionSort(int data[], const int numElements)
{
	if(numElements>1)
	{
		int maxloc = maxLocation(data, numElements);
		int temp = data[numElements-1];
		data[numElements-1] = data[maxloc];
		data[maxloc] = temp;
		
		selectionSort(data, numElements-1);
	}
	else if(numElements<0)
	{
		return -1;
	}
	else if(numElements == 0)
	{
		return 0;
	}
	return 0;
}

#ifndef MARMOSET_TESTING

#include <iostream>
#include <stdlib.h>

using namespace std;

int main(const int argc, const char *argv[])
{
	int dataset[argc-1];
	
	for(int i = 0; i<argc-1; i++)
	{
		dataset[i] = atoi(argv[i+1]);
	}
	
	selectionSort(dataset, argc);
	
	return 0;
}

#endif