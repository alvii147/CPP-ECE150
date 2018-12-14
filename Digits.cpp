#include <iostream>
#include <math.h>

using namespace std;

void swap(int data[], int i, int j)
{
	int tmp = data[i];
	data[i] = data[j];
	data[j] = tmp;
	return;
}

void bubbleAscend(int data[], int size)
{
	int condition = 0;
	while(!condition)
	{
		condition = 1;
		for(int i = 1; i < size; i++)
		{
			if(data[i - 1] < data[i])
			{
				swap(data, i - 1, i);
				condition = 0;
			}
		}
	}
	return;
}

void nextLargeArrangementHelper(int data[], int idx)
{
	int base = data[idx];
	int swpIdx = 0;
	int swpNum = 10;
	for(int i = 0; i < idx; i++)
	{
		if(data[i] > base && data[i] < swpNum)
		{
			swpIdx = i;
			swpNum = data[swpIdx];
		}
	}
	swap(data, swpIdx, idx);
	bubbleAscend(data, idx);
	return;
}

long long nextLargestArrangement(long long n)
{
	int length = log10(n) + 1;
	long long x = 0;
	if(length == 1)
	{
		return -1;
	}
	int num[length+1];
	for(int i = 1; i <= length; i++)
	{
		num[i - 1] = (n%((int)(pow(10, i))) - n%((int)(pow(10, i - 1))))/pow(10, i - 1);
	}
	
	if(num[0] > num[1])
	{
		swap(num, 0, 1);
		for(int i = 0; i < length; i++)
		{
			x = x + (num[i]*pow(10, i));
		}
		return x;
	}
	int condition = 0;
	int index = 0;
	for(int i = 1; i < length; i++)
	{
		if(num[i] < num[i - 1])
		{
			condition = 1;
			index = i;
		}
	}
	if(!condition)
	{
		return -1;
	}
	
	cout<<endl;
	nextLargeArrangementHelper(num, index);
	
	for(int i = 0; i < length; i++)
	{
		x = x + (num[i]*pow(10, i));
	}
	return x;
}

#ifndef MARMOSET_TESTING

int main()
{
	cout<<nextLargestArrangement(37824)<<endl;
	return 0;
}

#endif