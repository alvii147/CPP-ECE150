#ifndef CARTESIAN_H
#define CARTESIAN_H

class CartesianPoint
{
	public:
		float distance(CartesianPoint const &p) const;
		
		bool operator==(CartesianPoint const &p) const;
		
		void operator=(CartesianPoint const &p);
		
		CartesianPoint(CartesianPoint const &p);
		CartesianPoint(float x, float y);
		~CartesianPoint();
		
	private:
		#define COMPARE_DELTA 1e-5
		
		float m_x;
		float m_y;
		
		friend std::ostream &operator<<(std::ostream &os, CartesianPoint const &p);
};

#endif