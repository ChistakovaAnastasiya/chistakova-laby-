#include <iostream>
#include <math.h>
using namespace std;

int main(int argc, char** argv) {
	int a, b;
	long int X;
	cout<<"Enter a, b: ";
	cin>>a>>b;
	
	if (a > b) 
		if (a!= 0) {
			X = (b-9)/a;
			cout<<"Result: "<< X;
		}
		else cout<<"ERROR: "<< endl;
	if ( a == b){
		X = -b;
		cout<<"Result: "<< X;
	}
	if (a < b) 
	 if(a!= 0){
		X = a*b+5/a;
		cout<<"Result: "<< X;
	}
		else cout<<"ERROR: "<< endl;
	
	
	return 0;
}
