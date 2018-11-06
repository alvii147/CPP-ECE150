int partition(int data[], const int lo, const int hi)
{
	if(hi<0 || lo<0 || hi-lo<2)
	{
		return -1;
	}
	int pivot = data[hi];
	int pivotIndex = lo;
	int dataIndex = lo;
	int temp = 0;
	
	while(dataIndex<hi)
	{
		if(data[dataIndex]<pivot)
		{
			temp = data[dataIndex];
			data[dataIndex] = data[pivotIndex];
			data[pivotIndex] = temp;
			pivotIndex++;
		}
		dataIndex++;
	}
	temp = data[pivotIndex];
	data[pivotIndex] = data[hi];
	data[hi] = temp;
	
	return pivotIndex;
}

void quickSortHelper(int data[], const int lo, const int hi)
{
	int temp = 0;
	if(hi>=0 && lo>=0 && hi-lo>=2)
	{
		int pivotPoint = partition(data, lo, hi);
		quickSortHelper(data, 0, pivotPoint-1);
		quickSortHelper(data, pivotPoint+1, hi);
	}
	else if(hi-lo == 1)
	{
		if(data[lo]>data[hi])
		{
			temp = data[lo];
			data[lo] = data[hi];
			data[hi] = temp;
		}
	}
}


int quickSort(int data[], const int numElements)
{
	int rc = 0;
	if(numElements<1)
	{
		rc = -1;
	}
	else
	{
		quickSortHelper(data, 0, numElements-1);
	}
	return 0;
}


#ifndef MARMOSET_TESTING

#include <iostream>
#include <stdlib.h>

using namespace std;

void printArray(const int data[], const int numElements)
{
	int i = 0;
	while(i<numElements-1)
	{
		cout<<data[i]<< ", ";
		++i;
	}
	cout<<data[numElements-1]<<endl;
}


int main(void)
{
	int sz = 5;
	
	srandom(0);
	
	int data[sz];
	
	int i = 0;
	while(i < sz)
	{
		data[i] = (int)random();
		++i;
	}
	
	cout<<"Array is: ";
	printArray(data, sz);
	
	int ret = quickSort(data, sz);
	
	cout<<"After sorting, array is: ";
	printArray(data, sz);

	if(ret<0)
	{
		cout<<"quickSort() indicated error"<<endl;
	}
	else if(ret>0)
	{
		cout<<"quickSort() indicated warning"<<endl;
	}
	return 0;
}

#endif