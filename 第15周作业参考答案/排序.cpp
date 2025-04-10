#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
using namespace std;

void bubblesort(int n, int num[]) { //ð������
	ofstream bubble;
	bubble.open("bubblesort.txt", ios::out);
	if (!bubble) {
		cout << "error";
		return ;
	}
	for (int i = 1; i <= n - 1; i++) {
		for (int j = 1; j <= n - i; j++) {
			if (num[j] > num[j + 1]) //������������
				swap(num[j], num[j + 1]); //���н���
		}
	}
	for (int i = 1; i <= n; i++)
		bubble << num[i] << endl;
	bubble.close();
}

void selectionsort(int n, int num[]) {
	ofstream selection;
	selection.open("selectionsort.txt", ios::out);
	if (!selection) {
		cout << "error";
		return ;
	}
	for (int i = 1; i <= n - 1; i++) {
		int minn = 2147483647, minwz = 1;
		for (int j = i; j <= n; j++) {
			if (num[j] < minn) {
				minn = num[j]; //ѡ��ʣ��Ԫ������С��
				minwz = j;
			}

		}
		swap(num[minwz], num[i]); //���i�����н���
	}
	for (int i = 1; i <= n; i++)
		selection << num[i] << endl;
	selection.close();
}

void insertsort(int n, int num[]) {
	ofstream insert;
	insert.open("insertsort.txt", ios::out);
	if (!insert) {
		cout << "error";
		return ;
	}
	int i = 1;
	for (int i = 2; i <= n; i++) {
		if (num[i - 1] > num[i]) { //������������˵����i����Ҫ����ǰ��������������
			int end = i - 1, j;
			int temp = num[i];
			for (j = end; j >= 0; j--) {
				if (temp < num[j]) {
					num[j + 1] = num[j]; //�𽥺���
					continue;
				} else
					break;
			}
			num[j + 1] = temp; //����
		}
	}
	for (int i = 1; i <= n; i++)
		insert << num[i] << endl;
	insert.close();
}

void shell(int n, int num[], int gap) { //��d=gap��ʱ�����ֱ�Ӳ�������
	for (int i = gap; i <= n; i++) { //���������еĲ�������
		int temp = num[i];
		int end = i - gap, j;
		for (j = end; j >= 1; j -= gap) {
			if (temp < num[j]) {
				num[j + gap] = num[j];
				continue;
			} else
				break;
		}
		num[j + gap] = temp;
	}
}

void shellsort(int n, int num[]) { //ϣ������
	ofstream shellf;
	shellf.open("shellsort.txt", ios::out);
	if (!shellf) {
		cout << "error";
		return ;
	}
	int gap = n;
	while (gap > 1) {
		gap /= 2; //ÿ��gap������2
		if (gap == 1) {
			bubblesort(n, num); //���һ�ν���ð������
			break;
		}
		shell(n, num, gap);
	}
	for (int i = 1; i <= n; i++)
		shellf << num[i] << endl;
	shellf.close();
}

int main() {
	ifstream input;
	input.open("a.txt");
	if (!input) {
		cout << "��a.txtʧ��!" << endl;
		exit(1);
	}
	int num[100010], temp;
	int n = 0;
	while (input >> temp) { //����Ԫ��
		n++;
		num[n] = temp;
	}
	insertsort(n, num); //��������
	selectionsort(n, num); //ѡ������
	bubblesort(n, num); //ð������
	shellsort(n, num); //ϣ������
	input.close();
	return 0;
}
