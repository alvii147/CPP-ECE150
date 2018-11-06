#include <iostream>
#include <stdlib.h>

using namespace std;

int main(const int argc, const char *argv[])
{	
	int rc = 0;
	
	if(argc<3)
	{
		cerr<<"Error: Expected at least 2 arguments; received "<<argc-1<<"exiting"<<endl;
		rc = -1;
	}
	
	int window = atoi(argv[1]);
	
	if(window<=0)
	{
		cerr<<"Error: Window size negative; exiting"<<endl;
		rc = -1;
	}
	
	cout<<"Window Size: "<<window<<endl;
	cout<<"Sample\tValue\tSWMinimum\tSWMaximum"<<endl;
	
	/*
	int x = 0;
	for(int i = 2; i<argc; i++)
	{
		if(atof(argv[i])>0 && atof(argv[i])<150)
		{
			x++;
		}
	}
	float valid_arr[x];
	int y = 0;
	for(int i = 2; i<argc; i++)
	{
		if(atof(argv[i])>0 && atof(argv[i])<150)
		{
			valid_arr[y] = atof(argv[i]);
			y++;
		}
	}
	*/
	
	int j = 2;
	int i;
	int max;
	int min;
	
	while(j<window+1)
	{
		i = 2;
		max = 0;
		min = 150;
		if(atof(argv[j])>=150)
		{
			cout<<"Warning: invalid voltage reading "<<atof(argv[j])<<" ignored in calculation"<<endl;
		}
		else if(atof(argv[j])<0)
		{
			j = window+1;
		}
		else
		{
			while(i<j+1)
			{
				if(atof(argv[i])>0 && atof(argv[i])<150)
				{
					if(atof(argv[i])>max)
					{
						max = atof(argv[i]);
					}
					if(atof(argv[i])<min)
					{
						min = atof(argv[i]);
					}
				}
				i++;
			}
			cout<<j-1<<"\t"<<atof(argv[j])<<"\t"<<min<<"\t"<<max<<endl;
		}
		j++;
	}
	
	j = window+1;
	
	while(j<argc)
	{
		i = j-window+1;
		max = 0;
		min = 150;
		if(atof(argv[j])>=150)
		{
			cout<<"Warning: invalid voltage reading "<<atof(argv[j])<<" ignored in calculation"<<endl;
		}
		else if(atof(argv[j])<0)
		{
			j = argc;
		}
		else
		{
			while(i<=j)
			{
				if(atof(argv[i])>0 && atof(argv[i])<150)
				{
					if(atof(argv[i])>max)
					{
						max = atof(argv[i]);
					}
					if(atof(argv[i])<min)
					{
						min = atof(argv[i]);
					}
				}
				i++;
			}
			cout<<j-1<<"\t"<<atof(argv[j])<<"\t"<<min<<"\t"<<max<<endl;
		}
		j++;
	}
	
	if(atof(argv[argc-1])>=0)
	{
		cerr<<"Error: Missing terminator"<<endl;
		rc = -1;
	}
}