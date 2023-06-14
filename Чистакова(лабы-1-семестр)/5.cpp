#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int main(){
	int x=INT_MIN,n,count;
	cout<<"Enter number your numbers\n";
	cin>>n;
	for(int i = 1;i<=n;i++){
		int lastX=x;
		cin>>x;
		if(x<lastX){
			cout<<i<<endl;
			count++;
		}
	}
	cout << "Result Count is equal "<< count;
}
