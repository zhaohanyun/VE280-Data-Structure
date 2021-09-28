#include <iostream>
using namespace std;
int main() {
    int m; int a;int number;int result=0;
    cout<<"Please input a number: "<<endl;
    cin>>number;
    for (m=0;m*m<=number;m++)
    {
        a=0;
        for (int n=0;a<=number;n++)
        {
            a=a+(m+n)*(m+n) ;
            if (a==number)
            {
                result=1;
                break;
            }
        }
    }
    cout<< result <<endl;
    return 0;
}