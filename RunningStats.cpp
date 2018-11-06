#include <iostream>
#include <stdlib.h>
#include <cmath>

using namespace std;

int main(const int argc, const char *argv[])
{
	float min = 150;
	float max = 0;
	float sum = 0;
	int counter = 0;
	float average;
	int rc = 0;
	
	if(argc<2)
	{
		cerr<<"Error: No arguments"<<endl;
	}
	
	cout<<"Sample\tValue\tMinimum\tAverage\tMaximum"<<endl;
	
	for(int j = 1; j<argc; j++)
	{
		if(atof(argv[j])>0 && atof(argv[j])<150)
		{
			if(atof(argv[j])<min)
			{
				min = atof(argv[j]);
			}
			
			if(atof(argv[j])>max)
			{
				max = atof(argv[j]);
			}
			
			sum+=atof(argv[j]);
			counter+=1;
			
			average = sum/counter;
			
			cout<<j<<"\t"<<atof(argv[j])<<"\t"<<min<<"\t"<<average<<"\t"<<max<<endl;
		}
		else if(atof(argv[j])>150 || atof(argv[j])== 0)
		{
			cout<<"Warning: invalid voltage reading "<<atof(argv[j])<<" ignored in calculation"<<endl;
			rc = 1;
		}
		if(atof(argv[j])<0)
		{
			j = argc;
		}
	}
	
	if(counter==0)
	{
		cerr<<"Error: Unable to compute statistics over data set because no valid arguments were given"<<endl;
		rc = -1;
	}
	
	if(atof(argv[argc-1])>0)
	{
		cerr<<"Error: Missing terminator"<<endl;
		rc = -1;
	}
	
	return rc;
}