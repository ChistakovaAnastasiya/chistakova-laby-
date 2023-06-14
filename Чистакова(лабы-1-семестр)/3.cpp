#include <iostream>
#include <math.h>
using namespace std;

double y(double x){
	if (-3 > x)
	 if (x*x-25 >=0) {
		return log(cbrt(x*x-25));
		 cout<<"Result: "<<y(x)  ;
	}
	  else cout<<"ERROR: "<< endl;
	if (-3 <= x)  
     if(x < 4)
	  if(sin(x) != 0)
	{
		return 1/tan(x*x-25);
         cout<<"Result: "<< y(x);	
	}
	  else cout<<"ERROR: "<< endl;
	if (4 <= x)
	 if (x*x-25 !=0)
	{
		return tan(1/(x*x-25));
		cout<<"Result: "<< y(x);
	}
	  else cout<<"ERROR: "<< endl;
}

int main(int argc, char** argv) {
	double x;
	cout<<"Enter x: ";
	cin>>x;
	cout<<"Result: "<<y(x);
	
	return 0;
}
