#include <iostream>
#include <stdlib.h>

using namespace std;

int main(const int argc, const char *argv[])
{
	int rc = 0;
	
	if(argc<2)
	{
		cerr<<"Error: Unable to compute median over data set because no arguments were found"<<endl;
		rc = -1;
	}
	
	float valid_arr[argc-1];
	int j = 0;
	for(int i = 1; i<argc; i++)
	{
		if(atof(argv[i])>0 && atof(argv[i])<150)
		{
			valid_arr[j] = atof(argv[i]);
			j++;
		}
		else if(atof(argv[i])>=150)
		{
			cout<<"Warning: invalid voltage reading "<<atof(argv[i])<<" ignored in calculation"<<endl;
			rc = 1;
		}
		else if(atof(argv[i])<0)
		{
			i = argc;
		}
	}
	
	int status = 1;
	float holder = 0;
	
	while(status)
	{
		status = 0;
		for(int i = 0; i<j-2; i++)
		{
			if(valid_arr[i]>valid_arr[i+1])
			{
				holder = valid_arr[i];
				valid_arr[i] = valid_arr[i+1];
				valid_arr[i+1] = holder;
				holder = 0;
				status = 1;
			}
		}
	}
	
	float median;
	if(j%2 == 1)
	{
		median = valid_arr[(j-1)/2];
	}
	else if(j%2 == 0)
	{
		median = (valid_arr[j/2]+valid_arr[(j/2)-1])/2;
	}
	cout<<"Number of voltage readings: "<<j<<endl;
	cout<<"Median voltage: "<<median<<endl;
	
	return rc;
}