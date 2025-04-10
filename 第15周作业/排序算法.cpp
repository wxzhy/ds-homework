#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

void insertSort(vector<int> &v) {//插入排序
	for (int i = 1; i < v.size(); i++) {//从第二个元素开始
		int temp = v[i];//待插入元素
		int j = i - 1;//有序序列最后一个元素
		while (j >= 0 && v[j] > temp) {//从后向前遍历
			v[j + 1] = v[j];//向后移动
			j--;//向前移动
		}
		v[j + 1] = temp;//插入
	}
}

void bubbleSort(vector<int> &v) {//冒泡排序
	for (int i = 0; i < v.size() - 1; i++) {
		for (int j = 0; j < v.size() - i - 1; j++) {
			if (v[j] > v[j + 1]) {//相邻元素比较
				swap(v[j], v[j + 1]);//如果前者大于后者则交换
			}
		}
	}
}

void selectSort(vector<int> &v) {//简单选择排序
	for (int i = 0; i < v.size() - 1; i++) {
		int min = i;//最小值下标
		for (int j = i + 1; j < v.size(); j++) {
			if (v[j] < v[min]) {//找到最小值
				min = j;
			}
		}
		swap(v[i], v[min]);//交换
	}
}

void shellSort(vector<int> &v) {//希尔排序
	int d = v.size() / 2;//增量
	while (d > 0) {
		for (int i = d; i < v.size(); i++) {
			int temp = v[i];//待插入元素
			int j = i - d;//有序序列最后一个元素
			while (j >= 0 && v[j] > temp) {
				v[j + d] = v[j];//向后移动
				j -= d;//向前移动
			}
			v[j + d] = temp;//插入
		}
		d /= 2;
	}
}

int main() {
	system("chcp 65001>nul");//设置编码格式为utf-8(防止乱码)
	ifstream in("a.txt");
	if (in.fail()) {
		cout << "打开文件失败" << endl;
		exit(1);
	}
	vector<int> v;
	while (!in.eof()) {
		int temp;
		in >> temp;
		v.push_back(temp);
	}
	vector<int> a(v), b(v), c(v), d(v);
	insertSort(a);
	ofstream out("insertsort.txt");
	if (out.fail()) {
		cout << "打开文件失败" << endl;
		exit(1);
	}
	for (auto i: a) {
		out << i << " ";
	}
	cout << "insertsort.txt写入成功" << endl;
	out.close();
	bubbleSort(b);
	out.open("bubblesort.txt");
	if (out.fail()) {
		cout << "打开文件失败" << endl;
		exit(1);
	}
	for (auto i: b) {
		out << i << " ";
	}
	cout << "bubblesort.txt写入成功" << endl;
	out.close();
	selectSort(c);
	out.open("selectsort.txt");
	if (out.fail()) {
		cout << "打开文件失败" << endl;
		exit(1);
	}
	for (auto i: c) {
		out << i << " ";
	}
	out.close();
	shellSort(d);
	cout << "selectsort.txt写入成功" << endl;
	out.open("shellsort.txt");
	if (out.fail()) {
		cout << "打开文件失败" << endl;
		exit(1);
	}
	for (auto i: d) {
		out << i << " ";
	}
	cout << "shellsort.txt写入成功" << endl;
	out.close();
	return 0;
}