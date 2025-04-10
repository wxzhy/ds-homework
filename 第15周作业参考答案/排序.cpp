#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
using namespace std;

void bubblesort(int n, int num[]) { //冒泡排序
	ofstream bubble;
	bubble.open("bubblesort.txt", ios::out);
	if (!bubble) {
		cout << "error";
		return ;
	}
	for (int i = 1; i <= n - 1; i++) {
		for (int j = 1; j <= n - i; j++) {
			if (num[j] > num[j + 1]) //如果不满足大于
				swap(num[j], num[j + 1]); //进行交换
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
				minn = num[j]; //选择剩下元素中最小的
				minwz = j;
			}

		}
		swap(num[minwz], num[i]); //与第i个进行交换
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
		if (num[i - 1] > num[i]) { //如果是逆序对则说明第i个需要插入前面已有序序列中
			int end = i - 1, j;
			int temp = num[i];
			for (j = end; j >= 0; j--) {
				if (temp < num[j]) {
					num[j + 1] = num[j]; //逐渐后移
					continue;
				} else
					break;
			}
			num[j + 1] = temp; //插入
		}
	}
	for (int i = 1; i <= n; i++)
		insert << num[i] << endl;
	insert.close();
}

void shell(int n, int num[], int gap) { //在d=gap的时候进行直接插入排序
	for (int i = gap; i <= n; i++) { //类似上文中的插入排序
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

void shellsort(int n, int num[]) { //希尔排序
	ofstream shellf;
	shellf.open("shellsort.txt", ios::out);
	if (!shellf) {
		cout << "error";
		return ;
	}
	int gap = n;
	while (gap > 1) {
		gap /= 2; //每次gap都除以2
		if (gap == 1) {
			bubblesort(n, num); //最后一次进行冒泡排序
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
		cout << "打开a.txt失败!" << endl;
		exit(1);
	}
	int num[100010], temp;
	int n = 0;
	while (input >> temp) { //输入元素
		n++;
		num[n] = temp;
	}
	insertsort(n, num); //插入排序
	selectionsort(n, num); //选择排序
	bubblesort(n, num); //冒泡排序
	shellsort(n, num); //希尔排序
	input.close();
	return 0;
}
