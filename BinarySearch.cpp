int binarySearchHelper(const int data[], const int startIndex, const int numElements, const int numberToFind)
{
	if(startIndex>numElements)
	{
		return -1;
	}
	int mid = (numElements+startIndex)/2;
	if(data[mid]==numberToFind)
	{
		return mid;
	}
	else if(data[mid]<numberToFind)
	{
		return binarySearchHelper(data, mid+1, numElements, numberToFind);
	}
	else if(data[mid]>numberToFind)
	{
		return binarySearchHelper(data, startIndex, mid-1, numberToFind);
	}
	return 0;
}

int binarySearch(const int data[], const int numElements, const int numberToFind)
{
	int loc = binarySearchHelper(data, 0, numElements-1, numberToFind);
	return loc;
}

#ifndef MARMOSET_TESTING

#include <iostream>
#include <stdlib.h>

using namespace std;

int main(const int argc, const char *argv[])
{
	int dataset[] = {2, 5, 16, 18, 39, 48, 49, 77, 89};
	int location = binarySearch(dataset, 9, 49);
	cout<<location<<endl;
	return 0;
}

#endif