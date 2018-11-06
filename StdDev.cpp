#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

int main(const int argc, const char *argv[])
{
	int rc = 0;
	
	int x = 0;
	for(int i = 1; i<argc; i++)
	{
		if(atof(argv[i])>0 && atof(argv[i])<150)
		{
			x++;
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
	
	if(x==0)
	{
		cerr<<"Error: Unable to compute standard deviations over data set because no arguments were found"<<endl;
		rc = -1;
	}
	
	float valid_v[x];
	int y = 0;
	for(int i = 1; i<argc; i++)
	{
		if(atof(argv[i])>0 && atof(argv[i])<150)
		{
			valid_v[y] = atof(argv[i]);
			y++;
		}
		else if(atof(argv[i])<0)
		{
			i = argc;
		}
	}
	
	float sum = 0;
	for(int i = 0; i<x; i++)
	{
		sum+=valid_v[i];
	}
	
	float average = sum/x;
	
	float stdsum = 0;
	for(int i = 0; i<x; i++)
	{
		stdsum += (valid_v[i]-average)*(valid_v[i]-average);
	}
	
	float pop;
	float sam;
	
	pop = sqrt((stdsum)/(x));
	sam = sqrt((stdsum)/(x-1));
	
	int scenario = 0;
	
	if(x == 1)
	{
		if(sqrt(stdsum*stdsum)<0.001)
		{
			scenario = 1;
		}
		else if(stdsum>0)
		{
			scenario = 2;
		}
		else if(stdsum<0)
		{
			scenario = 3;
		}
	}
	
	if(scenario == 0)
	{
		cout<<"Number of voltage readings: "<<x<<endl;
		cout<<"Population standard deviation: "<<pop<<endl;
		cout<<"Sample standard deviation: "<<sam<<endl;
	}
	else if(scenario == 1)
	{
		cout<<"Number of voltage readings: "<<x<<endl;
		cout<<"Population standard deviation: "<<pop<<endl;
		cout<<"Sample standard deviation: "<<"undefined"<<endl;
	}
	else if(scenario == 2)
	{
		cout<<"Number of voltage readings: "<<x<<endl;
		cout<<"Population standard deviation: "<<pop<<endl;
		cout<<"Sample standard deviation: "<<"infinity"<<endl;
	}
	else if(scenario == 3)
	{
		cout<<"Number of voltage readings: "<<x<<endl;
		cout<<"Population standard deviation: "<<pop<<endl;
		cout<<"Sample standard deviation: "<<"-infinity"<<endl;
	}
	
	return rc;
}