#include <math.h>

extern float f(float t);

static float bisectionHelper(const float left, const float right, const float minIntervalSize, int count)
{
	float c = f((left+right)/2);
	
	float x = 0;
	float y = 0;
	float fin = 0;
	
	if(minIntervalSize<=0)
	{
		return NAN;
	}
	if((f(left)*f(right))>0)
	{
		return NAN;
	}
	
	float ll = left;
	float rr = right;
	if(left>right)
	{
		ll = right;
		rr = left;
	}
	if((sqrt(pow(rr-ll,2))<minIntervalSize) || (count>=1000) || c == 0)
	{
		fin = (ll+rr)/2;
	}
	else if(count<1000)
	{
		if(c<0)
		{
			x = (ll+rr)/2;
			y = rr;
		}
		else if(c>0)
		{
			x = ll;
			y = (ll+rr)/2;
		}
		count++;
		fin = bisectionHelper(x, y, minIntervalSize, count);
	}
	return fin;
}

float bisection(const float left, const float right, const float minIntervalSize)
{
	return bisectionHelper(left, right, minIntervalSize, 1);
}

#ifndef MARMOSET_TESTING

#include <iostream>
#include <cstdlib>

using namespace std;

int main(const int argc, const char* const argv[])
{
	int rc = 0;
	if (argc != 3)
	{
		cerr<<"Error: Expected 2 arguments; received "<<argc-1<<"; exiting"<<endl;
		rc = -1;
	}
	
	float lbound = atof(argv[1]);
	float rbound = atof(argv[2]);
	
	if(lbound == rbound)
	{
		cerr<<"Error: Two points are the same"<<endl;
		rc = -1;
	}
	
	if(lbound>rbound)
	{
		float tmp;
		tmp = lbound;
		lbound = rbound;
		rbound = tmp;
	}
	
	float int_sz = 0.01;
	
	float root = bisection(lbound, rbound, int_sz);
	
	cout<<"f(t) has a root between t = "<<lbound<<" and t = "<<rbound<<" at t = "<<root<<endl; return rc;
}

#endif
