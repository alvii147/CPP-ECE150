#include <iostream>
#include <math.h>
#include <cstdlib>
using namespace std;

int main(const int argc, const char *argv[])
{
	int rc = 0;
	if(argc != 7)
	{
		cerr<<"Usage: 6 arguments required, "<<argc-1<<" arguments found"<<endl;
		rc = 1;
	}
	
	float x1 = atof(argv[1]);
	float y1 = atof(argv[2]);
	float x2 = atof(argv[3]);
	float y2 = atof(argv[4]);
	float x3 = atof(argv[5]);
	float y3 = atof(argv[6]);

	float d1 = x2-x1;
	float d2 = y2-y1;
	float d3 = x3-x2;
	float d4 = y3-y2;
	float d5 = x3-x1;
	float d6 = y3-y1;
  
	float s1 = sqrt(pow(d1, 2.0)+pow(d2, 2.0));
	float s2 = sqrt(pow(d3, 2.0)+pow(d4, 2.0));
	float s3 = sqrt(pow(d5, 2.0)+pow(d6, 2.0));

	float s = 0.5*(s1+s2+s3);

	float a = sqrt(s*(s-s1)*(s-s2)*(s-s3));

	cout<<"The area of the triangle formed by points "<<"("<<x1<<", "<<y1<<"), ("<<x2<<", "<<y2<<"), and ("<<x3<<", "<<y3<<") is: "<<a<<endl;
	
	return rc;
}