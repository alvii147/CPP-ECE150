#include <iostream>
#include <cstdlib>

using namespace std;

extern float f(float t);

int main(const int argc, const char *argv[])
{
	int rc = 0;
	
	if(argc < 2)
	{
		cerr<<"Error: Expected 1 argument; received "<<argc-1<<"; exiting"<<endl;
		return -1;
	}
	if(argc > 2)
	{
		cerr<<"Error: Expected 1 argument; received "<<argc-1<<"; ignoring extraneous arguments"<<endl;
	}
	
	float x = atof(argv[1]);
	
	float d1 = f(x-0.0001);
	float d2 = f(x+0.0001);
	
	float slope = ((d2-d1)/0.0002);
	
	cout<<"The slope of f(t) at "<<x<<" is "<<slope<<endl;
	
	return rc;
}