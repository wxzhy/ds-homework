//===========================================================================
//		ѧ�ţ�162120215
//		����������
//		���ݽṹ-��5����ҵ-����ʵ��
//		ʱ�䣺2022/9/30
//============================================================================

/*
	ע�⣺������Ϊ���ڲ��ԣ���data��data2�ϲ��������������ļ���data_output.txt��
	�У���ע��鿴
*/

#include<iostream>
#include<fstream>

using namespace std;

struct Node {
	int data;
	struct Node* next;
};

struct Node* InitNode();					//��ʼ������data
struct Node* InitNode2();					//��ʼ������data2
void Print(Node*);							//�����������
void InsertElem(Node*);						//������ڶ�λ�ò���Ԫ��
void NodeCat(Node*,Node*);					//����������
void DelElem(Node*);						//ɾ���ظ�Ԫ��
void Output(Node*);							//�����������������data_output.txt��
void DelNode(Node*);

int main() {

	struct Node* head = InitNode();
	cout << "      data���ݣ�";
	Print(head);

	InsertElem(head);
	cout << "    ����Ԫ�غ�";
	Print(head);

	struct Node* head2 = InitNode2();
	cout << "     data2���ݣ�";
	Print(head2);

	NodeCat(head,head2);
	cout << "  �����������";
	Print(head);

	DelElem(head);
	cout << "ɾ���ظ�Ԫ�غ�";
	Print(head);

	Output(head);
	DelNode(head);
	return 0;
}

struct Node* InitNode() {
	/*��data.txt�ļ�*/
	ifstream InputFile;
	InputFile.open("data.txt", ios::in);
	if (!InputFile) {
		cout << "Error!" << endl;
		exit(0);
	}
	struct Node* head, * p1, * p2;
	// head ˳����������p1��p2 Ϊ��������ʹ�õ���ʱ����
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
	/*��data.txt�ļ�*/
	ifstream InputFile;
	InputFile.open("data2.txt", ios::in);
	if (!InputFile) {
		cout << "Error!" << endl;
		exit(0);
	}
	struct Node* head, * p1, * p2;
	// head ˳����������p1��p2 Ϊ��������ʹ�õ���ʱ����
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

	cout << endl << "д���ļ��ɹ���" << endl;

	OutputFile.close();
}

void DelNode(Node* head) {
	struct Node* p;
	while (head != NULL) {
		p = head;
		head = head->next;
		delete p;
	}
	cout << "���ͷ�����ռ䣡" << endl;
}