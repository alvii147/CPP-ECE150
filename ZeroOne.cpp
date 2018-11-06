#include <iostream>
#include <math.h>

using namespace std;

/*
int getNumber(const int dataArr[], int i, const int size)
{
	if(i<size)
	{
		float value = dataArr[i];
		i++;
		return value;
	}
	else
	{
		return NAN;
	}
}
*/

int countZerosAndOnes(const int zeroOneData[], const int numSamples, int& zeroCount, int& oneCount)
{
	enum State { START, DONE, GOT_ZERO, GOT_ONE };
	State s = START;
	int i = 0;
	int rc = 0;
	int input;
	if(numSamples<1)
	{
		cerr<<"An unknown error has occured"<<endl;
		return -1;
	}
	
	while(s!=DONE)
	{
		if(i<numSamples)
		{
			input = zeroOneData[i];
		}
		
		//transition processes
		switch(s)
		{
			case START:
				if(input == 1)
				{
					oneCount = 1;
					zeroCount = 0;
					s = GOT_ONE;
				}
				else if(input == 0)
				{
					oneCount = 0;
					zeroCount = 1;
					s = GOT_ZERO;
				}
				else
				{
					return -1;
				}
				break;
			
			case GOT_ONE:
				if(i>=numSamples)
				{
					s = DONE;
				}
				else if(input == 1)
				{
					s = GOT_ONE;
				}
				else if(input == 0)
				{
					zeroCount++;
					s = GOT_ZERO;
				}
				else
				{
					return -1;
				}
				break;
			
			case GOT_ZERO:
				if(i>=numSamples)
				{
					s = DONE;
				}
				else if(input == 1)
				{
					oneCount++;
					s = GOT_ONE;
				}
				else if(input == 0)
				{
					s = GOT_ZERO;
				}
				else
				{
					return -1;
				}
				break;
			
			case DONE:
			default:
				cerr<<"An unknown error occured"<<endl;
				return -1;
		}
		//Entering state processes
		switch(s)
		{
			case GOT_ONE:
				i++;
				break;
			
			case GOT_ZERO:
				i++;
				break;
			
			case DONE:
				rc = 0;
				break;
			
			case START:
			
			default:
				cerr<<"An unknown error occured"<<endl;
				return -1;
		}
	}
	return rc;
}

/*
int main()
{
	int zeroCount;
	int oneCount;
	int data[5] = {1, 0, 0, 1, 0};
	
	int count = countZerosAndOnes(data, 5, zeroCount, oneCount);
	
	cout<<zeroCount<<endl;
	cout<<oneCount<<endl;
	cout<<count<<endl;
	
	return 0;
}*/