#include <math.h>

float projectileDestinationWithDrag(const float initialHeight, const float initialVelocity, const float mass, const float initialAngle, const float k, const float deltaT)
{
	if(initialHeight<=0 || initialVelocity<=0 || mass<=0 || initialAngle<=-90 || initialAngle>=90)
	{
		return NAN;
	}
	
	float v = initialVelocity;
	float vY = initialVelocity*sin(initialAngle*(3.14159/180));
	float vX = initialVelocity*cos(initialAngle*(3.14159/180));
	
	float hY = 0;
	float hX = 0;
	
	float drag_F = k*initialVelocity*initialVelocity;
	float drag_accY = (drag_F*sin(initialAngle*(3.14159/180)))/mass;
	float drag_accX = (drag_F*cos(initialAngle*(3.14159/180)))/mass;
	
	float aX = -drag_accX;
	float aY = -drag_accY-9.8;
	
	while(hY>(-1)*initialHeight)
	{
		hY = hY+(vY*deltaT)+(0.5*aY*deltaT*deltaT);
		hX = hX+(vX*deltaT)+(0.5*aX*deltaT*deltaT);
		
		vY = vY+(aY*deltaT);
		vX = vX+(aX*deltaT);
		
		v = sqrt((vX*vX)+(vY*vY));
		drag_accY = (k*v*vY)/mass;
		drag_accX = (k*v*vX)/mass;
		
		aX = -drag_accX;
		aY = -drag_accY-9.8;
		
		if(vX<=0)
		{
			hY = (-1)*initialHeight;
		}
	}
	
	return hX;
}
#ifndef MARMOSET_TESTING

#include <iostream>
#include <stdlib.h>

using namespace std;

int main(const int argc, const char *argv[])
{
	float d = projectileDestinationWithDrag(atof(argv[1]), atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]), atof(argv[6]));
	cout<<d<<endl;
	return 0;
}

#endif