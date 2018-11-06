#include <iostream>
#include <stdlib.h>

using namespace std;

int main(const int argc, const char *argv[])
{
	float min = 150;
	float max = 0;
	float sum = 0;
	int counter = 0;
	float average;
	int rc = 0;
	
	for(int i = 1; i<argc; i++)
	{
		if(atof(argv[i])>=150)
		{
			cout<<"Warning: invalid voltage reading "<<atof(argv[i])<<" ignored in calculation"<<endl;
			rc = 1;
		}
	}
	
	for(int j = 1; j<argc; j++)
	{
		if(atof(argv[j])>=0 && atof(argv[j])<150)
		{
			if(atof(argv[j])<min)
			{
				min = atof(argv[j]);
			}
		}
	}
	
	for(int k = 1; k<argc; k++)
	{
		if(atof(argv[k])>=0 && atof(argv[k])<150)
		{
			if(atof(argv[k])>max)
			{
				max = atof(argv[k]);
			}
		}
	}
	
	for(int l = 1; l<argc; l++)
	{
		if(atof(argv[l])>=0 && atof(argv[l])<150)
		{
			sum+=atof(argv[l]);
			counter+=1;
		}
	}
	
	if(counter==0)
	{
		cerr<<"Error: Unable to compute statistics over data set because no valid arguments were given"<<endl;
		rc = -1;
	}
	
	average = sum/counter;
	
	cout<<"Number of voltage readings: "<<counter<<endl;
	cout<<"Minimum voltage: "<<min<<endl;
	cout<<"Average voltage: "<<average<<endl;
	cout<<"Maximum voltage: "<<max<<endl;
	
	return rc;
}