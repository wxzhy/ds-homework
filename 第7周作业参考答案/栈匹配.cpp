#include <iostream>
#include <fstream>
using namespace std;

#define MAXSTACKCOUNTER 128
//请同学们定义一个struct或者class 叫Stack， 然后通过函数Push和Pop完成进栈和出栈操作 

void PrintStack(char stack[], int top)
{
	while(top >= 0){
		cout<<stack[top];
		top--; 
	}
}
int main()
{
	fstream dataFile;
	dataFile.open("data.txt", ios::in);
	if(!dataFile){
		cout<<"File open error!"<<endl;
		exit(0);
	}
	char data; 
	int square_bracket_no = 0;
	int parentheses_no = 0;
	int brace_no = 0;
	char Stack[MAXSTACKCOUNTER];
	int top = 0;
	while(dataFile.eof() == false){
		dataFile>>data;
		if(isalpha(data)) continue;
		//cout<<data<<endl;
		if(data == '(' ||  data == '{' ||  data == '['){
			Stack[top] = data;
			top++;			
			if(top == MAXSTACKCOUNTER){
				cout<<"stack overflow"<<endl;
				break; 
			}
		}
		if(data == ')'){
			if(Stack[top - 1] == '('){
				top--;
				parentheses_no++;
			}else{
				Stack[top] = data;
				top++;
			}	
		}
		if(data == ']'){
			if(Stack[top - 1] == '['){
				top--;
				square_bracket_no++;
			}else{
				Stack[top] = data;
				top++;
			}
		}
		if(data == '}'){
			if(Stack[top - 1] == '{'){
				top--;
				brace_no++;
			}else{
				Stack[top] = data;
				top++;
			}
		}
	}
	cout<<"():"<<parentheses_no<<" []:"<<square_bracket_no<<" {}: "<<brace_no<<endl;
	PrintStack(Stack, top - 1);
	dataFile.close();
	return 0;
	
}
