//===========================================================================
//		ѧ�ţ�162120215
//		����������
//		���ݽṹ-��5����ҵ-����ʵ��
//		ʱ�䣺2022/9/28
//============================================================================

/*
	ע�⣺������Ϊ���ڲ��ԣ���data��data2�ϲ��������������ļ���data_output.txt��
	�У���ע��鿴
*/

#include<iostream>
#include<fstream>
#include<stdlib.h>

using namespace std;

int* InitArray(int);						//��ʼ������
int getlen();								//��ȡdata�����ݵĸ���
int* InsArray(int*,int&);					//������ĵڶ���λ�ò���3456
void Print(int*,int);						//�������
int getlen_2();								//��ȡdata2�����ݵĸ���
int* InitArray_2(int);						//��ʼ������data2
int* ArrayCat(int*,int*,int,int);			//������������
int* DelElem(int*,int&);					//ɾ�������е��ظ�Ԫ��
void Output(int*, int);						//�������е�Ԫ��������ļ�

int main() {
	
	int cnt = getlen();
	int* pArray = InitArray(cnt);
	cout << "     dataԭʼ���ݣ�";
	Print(pArray,cnt);

	pArray=InsArray(pArray,cnt);
	cout << " ����3456���data��";
	Print(pArray, cnt);

	int cnt2 = getlen_2();
	int* pArray2 = InitArray_2(cnt2);
	cout << "      data2�����ݣ�";
	Print(pArray2, cnt2);

	int *pArray_Cat = ArrayCat(pArray, pArray2, cnt, cnt2);
	int cnt_sum = cnt + cnt2;
	cout << "           �ϲ���";
	Print(pArray_Cat, cnt_sum);

	int* pArray_Del = DelElem(pArray_Cat, cnt_sum);
	cout << " �ϲ�ɾ���ظ�Ԫ�أ�";
	Print(pArray_Del, cnt_sum);

	Output(pArray_Del, cnt_sum);

	delete[]pArray;
	delete[]pArray2;
	delete[]pArray_Cat;
	delete[]pArray_Del;
	return 0;
}

int* InitArray(int cnt) {
	ifstream InputFile;
	InputFile.open("data.txt", ios::in);
	if (!InputFile) {
		cout << "Error!" << endl;
		exit(0);
	}

	int* pArray = new int[cnt];
	// pArray ˳����������
	for (int i = 0; i < cnt; i++) {
		InputFile >> pArray[i];
	}
	InputFile.close();
	return pArray;
}

int getlen() {
	/*��data.txt�ļ�*/
	ifstream InputFile;
	InputFile.open("data.txt", ios::in);
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
	InputFile.close();
	return cnt;
}

int* InsArray(int* p,int &n) {
	int* ans = new int[n + 1];
	ans[0] = p[0];
	ans[1] = 3456;
	for (int i = 1; i < n ; i++) {
		ans[i + 1] = p[i];
	}
	n++;
	return ans;
}

void Print(int* p, int n) {
	for (int i = 0; i < n; i++) {
		cout << p[i] << ' ';
	}
	cout << endl;
}

int getlen_2() {
	/*��data.txt�ļ�*/
	ifstream InputFile;
	InputFile.open("data2.txt", ios::in);
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
	InputFile.close();
	return cnt;
}

int* InitArray_2(int cnt) {
	ifstream InputFile;
	InputFile.open("data2.txt", ios::in);
	if (!InputFile) {
		cout << "Error!" << endl;
		exit(0);
	}

	int* pArray = new int[cnt];
	// pArray ˳����������
	for (int i = 0; i < cnt; i++) {
		InputFile >> pArray[i];
	}
	InputFile.close();
	return pArray;
}

int* ArrayCat(int* p1, int* p2, int n1, int n2) {
	int* p = new int[n1 + n2];
	for (int i = 0; i < n1; i++) {
		p[i] = p1[i];
	}
	for (int i = n1; i < n1 + n2; i++) {
		p[i] = p2[i - n1];
	}
	return p;
}

int* DelElem(int* pArray, int &cnt) {
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
	cnt = cnt_Del;
	delete[]pArray_tmp;		//�ͷ���ʱ����
	return pArray_Del;
}

void Output(int* p, int n) {
	ofstream OutputFile;
	OutputFile.open("data_output.txt", ios::out);
	for (int i = 0; i < n-1; i++) {
		OutputFile << p[i];
		OutputFile << "\n";
	}
	OutputFile << p[n - 1];

	cout << endl << "д���ļ��ɹ���" << endl;

	OutputFile.close();
}