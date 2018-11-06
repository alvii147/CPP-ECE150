#include <iostream>
#include <stdlib.h>

using namespace std;

extern float f(float x);
int rc = 0;

int main(const int argc, const char *argv[])
{
	float a = atof(argv[1]);
	float b = atof(argv[2]);
	
	if(a>b)
	{
		cerr<<"Error: first argument greater than second; exiting"<<endl;
		rc = -1;
	}
	
	if(argc>3)
	{
		cerr<<"Warning: expected 2 arguments; received "<<argc-1<<"; ignoring extraneous arguments"<<endl;
		rc = 1;
	}
	
	if(argc<3)
	{
		cerr<<"Error: expected 2 arguments; received "<<argc-1<<"; exiting"<<endl;
		rc = -1;
	}
	
	float c = a;
	float p = 0.01;
	
	int i = 1;
	
	float area = 0;
	
	while(i != 0)
	{
		if(b-c<0)
		{
			i = 0;
		}
		else if(b-c<p)
		{
			p = b-c;
			area = area+(p)*((f(c+p)+f(c))/2);
			i = 0;
		}
		else if(b-c>=p)
		{
			area = area+(p)*((f(c+p)+f(c))/2);
			c+=p;
		}
	}
	cout<<"The area under f(x) from "<<a<<" to "<<b<<" is "<<area<<endl;
	
	return rc;
}