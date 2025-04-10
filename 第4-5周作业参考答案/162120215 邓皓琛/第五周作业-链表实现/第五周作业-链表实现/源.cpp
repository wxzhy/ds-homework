//===========================================================================
//		学号：162120215
//		姓名：邓皓琛
//		数据结构-第5周作业-数组实现
//		时间：2022/9/30
//============================================================================

/*
	注意：本程序为便于测试，将data与data2合并后的数据输出至文件“data_output.txt”
	中，请注意查看
*/

#include<iostream>
#include<fstream>

using namespace std;

struct Node {
	int data;
	struct Node* next;
};

struct Node* InitNode();					//初始化链表data
struct Node* InitNode2();					//初始化链表data2
void Print(Node*);							//输出链表内容
void InsertElem(Node*);						//在链表第二位置插入元素
void NodeCat(Node*,Node*);					//链接两链表
void DelElem(Node*);						//删除重复元素
void Output(Node*);							//将链表数据输出至“data_output.txt”
void DelNode(Node*);

int main() {

	struct Node* head = InitNode();
	cout << "      data数据：";
	Print(head);

	InsertElem(head);
	cout << "    插入元素后：";
	Print(head);

	struct Node* head2 = InitNode2();
	cout << "     data2数据：";
	Print(head2);

	NodeCat(head,head2);
	cout << "  链接两链表后：";
	Print(head);

	DelElem(head);
	cout << "删除重复元素后：";
	Print(head);

	Output(head);
	DelNode(head);
	return 0;
}

struct Node* InitNode() {
	/*打开data.txt文件*/
	ifstream InputFile;
	InputFile.open("data.txt", ios::in);
	if (!InputFile) {
		cout << "Error!" << endl;
		exit(0);
	}
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

	InputFile.close();
	return head;
}

void Print(Node* p) {
	while (p != NULL) {
		cout << p->data << ' ';
		p = p->next;
	}
	cout << endl;
}

void InsertElem(Node* head) {
	struct Node* p;
	p = new struct Node;
	p->data = 3456;
	p->next = head->next;
	head->next = p;
}

struct Node* InitNode2() {
	/*打开data.txt文件*/
	ifstream InputFile;
	InputFile.open("data2.txt", ios::in);
	if (!InputFile) {
		cout << "Error!" << endl;
		exit(0);
	}
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

	InputFile.close();
	return head;
}

void NodeCat(Node* head1, Node* head2) {
	struct Node* p;
	p = head1;
	while (p->next != NULL) {
		p = p->next;
	}
	p->next = head2;
}

void DelElem(Node* head) {
	struct Node* cur, * t, * p;
	p = head;
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
			t->next = p->next;
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
}

void Output(Node* head) {
	ofstream OutputFile;
	OutputFile.open("data_output.txt", ios::out);
	while (head->next != NULL) {
		OutputFile << head->data;
		OutputFile << '\n';
		head = head->next;
	}
	OutputFile << head->data;

	cout << endl << "写入文件成功！" << endl;

	OutputFile.close();
}

void DelNode(Node* head) {
	struct Node* p;
	while (head != NULL) {
		p = head;
		head = head->next;
		delete p;
	}
	cout << "已释放链表空间！" << endl;
}