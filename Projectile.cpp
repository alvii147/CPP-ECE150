#include <math.h>

float projectileDestination(const float initialHeight, const float initialVelocity, const float mass, const float initialAngle)
{
	if(initialHeight<=0 || initialVelocity<=0 || mass<=0 || initialAngle<=-90 || initialAngle>=90)
	{
		return NAN;
	}
	
	float a = pow(initialVelocity, 2)*(sin((initialAngle*3.141592)/180))*(cos((initialAngle*3.141592)/180));
	
	float b = initialVelocity*(cos((initialAngle*3.141592)/180))*(sqrt(pow(initialVelocity, 2)*pow(sin((initialAngle*3.141592)/180), 2)+(19.6*initialHeight)));
	
	float horizontalRange = (a+b)/9.8;
	
	return horizontalRange;
}

#ifndef MARMOSET_TESTING

#include <iostream>
#include <stdlib.h>

using namespace std;

int main(const int argc, const char *argv[])
{
	float h = atof(argv[1]);
	float v = atof(argv[2]);
	float m = atof(argv[3]);
	float t = atof(argv[4]);
	
	float d = projectileDestination(h, v, m, t);
	
	cout<<"Horizontal Range: "<<d<<endl;
	
	return 0;
}

#endif