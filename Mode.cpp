
int mode(const int dataset[], const int size, int modes[])
{
	int count = 1;
	int occ[size][2];
	int x = 0;
	for(int i = 0; i<size-1; i++)
	{
		if(dataset[i] == dataset[i+1])
		{
			count+=1;
			if(i == size-2)
			{
				occ[x][0] = dataset[i];
				occ[x][1] = count;
				count = 1;
				x++;
			}
		}
		else
		{
			occ[x][0] = dataset[i];
			occ[x][1] = count;
			count = 1;
			if(i == size-2)
			{
				occ[x+1][0] = dataset[i+1];
				occ[x+1][1] = 1;
			}
			x++;
		}
	}
	
	int max = 0;
	for(int a = 0; a<size; a++)
	{
		if(occ[a][1]>max)
		{
			max = occ[a][1];
		}
	}
	
	int y = 0;
	for(int b = 0; b<size; b++)
	{
		if(occ[b][1]==max)
		{
			modes[y] = occ[b][0];
			y++;
		}
	}
	
	if(size<0)
	{
		return -1;
	}
	
	return y;
}

#ifndef MARMOSET_TESTING
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(const int argc, const char *argv[])
{
	int rc = 0;
	int valid_arr[argc];
	int j = 0;
	float volt;
	for(int i = 1; i<argc; i++)
	{
		volt = atoi(argv[i]);
		valid_arr[j] = volt;
		j++;
	}
	
	int status = 1;
	float holder = 0;
	
	while(status)
	{
		status = 0;
		for(int i = 0; i<j-1; i++)
		{
			if(valid_arr[i]>valid_arr[i+1])
			{
				holder = valid_arr[i];
				valid_arr[i] = valid_arr[i+1];
				valid_arr[i+1] = holder;
				holder = 0;
				status = 1;
			}
		}
	}
	
	int modeslist[j];
	int num;
	num = mode(valid_arr, j, modeslist);
	
	if(num<=0)
	{
		cerr<<"Error: number of modes returned was less than or equal to zero"<<endl;
		rc = -1;
	}
	
	cout<<"Function returned: "<<num<<" modes"<<endl;
	cout<<"Modes were:";
	for(int i = 0; i<num; i++)
	{
		cout<<" "<<modeslist[i];
	}
	cout<<endl;
	return rc;
}

#endif