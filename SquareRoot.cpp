#include <iostream>
#include <cstdlib>

using namespace std;

int main(const int argc, const char *argv[])
{
	int rc = 0;
	
	if(argc < 2)
	{
		cerr<<"Error: Expected 1 argument; received "<<argc-1<<"; exiting"<<endl;
		return 1;
	}
	
	if(argc > 2)
	{
		cerr<<"Error: Expected 1 argument; received "<<argc-1<<"; ignoring extraneous arguments"<<endl;
	}
	
	float s = atof(argv[1]);
	float x = s/2;
	float p = (s-(x*x))/s;
	
	if(s<0)
	{
		cerr<<"Error: Negative values have no square root; exiting"<< endl;
		return 1;
	}
	if(p<0)
	{
		p = p*(-1);
	}
	
	while(p>0.00001)
	{
		x = (x+(s/x))/2;
		p = (s-(x*x))/s;
		if(p<0)
		{
			p = p*(-1);
		}
	}
	
	cout<<"The square root of "<<s<<" is "<<x<<endl;
}