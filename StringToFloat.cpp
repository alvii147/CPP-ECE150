#include <iostream>
#include <math.h>

using namespace std;

float stringToFloat(const char input[])
{
	enum State {START, DIGIT_BEFORE_DECIMAL, DIGIT_AFTER_DECIMAL, SIGN, DECIMAL, POWER, POWER_SIGN, SCIENTIFIC, DONE};
	State s = START;
	int i = 0;
	int d = 1;
	int p = 1;
	int b = 0;
	int ps = 1;
	int in;
	float total = 0.0;
	
	while(s != DONE)
	{
		in = input[i];
		
		switch(s)
		{
			case START:
				if((in >= '0') && (in <= '9'))
				{
					s = DIGIT_BEFORE_DECIMAL;
				}
				else if((in == '+') || (in == '-'))
				{
					s = SIGN;
				}
				else if(in == '.')
				{
					s = DECIMAL;
				}
				else
				{
					return NAN;
				}
				break;
			
			case DIGIT_BEFORE_DECIMAL:
				if((in >= '0') && (in <= '9'))
				{
					s = DIGIT_BEFORE_DECIMAL;
				}
				else if(in == '.')
				{
					s = DECIMAL;
				}
				else if((in == 'e') || (in == 'E'))
				{
					s = POWER;
				}
				else if(in == 0)
				{
					s = DONE;
				}
				else
				{
					return NAN;
				}
				break;
			
			case SIGN:
				if((in >= '0') && (in <= '9'))
				{
					s = DIGIT_BEFORE_DECIMAL;
				}
				else if(in == '.')
				{
					s = DECIMAL;
				}
				else
				{
					return NAN;
				}
				break;
			
			case DECIMAL:
				if((in >= '0') && (in <= '9'))
				{
					s = DIGIT_AFTER_DECIMAL;
				}
				else
				{
					return NAN;
				}
				break;
			
			case DIGIT_AFTER_DECIMAL:
				if((in >= '0') && (in <= '9'))
				{
					s = DIGIT_AFTER_DECIMAL;
				}
				else if((in == 'e') || (in == 'E'))
				{
					s = POWER;
				}
				else if(in == 0)
				{
					s = DONE;
				}
				else
				{
					return NAN;
				}
				break;
			
			case POWER:
				if((in >= '0') && (in <= '9'))
				{
					s = SCIENTIFIC;
				}
				else if((in == '+') || (in == '-'))
				{
					s = POWER_SIGN;
				}
				else
				{
					return NAN;
				}
				break;
			
			case POWER_SIGN:
				if((in >= '0') && (in <= '9'))
				{
					s = SCIENTIFIC;
				}
				else
				{
					return NAN;
				}
				break;
			
			case SCIENTIFIC:
				if((in >= '0') && (in <= '9'))
				{
					s = SCIENTIFIC;
				}
				else if(in == 0)
				{
					s = DONE;
				}
				else
				{
					return NAN;
				}
				break;
			
			case DONE:
			default:
				break;
		}
		
		switch(s)
		{
			case DIGIT_BEFORE_DECIMAL:
				total = (total*10.0)+(float)(in-48);
				i++;
				break;
			
			case SIGN:
				if(in == '-')
				{
					p = -1;
				}
				i++;
				break;
			
			case DIGIT_AFTER_DECIMAL:
				total = total+(((float)(in-48))/(pow(10, d)));
				d++;
				i++;
				break;
			
			case SCIENTIFIC:
				b = (b*10)+(int)(in-48);
				if(b>=38)
				{
					return INFINITY;
				}
				i++;
				break;
			
			case POWER_SIGN:
				if(in == '-')
				{
					ps = -1;
				}
				i++;
				break;
			
			case DONE:
				total = total*p*pow(10, b*ps);
				break;
			
			case START:
				i++;
				break;
			
			case DECIMAL:
				i++;
				break;
			
			case POWER:
				i++;
				break;
			
			default:
				break;
		}
	}
	return total;
}

#ifndef MARMOSET_TESTING

int main()
{
	char array[200] = "37.56e+";
	float x = stringToFloat(array);
	cout<<x<<endl;
	return 0;
}

#endif