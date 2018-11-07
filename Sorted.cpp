#include <iostream>
#include <math.h>
#include <stdlib.h>

using namespace std;

int compare(const char str1[], const char str2[])
{
	int k = 0;
	int l = 1;
	
	while(str2[k])
	{
		l = str2[k];
		if((l<'a' || l>'z') && (l<'A' || l>'Z') && (l != ' ') && (l != '\'') && (l != '-'))
		{
			return -2;
		}
		k++;
	}
	int i = 0;
	int j = 0;
	
	int rc = 0;
	int loop = 1;
	
	int nameOne = 0;
	int nameTwo = 0;
	
	while(loop)
	{
		nameOne = str1[i];
		nameTwo = str2[j];
		
		if(nameOne >= 'A' && nameOne <= 'Z')
		{
			nameOne = nameOne + ('a'-'A');
		}
		if(nameTwo >= 'A' && nameTwo <= 'Z')
		{
			nameTwo = nameTwo + ('a'-'A');
		}
		
		if(nameOne == 0 && nameTwo == 0)
		{
			loop = 0;
		}
		else if(nameOne == 0)
		{
			rc = -1;
			loop = 0;
		}
		else if(nameTwo == 0)
		{
			rc = 1;
			loop = 0;
		}
		else if(nameOne == '-' || nameOne == ' ' || nameOne == '\'')
		{
			j--;
		}
		else if(nameTwo == '-' || nameTwo == ' ' || nameTwo == '\'')
		{
			i--;
		}
		else if((nameOne >= 'a' && nameOne <= 'z') && (nameTwo >= 'a' && nameTwo <= 'z'))
		{
			if(nameOne < nameTwo)
			{
				rc = -1;
				loop = 0;
			}
			else if(nameOne > nameTwo)
			{
				rc = 1;
				loop = 0;
			}
			else if(nameOne == nameTwo)
			{
				rc = 0;
			}
		}
		
		i++;
		j++;
	}
	
	if(!rc)
	{
		i = 0;
		j = 0;
		int loop = 1;
		int nameOne = 0;
		int nameTwo = 0;
		
		while(loop)
		{
			nameOne = str1[i];
			nameTwo = str2[j];
			
			if(nameOne == 0 || nameTwo == 0)
			{
				break;
			}
			
			if(nameOne == ' ')
			{
				if(nameTwo != ' ')
				{
					rc = -1;
					loop = 0;
				}
			}
			else if(nameOne == '-')
			{
				if(nameTwo == ' ')
				{
					rc = 1;
					loop = 0;
				}
				else if(nameTwo != '-')
				{
					rc = -1;
					loop = 0;
				}
			}
			else if(nameOne == '\'')
			{
				if(nameTwo == ' ' || nameTwo == '-')
				{
					rc = 1;
					loop = 0;
				}
				else if(nameTwo != '\'')
				{
					rc = -1;
					loop = 0;
				}
			}
			else
			{
				if(nameTwo == ' ' || nameTwo == '-' || nameTwo == '\'')
				{
					rc = 1;
					loop = 0;
				}
			}
			i++;
			j++;
		}
	}
	
	if(!rc)
	{
		i = 0;
		j = 0;
		int loop = 1;
		int nameOne = 0;
		int nameTwo = 0;
		
		while(loop)
		{
			nameOne = str1[i];
			nameTwo = str2[j];
			
			if(nameOne == 0 || nameTwo == 0)
			{
				break;
			}
			
			if(nameOne<nameTwo)
			{
				rc = 1;
				loop = 0;
			}
			else if(nameOne>nameTwo)
			{
				rc = -1;
				loop = 0;
			}
			i++;
			j++;
		}
	}
	
	return rc;
}
int isSorted(const char*const names[])
{
	enum sortType {START, ASCENDING, DESCENDING, UNKNOWN, UNSORTED, DONE};
	sortType s = START;
	
	int i = 1;
	int rc = 0;
	
	if(names[0] == 0)
	{
		return 0;
	}
	
	while(s!=DONE)
	{
		const char *current = names[i];
		const char *previous = names[i-1];
		
		switch(s)
		{
			case START:
				if(current == 0)
				{
					s = DONE;
				}
				else if(compare(previous, current) == -1)
				{
					s = ASCENDING;
				}
				else if(compare(previous, current) == 1)
				{
					s = DESCENDING;
				}
				else if(compare(previous, current) == 0)
				{
					s = UNKNOWN;
				}
				else
				{
					return -1;
				}
				break;
			
			case UNKNOWN:
				if(current == 0)
				{
					s = DONE;
				}
				else if(compare(previous, current) == -1)
				{
					s = ASCENDING;
				}
				else if(compare(previous, current) == 1)
				{
					s = UNSORTED;
				}
				else if(compare(previous, current) == 0)
				{
					s = UNKNOWN;
				}
				else
				{
					return -1;
				}
				break;
			
			case ASCENDING:
				if(current == 0)
				{
					s = DONE;
				}
				else if(compare(previous, current) == -1)
				{
					s = ASCENDING;
				}
				else if(compare(previous, current) == 1)
				{
					s = UNSORTED;
				}
				else if(compare(previous, current) == 0)
				{
					s = ASCENDING;
				}
				else
				{
					return -1;
				}
				break;
			
			case DESCENDING:
				if(current == 0)
				{
					s = DONE;
				}
				else if(compare(previous, current) == -1)
				{
					s = UNSORTED;
				}
				else if(compare(previous, current) == 1)
				{
					s = DESCENDING;
				}
				else if(compare(previous, current) == 0)
				{
					s = DESCENDING;
				}
				else
				{
					return -1;
				}
				break;
			
			case UNSORTED:
				s = DONE;
				break;
			
			case DONE:
				break;
			
			default:
				break;
		}
		
		switch(s)
		{
			case START:
				break;
			
			case UNKNOWN:
				i++;
				break;
			
			case ASCENDING:
				i++;
				break;
				
			case DESCENDING:
				i++;
				break;
			
			case UNSORTED:
				rc = i+1;
				break;
			
			case DONE:
				break;
			
			default:
				break;
		}
	}
	
	return rc;
}

#ifndef MARMOSET_TESTING
int main()
{
	const char* const words[] = {"Chen", "Chen", "Cheng", "Cheng-Jones", "ChengJones", "Cheung", "O'Leary", "OLeary", "Smith", 0};
	
	cout<<isSorted(words)<<endl;
	
	return 0;
}
#endif