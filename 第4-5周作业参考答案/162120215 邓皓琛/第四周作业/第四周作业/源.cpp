//===========================================================================
//		学号：162120215
//		姓名：邓皓琛
//		数据结构-第4周作业
//		时间：2022/9/23
//============================================================================

#include<iostream>
#include<fstream>
using namespace std;

struct Node {
	int data;
	struct Node* next;
};

int main() {

	/*打开data.txt文件*/
	ifstream InputFile;
	InputFile.open("data.txt",ios::in);
	if (!InputFile) {
		cout << "Error!" << endl;
		exit(0);
	}
	int cnt = 0;		//存储数组长度
	int tmp;
	while (!InputFile.eof()) {
		InputFile >> tmp;
		cnt++;
	}


	/*将文件中的数据存储至数组*/
	InputFile.seekg(0, ios::beg);
	int* pArray = new int[cnt];
	// pArray 顺序完整数组
	for (int i = 0; i < cnt; i++) {
		InputFile >> pArray[i];
	}


	/*顺序输出数组*/
	cout << "数组顺序输出：";
	for (int i = 0; i < cnt; i++) {
		cout << pArray[i] << ' ';
	}
	cout << endl;


	/*倒序输出数组*/
	cout << "数组倒序输出：";
	for (int i = cnt - 1; i >= 0; i--) {
		cout << pArray[i] << ' ';
	}
	cout << endl;


	/*将数据存储至链表(head为头指针)*/
	InputFile.seekg(0, ios::beg);
	struct Node* head, * p1, * p2;
	// head 顺序完整链表，p1，p2 为创建链表使用的临时变量
	head = NULL;
	p1 = NULL;
	p2 = NULL;

	while (!InputFile.eof()) {
		p1 = new struct Node;
		InputFile >> p1->data;
		if (head == NULL) {
			head = p1;
		}
		else {
			p2->next = p1;
		}
		p2 = p1;
	}
	if (head != NULL) {
		p2->next = NULL;
	}


	/*顺序输出链表*/
	struct Node* p;
	p = head;
	cout << "链表顺序输出：";
	while (p != NULL) {
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;


	/*逆置链表(head_D为头指针)*/
	struct Node* head_D, * p3, * p4;
	p = head;
	p3 = NULL;
	p4 = NULL;

	while (p != NULL) {
		p3 = new struct Node;
		p3->data = p->data;
		if (p3->next == NULL) {
			continue;
		}
		else {
			p3->next = p4;
		}
		p4 = p3;
		p = p->next;
	}
	head_D = p4;
	// head_D 为逆置后的完整链表

	/*输出逆置后的链表*/
	p = head_D;
	cout << "链表倒序输出：";
	while (p != NULL) {
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;


	/*计算删除重复元素后数组的长度*/
	int* pArray_tmp = new int[cnt];
	int cnt_Del = 0;	//删除重复元素后的数组长度
	for (int i = 0; i < cnt; i++) {
		int flag = 0;
		for (int j = 0; j < cnt_Del; j++) {
			if (pArray[i] == pArray_tmp[j]) {
				flag = 1;
			}
		}
		if (flag == 0) {
			pArray_tmp[cnt_Del] = pArray[i];
			cnt_Del++;
		}
	}


	/*获得删除相同元素后的数组*/
	int* pArray_Del = new int[cnt_Del];
	for (int i = 0; i < cnt_Del; i++) {
		pArray_Del[i] = pArray_tmp[i];
	}
	delete[]pArray_tmp;		//释放临时数组


	/*输出删除元素后的数组*/
	cout << "删除重复元素(数组)：";
	for (int i = 0; i < cnt_Del; i++) {
		cout << pArray_Del[i] << " ";
	}
	cout << endl;


	/*删除链表中的重复元素*/
	p = head;
	struct Node* cur, * t;
	cur = NULL;
	t = p;
	while (p != NULL) {
		int flag = 0;
		cur = head;
		while (cur != p) {
			if (cur->data == p->data) {
				flag = 1;
				break;
			}
			cur = cur->next;
		}
		
		if (flag == 1) {
			t->next=p->next;
			struct Node* tmp;
			tmp = p;
			p = p->next;
			delete tmp;
		}
		else {
			t = p;
			p = p->next;
		}
	}

	/*输出删除重复元素后的链表*/
	cout << "删除重复元素(链表)：";
	p = head;
	while (p != NULL) {
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;

	/*释放链表与数组，关闭文件*/
	while (head != NULL) {
		p = head;
		head = head->next;
		delete p;
	}
	while (head_D != NULL) {
		p = head_D;
		head_D = head_D->next;
		delete p;
	}
	delete[]pArray;
	delete[]pArray_Del;
	InputFile.close();
	return 0;
}