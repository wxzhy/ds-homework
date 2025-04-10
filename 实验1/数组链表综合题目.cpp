#include <iostream>
#include <fstream>
#include <time.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h> /* srand, rand */
using namespace std;

#define LIST_SIZE_INC 500

void PrintList(int *ptr_head, int count) {

	for (int i = 0; i < count; i++) {
		cout << ptr_head[i] << " ";
	}
	cout << endl;
}
struct ValNode {
	int val;
	ValNode *next;
	ValNode() : next(NULL) {
	}
	ValNode(int in, ValNode *ptr) : val(in), next(ptr) {
	}
};

/*
traverse the list to print the elements
遍历链表输出元素

*/
void PrintList(ValNode *head) {
	ValNode *cur = head->next;
	while (cur != NULL) {
		cout << cur->val << " ";
		cur = cur->next;
	}
	cout << endl;
}
/*
释放所在空间

*/
void FreeList(ValNode *head) {
	ValNode *cur = head->next;
	while (cur != NULL) {
		delete head;
		head = cur;
		cur = head->next;
	}
}

void InsertElement(ValNode *head, int elem) {
	ValNode *p = new ValNode;
	p->val = elem;
	p->next = head->next;
	head->next = p;
}
void CountList(ValNode *head, int max_value, int threshold) {
	int *intarray = new int[max_value + 1];
	for(int i=0; i<=100; ++i)
		intarray[i]=0;
	for (head = head->next; head != nullptr; head = head->next)
		intarray[head->val]++;
    cout<<"value"<<'\t'<<"count"<<endl;
	for (int i = 0; i <= 100; ++i)
		if (intarray[i] > threshold)
			cout << i << '\t' << intarray[i] << endl;
}
bool Contain(ValNode *head, int val) {
	for (head = head->next; head != nullptr; head = head->next)
		if (head->val == val)
			return true;
	return false;
}
void OutPutList(ValNode *head, int max_value, int threshold, ValNode *head2) {
	int *intarray = new int[max_value + 1];
//	memset(intarray, 0, max_value + 1);
	for (int i=0; i<=100; ++i)
		intarray[i]=0;
	for (head = head->next; head != nullptr; head = head->next)
		intarray[head->val]++;
	for (int i = 0; i <= 100; ++i)
		if (intarray[i] > threshold) {
			ValNode *p = new ValNode;
			p->val = i;
			p->next = head2->next;
			head2->next = p;
		}
	for (head2 = head2->next; head2 != nullptr; head2 = head2->next)
		cout << head2->val << ' ';
    cout<<endl;
}
int main() {

	srand(time(NULL));

	// time_t是long类型，精确到秒，是当前时间和1900年1月1日零点时间的差
	//    cout<<"current time is "<<t<<endl;
	/*本地时间：日期，时间 年月日，星期，时分秒*/
	const int INI_LIST_SIZE = 2000;
	int element_count = INI_LIST_SIZE; // testing the out of range
	int *ptr_list = new int[element_count];
	char filename[] = "data.txt";
	std::ofstream fileout(filename, ios::out);
	//  int max_value = 100000;
	int max_value = 100;
	for (int i = 0; i < element_count; i++) {
		ptr_list[i] = (rand() % max_value);
		fileout << ptr_list[i] << " ";
	}
	fileout << endl;

	PrintList(ptr_list, element_count);
	delete[] ptr_list;

	ValNode *head = new ValNode();
	ValNode *cur = head;

	cout << "read data from the file" << endl;
	std::ifstream filein(filename, ios::in);
	if (filein.is_open()) {

		while (filein.eof() == false) {
			int val;
			filein >> val;
			//			cout<<val<<" ";
			InsertElement(head, val);
		}
		//		cout<<endl;
	}
	//	PrintList(head);

	// count the number of elemenets for each value and print the top-10 result
	int threshold = 10;
	CountList(head, max_value, threshold);
	ValNode *head2 = new ValNode();
	OutPutList(head, max_value, threshold, head2);
	cout << "elements appearing more than 10: " << endl;
	PrintList(head2);
	FreeList(head);
	FreeList(head2);
	return 0;
}
