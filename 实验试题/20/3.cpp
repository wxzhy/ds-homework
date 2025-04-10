#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
typedef bool Status;
#define OK 1
#define ERROR 0
typedef vector<int> SqList;
void Adjust(SqList &H, int low, int high) {
	int parent = low, child = 2 * low + 1;
	while (child <= high) {
		if (child + 1 <= high && H[child + 1] > H[child])
			child++;
		if (H[child] > H[parent]) {
			swap(H[parent], H[child]);
			parent = child;
			child = child * 2 + 1;
		} else
			break;

	}
}
Status HeapSort(SqList &H) {
	for (int i = H.size() / 2 - 1; i >= 0; i--)
		Adjust(H, i, H.size() - 1);
	for (int i = H.size() - 1; i >= 0; i--) {
		swap(H[0], H[i]);
		Adjust(H, 0, i - 1);
	}
	return OK;

}

Status DestroyData(SqList &H) {
	H.clear();
	return OK;
}

int BinSearch(SqList H, int key) {
	int low = 0, high = H.size() - 1, mid;
	while (low != high) {
		mid = (low + high) / 2;
		if (H[mid] == key)
			return mid;
		else if (H[mid] < key)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return -1;
}
int main() {
	ifstream in("data.txt");
	SqList H;
	if (in.fail()) {
		cout << "打开失败" << endl;
		exit(1);
	}
	while (!in.eof()) {
		int temp;
		in >> temp;
		H.push_back(temp);
	}
	in.close();
	HeapSort(H);
	cout << "排序后：" << endl;
	for (auto i : H)
		cout << i << ' ';
	cout << endl;
	cout << "查找位置在：" << BinSearch(H, 98) << endl;
	DestroyData(H);
	cout << "销毁成功";
	return 0;
}
