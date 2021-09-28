#include <iostream>
#include <string>
#include <cmath>
using namespace std;

bool judge(int, int);

int main()
{
	int choice, number;bool result;
	do
	{
		cout<<"Please enter the test choice: "<<endl;
		cin>>choice;
	}
	while(choice<0 ||choice >4);

	do
	{
		cout<<"Please enter the number for test: "<<endl;
		cin>>number;
	}
	while (number<0 || number >100000000);
		result=judge(choice, number); //judge is the major function
	if(result==true)
	{	
		cout<<"Pass"<<endl;
	}
	else
	{
		cout<<"Fail"<<endl;
	}
	return 0;
}


bool judge(int choice, int number)
{
	bool result=false; //set the initial state as false. If it pass the test, turn to true
	switch (choice)
	{
		case 1:
			{
				int a=0; int b=1;int c;
				if(number==a || number==b) // if the number is 0 or 1
				{
					result=true;
				}
				else
				{
					for (int i=1;b<number;i++) // add up to the fibonacci number is no less than the tested number
					{
						c=b;
						b+=a;
						a=c;
			
						if (b==number) 
						{
							result=true;
							break;
						}
					}
				}
				return result;
				break;
			}

		case 2:
			{
				int m;int a ;
				for (m=0;m*m<number;m++) //quadratic sum start from m^2
				a=0;
				{
					for(int n=0;a<number;n++)
					{
						a=a+(m+n)*(m+n);
						if (a==number)
						{
							result=true;
							break;
						}
					}
				}
				return result;
				break;
			}

		case 3:
			{
				char number_ss[20];
				int n,m,j;int _number=number;

				for (n=1;number/pow(10,n)>=1;n++){} //find the digit (n) of the tested number
		
				for (m=n;m>=1;m--)
				{
					number_ss[n-m]=floor(_number/pow(10,m-1));
					_number=_number-floor(_number/pow(10,m-1))*pow(10,m-1);
				}
				//number_ss now is the string that stores every digit of the number
				
				for (int i=1;i<=n/2;i++)
				{
					if (n%i==0)// i is the length of the repeated part
					{
						for (j=0;j<n;j++)
						{
							if (number_ss[j]!=number_ss[(j)%i])
							{
								break;
							}
						}
						if (j==n) //if the exam goes to the last digit and passes
						{
							result=true;
							break;
						}
					}
				}
				return result;  
				break;
			}

		case 4:
			{
				int sum=0;
				for(int i=1;i<number;i++)
				{
					if (number%i==0) //plus all the divisor
					{
					sum+=i;
					}
				}
				if (sum==number)
				{
					result = true;
				}
				return result;
				break; 
			}
	}
}
