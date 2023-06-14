#include <iostream>
#include <math.h>
using namespace std;

long double fact(int N)
{
    if(N < 0) 
        return 0; 
    if (N == 0) 
        return 1; 
    else 
        return N * fact(N - 1); 
}

int main(int argc, char** argv) {
	int n, k = 0;
	float total = 0, x;
	cout<<"Enter n, x: ";
	cin>>n>>x;
	
	while (k <= n){
		total += (pow(-1, k) * pow(x, 2*k + 1)) /
		 (fact( 2*k + 1 ));
		k++;
	}
	
	cout<<"Result: "<<total;
	
	return 0;
}


