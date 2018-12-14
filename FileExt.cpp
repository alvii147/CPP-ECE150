#include <iostream>

using namespace std;

enum ExtensionType {NO_DOT, CSV_EXT, INVALID_EXT};

ExtensionType filenameType(char const filename[])
{
	enum STATE {START, GotLetter, GotDot, GotC, GotS, GotV, DoneWithExtension, DoneNoExtension};
	STATE s = START;
	
	int i = 0;
	while(s != DoneWithExtension && s != DoneNoExtension)
	{
		switch(s)
		{
			case START:
				if(filename[i] >= 'a' && filename[i] <= 'z')
				{
					s = GotLetter;
				}
				else
				{
					return INVALID_EXT;
				}
				break;
			
			case GotLetter:
				if(filename[i] == '.')
				{
					s = GotDot;
				}
				else if(filename[i] >= 'a' && filename[i] <= 'z')
				{
					s = GotLetter;
				}
				else if(filename[i] == 0)
				{
					s = DoneNoExtension;
					return NO_DOT;
				}
				else
				{
					return INVALID_EXT;
				}
				break;
			
			case GotDot:
				if(filename[i] == 'c')
				{
					s = GotC;
				}
				else
				{
					return INVALID_EXT;
				}
				break;
			
			case GotC:
				if(filename[i] == 's')
				{
					s = GotS;
				}
				else
				{
					return INVALID_EXT;
				}
				break;
			
			case GotS:
				if(filename[i] == 'v')
				{
					s = GotV;
				}
				else
				{
					return INVALID_EXT;
				}
				break;
			
			case GotV:
				if(filename[i] == 0)
				{
					s = DoneWithExtension;
					return CSV_EXT;
				}
				else
				{
					return INVALID_EXT;
				}
				break;
			
			case DoneWithExtension:
				break;
				
			case DoneNoExtension:
				break;
				
			default:
				break;
		}
		i++;
	}
	return INVALID_EXT;
}

#ifndef MARMOSET_TESTING

int main()
{
	return 0;
}

#endif