#include <iostream>
#include <stdlib.h>

using namespace std;

int main(const int argc, const char *argv[])
{
	int counter = 0;
	float average;
	float alpha;
	int rc = 0;
	
	if(argc<3)
	{
		cerr<<"Error: Expected at least 2 arguments; received "<<argc-1<<"exiting"<<endl;
		rc = -1;
	}
	
	cout<<"Sample\tValue\tEWMA"<<endl;
	
	alpha = atof(argv[1]);
	
	if(atof(argv[argc-1])>=0)
	{
		cerr<<"Error: Missing terminator"<<endl;
		rc = -1;
	}
	
	if(alpha>1 || alpha<0)
	{
		cerr<<"Error: Value of alpha must be between 0 and 1"<<endl;
		rc = -1;
	}
	int cond = 0;
	for(int j = 2; j<argc; j++)
	{
		if(atof(argv[j])>0 && atof(argv[j])<150)
		{
			if(cond == 0)
			{
				average = atof(argv[j]);
				cout<<1<<"\t"<<average<<"\t"<<average<<endl;
				cond = 1;
			}
			else
			{
				average = (alpha)*(atof(argv[j]))+(1-alpha)*(average);
				cout<<j-1<<"\t"<<atof(argv[j])<<"\t"<<average<<endl;
				counter+=1;
			}
		}
		else if(atof(argv[j])>=150 || atof(argv[j])== 0)
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
	
	return rc;
}