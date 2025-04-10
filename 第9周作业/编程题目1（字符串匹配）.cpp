#include<iostream>
#include<fstream>
#include<cstring>
#define MAX 100
using namespace std;
bool equal(char* word, char* pattern) { //判断单词是否相等
	//去除标点等特殊符号
	char c[MAX];
	int l1 = 0, l2 = strlen(pattern);
	for (word; *word != '\0'; ++word) {
		if (isalpha(*word)) {
			c[l1++] = *word;
		}
	}
	c[l1]='\0';
//	cout << c<<endl;
	if (l1 != l2)//长度不相等则为否
		return false;
	for (int i = 0; i < l1; ++i)
		if (c[i] != pattern[i])//如果任意字符不相等
			return false;
	return true;
}

int count(ifstream& in, char* pattern) {//计数对应单词个数
	char word[MAX];
	int count = 0;
	if (in.fail()) {
		cout<<"打开失败";
		exit(1);
	}
	while (!in.eof()) {
		in >> word;//通过空格分割
		if (equal(word, pattern))
			count++;
	}
	return count;
}
int main() {
	system("chcp 65001>nul");
	char pattern[MAX];
	cin >> pattern;
	ifstream in("text.txt");
	cout<<"text.txt中"<<pattern<<"出现的次数为："<<count(in, pattern)<<endl;
	in.close();
	in.open("text2.txt");
	cout<<"text2.txt中"<<pattern<<"出现的次数为："<<count(in, pattern)<<endl;
}