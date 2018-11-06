#include <iostream>
#include <stdlib.h>

using namespace std;

int main(const int argc, const char *argv[])
{
	int rc = 0;
	
	int count[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int x = 0;
	int term = 0;
	
	for(int i = 1; i<argc; i++)
	{
		float volt = atof(argv[i]);
		
		if(volt>0 && volt<106)
		{
			count[0]+=1;
		}
		else if(volt>=106 && volt<109)
		{
			count[1]+=1;
		}
		else if(volt>=109 && volt<112)
		{
			count[2]+=1;
		}
		else if(volt>=112 && volt<115)
		{
			count[3]+=1;
		}
		else if(volt>=115 && volt<118)
		{
			count[4]+=1;
		}
		else if(volt>=118 && volt<121)
		{
			count[5]+=1;
		}
		else if(volt>=121 && volt<124)
		{
			count[6]+=1;
		}
		else if(volt>=124 && volt<=127)
		{
			count[7]+=1;
		}
		else if(volt>127 && volt<150)
		{
			count[8]+=1;
		}
		else if((volt<0.001 && volt>0) || volt>=150)
		{
			count[9]+=1;
			cout<<"Warning: invalid voltage reading "<<volt<<" ignored in calculation"<<endl;
		}
		else if(volt<0)
		{
			i = argc;
			x-=1;
			term = 1;
		}
		x++;
	}
	
	if(x==0)
	{
		cerr<<"Error: Unable to compute histogram over data set because no valid arguments were found"<<endl;
		rc = -1;
	}
	if(term == 0)
	{
		cerr<<"Error: Missing terminator"<<endl;
		rc = -1;
	}
	
	cout<<"Number of voltage readings: "<<x-count[9]<<endl;
	cout<<"Voltage readings (0-106): "<<count[0]<<endl;
	cout<<"Voltage readings [106-109): "<<count[1]<<endl;
	cout<<"Voltage readings [109-112): "<<count[2]<<endl;
	cout<<"Voltage readings [112-115): "<<count[3]<<endl;
	cout<<"Voltage readings [115-118): "<<count[4]<<endl;
	cout<<"Voltage readings [118-121): "<<count[5]<<endl;
	cout<<"Voltage readings [121-124): "<<count[6]<<endl;
	cout<<"Voltage readings [124-127]: "<<count[7]<<endl;
	cout<<"Voltage readings (127-150): "<<count[8]<<endl;
	cout<<"Invalid readings: "<<count[9]<<endl;
	
	return rc;
}