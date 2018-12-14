#include <iostream>
#include <math.h>
#include "CartesianPoint.h"

using namespace std;

CartesianPoint::CartesianPoint(CartesianPoint const &p)
{
	m_x = p.m_x;
	m_y = p.m_y;
}

CartesianPoint::CartesianPoint(float x, float y)
{
	m_x = x;
	m_y = y;
}

CartesianPoint::~CartesianPoint()
{
	m_x = 0;
	m_y = 0;
}

float CartesianPoint::distance(const CartesianPoint &p) const
{
	float delX = m_x - p.m_x;
	float delY = m_y - p.m_y;
	float dis = sqrt(pow(delX, 2) + pow(delY, 2));
	return dis;
}

bool CartesianPoint::operator==(CartesianPoint const &p) const
{
	float delX = m_x - p.m_x;
	float delY = m_y - p.m_y;
	
	if(delX < 0)
	{
		delX *= -1;
	}
	if(delY < 0)
	{
		delY *= -1;
	}
	
	if(delX <= COMPARE_DELTA && delY <= COMPARE_DELTA)
	{
		return true;
	}
	return false;
}

void CartesianPoint::operator=(CartesianPoint const &p)
{
	m_x = p.m_x;
	m_y = p.m_y;
	return;
}

std::ostream &operator<<(std::ostream &os, CartesianPoint const &p)
{
	os<<'('<<p.m_x<<", "<<p.m_y<<')';
	return os;
}

#ifndef MARMOSET_TESTING

int main()
{
	return 0;
}

#endif