#include <iostream>
#include <math.h>

using namespace std;

int countZerosAndOnes(const int zeroOneData[], const int numSamples, const int kMax, int& zeroCount, int& oneCount)
{
	if(kMax<0 || numSamples<1)
	{
		return -1;
	}
	
	enum State {START, DONE, GOT_ZERO, GOT_ONE,GOT_KTH_ZERO, GOT_KTH_ONE};
	State s = START;
	int i = 0;
	int k = 0;
	int input;
	zeroCount = 0;
	oneCount = 1;
	int rc = 0;
	
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
					s = GOT_ONE;
				}
				else if(input == 0)
				{
					s = GOT_KTH_ZERO;
				}
				else
				{
					return -1;
				}
				break;
			
			case GOT_KTH_ONE:
				if(i>numSamples)
				{
					s = DONE;
				}
				else if(k>kMax)
				{
					s = GOT_ONE;
					oneCount++;
				}
				else if(input == 1)
				{
					s = GOT_KTH_ONE;
				}
				else if(input == 0)
				{
					s = GOT_ZERO;
					k = 0;
				}
				else
				{
					return -1;
				}
				break;
			
			case GOT_KTH_ZERO:
				if(i>numSamples)
				{
					s = DONE;
				}
				else if(k>kMax)
				{
					s = GOT_ZERO;
					zeroCount++;
				}
				else if(input == 1)
				{
					s = GOT_ONE;
					k = 0;
				}
				else if(input == 0)
				{
					s = GOT_KTH_ZERO;
				}
				else
				{
					return -1;
				}
				break;
				
			case GOT_ONE:
				if(i>numSamples)
				{
					s = DONE;
				}
				else if(input == 1)
				{
					s = GOT_ONE;
				}
				else if(input == 0)
				{
					s = GOT_KTH_ZERO;
					k = 0;
				}
				else
				{
					return -1;
				}
				break;
			
			case GOT_ZERO:
				if(i>numSamples)
				{
					s = DONE;
				}
				else if(input == 1)
				{
					s = GOT_KTH_ONE;
					k = 0;
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
				break;
		}
		
		//state processes
		switch(s)
		{
			case GOT_KTH_ONE:
				i++;
				k++;
				break;
			
			case GOT_KTH_ZERO:
				i++;
				k++;
				break;
			
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
				break;
		}
	}
	return rc;
}

#ifndef MARMOSET_TESTING

int main()
{
	int zeroCount = 0;
	int oneCount = 0;
	
	int data[6] = {0, 0, 0, 1, 0, 0};
	
	countZerosAndOnes(data, 8, 1, zeroCount, oneCount);
	
	cout<<zeroCount<<endl;
	cout<<oneCount<<endl;
	
	return 0;
}

#endif