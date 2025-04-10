#include <iostream>
#include <fstream>
using namespace std;

#define MAXSTACKCOUNTER 20
void PrintStack(int stack[], int top)
{
	while(top >= 0){
		cout<<stack[top];
		top--; 
	}
}
int main()
{
	int stack[MAXSTACKCOUNTER];
	int top = 0;
//	int val = 23;
	int val = 28;
	while(val > 0){
		int v = val % 2;
		val = val / 2;
//		cout<<"v: "<<v<<endl; 
		stack[top] = v;
		top++;
	}
	PrintStack(stack, top - 1);
	return 0;
}
