#include <iostream>
#include <math.h>
#include <cstdlib>

using namespace std;

int main(const int argc, const char *argv[])
{
	int rc = 0;
	int type;
	int angle;
	
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
	
	float a3 = (acos((pow(s1, 2.0)+pow(s2, 2.0)-pow(s3, 2.0))/(2*s1*s2)))*(180/3.141592);
	float a2 = (acos((pow(s1, 2.0)+pow(s3, 2.0)-pow(s2, 2.0))/(2*s1*s3)))*(180/3.141592);
	float a1 = (acos((pow(s3, 2.0)+pow(s2, 2.0)-pow(s1, 2.0))/(2*s3*s2)))*(180/3.141592);
	
	if((sqrt(pow(s1-s2, 2.0))<=0.01)&&(sqrt(pow(s1-s3, 2.0))<=0.01))
	{
		type = 1;
	}
	else if((sqrt(pow(s1-s2, 2.0))<=0.01)||(sqrt(pow(s1-s3, 2.0))<=0.01)||(sqrt(pow(s3-s2, 2.0))<=0.01))
	{
		type = 2;
	}
	else
	{
		type = 3;
	}
	
	if((sqrt(pow(a1-90, 2.0))<=0.01)||(sqrt(pow(a2-90, 2.0))<=0.01)||(sqrt(pow(a3-90, 2.0))<=0.01))
	{
		angle = 1;
	}
	else if((a1>90)||(a2>90)||(a3>90))
	{
		angle = 2;
	}
	else
	{
		angle = 3;
	}
	
	cout<<"The triangle formed by points ("<<x1<<","<<y1<<"), ("<<x2<<","<<y2<<"), and ("<<x3<<","<<y3<<") is: ";
	if(type == 1)
	{
		cout<<"equilateral ";
	}
	else if(type == 2)
	{
		cout<<"isosceles ";
	}
	else if(type == 3)
	{
		cout<<"scalene ";
	}
	
	if(angle == 1)
	{
		cout<<"right"<<endl;
	}
	else if(angle == 2)
	{
		cout<<"obtuse"<<endl;
	}
	else if(angle == 3)
	{
		cout<<"acute"<<endl;
	}
	
	cout<<"The area of the triangle formed by points "<<"("<<x1<<", "<<y1<<"), ("<<x2<<", "<<y2<<"), and ("<<x3<<", "<<y3<<") is: "<<a<<endl;
}