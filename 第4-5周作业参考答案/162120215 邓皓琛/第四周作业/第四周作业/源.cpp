//===========================================================================
//		ѧ�ţ�162120215
//		����������
//		���ݽṹ-��4����ҵ
//		ʱ�䣺2022/9/23
//============================================================================

#include<iostream>
#include<fstream>
using namespace std;

struct Node {
	int data;
	struct Node* next;
};

int main() {

	/*��data.txt�ļ�*/
	ifstream InputFile;
	InputFile.open("data.txt",ios::in);
	if (!InputFile) {
		cout << "Error!" << endl;
		exit(0);
	}
	int cnt = 0;		//�洢���鳤��
	int tmp;
	while (!InputFile.eof()) {
		InputFile >> tmp;
		cnt++;
	}


	/*���ļ��е����ݴ洢������*/
	InputFile.seekg(0, ios::beg);
	int* pArray = new int[cnt];
	// pArray ˳����������
	for (int i = 0; i < cnt; i++) {
		InputFile >> pArray[i];
	}


	/*˳���������*/
	cout << "����˳�������";
	for (int i = 0; i < cnt; i++) {
		cout << pArray[i] << ' ';
	}
	cout << endl;


	/*�����������*/
	cout << "���鵹�������";
	for (int i = cnt - 1; i >= 0; i--) {
		cout << pArray[i] << ' ';
	}
	cout << endl;


	/*�����ݴ洢������(headΪͷָ��)*/
	InputFile.seekg(0, ios::beg);
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


	/*˳���������*/
	struct Node* p;
	p = head;
	cout << "����˳�������";
	while (p != NULL) {
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;


	/*��������(head_DΪͷָ��)*/
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
	// head_D Ϊ���ú����������

	/*������ú������*/
	p = head_D;
	cout << "�����������";
	while (p != NULL) {
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;


	/*����ɾ���ظ�Ԫ�غ�����ĳ���*/
	int* pArray_tmp = new int[cnt];
	int cnt_Del = 0;	//ɾ���ظ�Ԫ�غ�����鳤��
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


	/*���ɾ����ͬԪ�غ������*/
	int* pArray_Del = new int[cnt_Del];
	for (int i = 0; i < cnt_Del; i++) {
		pArray_Del[i] = pArray_tmp[i];
	}
	delete[]pArray_tmp;		//�ͷ���ʱ����


	/*���ɾ��Ԫ�غ������*/
	cout << "ɾ���ظ�Ԫ��(����)��";
	for (int i = 0; i < cnt_Del; i++) {
		cout << pArray_Del[i] << " ";
	}
	cout << endl;


	/*ɾ�������е��ظ�Ԫ��*/
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

	/*���ɾ���ظ�Ԫ�غ������*/
	cout << "ɾ���ظ�Ԫ��(����)��";
	p = head;
	while (p != NULL) {
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;

	/*�ͷ����������飬�ر��ļ�*/
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