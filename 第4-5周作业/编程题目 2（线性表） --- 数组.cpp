#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
int main() {
//	system("chcp 65001>nul");
	//遍历一遍文件得到数据的个数
	ifstream in("data2.txt");
	int l = 0, d; //data2数据个数
	if (in.fail()) {
		cout << "打开失败！";
		exit(1);
	}
	while (!in.eof()) {
		in >> d;
		l++;
	}
	in.seekg(0, ios::beg);
//    读取文件里的数值并用数组存储
	int *arr = new int[l];
	for (int i = 0; i < l; ++i)
		in >> arr[i];
	in.close();
	cout << "原数组：" << endl << arr[0];
	for (int i = 1; i < l; ++i)
		cout << "->" << arr[i];
	int *arr2 = new int[++l]; //创建新数组
	if (arr == nullptr)
		exit(1);
	memcpy(arr2, arr, sizeof(int)); //将原数组第一个数值复制到新数组
	arr2[1] = 3456; //在新数组第 2 个位置插入数值 3456
	memcpy(arr2 + 2, arr + 1, sizeof(int) * (l - 2)); //将原数组第 3 个数值开始的数值复制到新数组
	delete[] arr;//释放原数组内存
	arr = arr2;
//输出插入后的数组
	cout << endl << "插入元素后为：" << endl << arr[0];
	for (int i = 1; i < l; ++i)
		cout << "->" << arr[i];
	//读取data3.txt的元素个数
	in.open("data3.txt");
	if (in.fail()) {
		cout << "打开失败！";
		exit(1);
	}
	int l2 = 0; //data3元素个数
	while (!in.eof()) {
		in >> d;
		l2++;
	}
	in.seekg(0, ios::beg);
	arr2 = new int[l + l2]; //重新申请内存
	if (arr2 == nullptr)
		exit(1);
	memcpy(arr2, arr, l * sizeof(int));
	delete[] arr;
	arr = arr2;
	while (!in.eof()) {
		in >> d;
		for (int i = 0; i < l; ++i)
			if (arr[i] == d)
				goto end;//如果存在不添加
		arr[l++] = d;
end:
		continue;
	}
	in.close();
//写入data.txt
	ofstream out("data.txt");
	if (out.fail()) {
		cout << "写入失败！";
		exit(1);
	}
	for (int i = 0; i < l; ++i)
		out << arr[i] << endl;
	out.close();
	return 0;
}
