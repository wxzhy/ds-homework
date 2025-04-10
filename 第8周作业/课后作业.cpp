#include <iostream>
using namespace std;
template<class T>
class Array {
	private:
		T *base;
		int m, n;
	public:
		Array(int m, int n): m(m), n(n) {
			base = new T[m * n];
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < n; j++) {
					base[i * n + j] = 0;
				}
			}
		}
		~Array() {
			delete []base;
		}
		Array(Array &a) {
			m = a.m;
			n = a.n;
			base = new T[m * n];
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < n; j++) {
					base[i * n + j] = a.base[i * n + j];
				}
			}
		}
		void traverse() {
			cout << "遍历结果为：" << endl;
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < n; j++) {
					cout << base[i * n + j] << " ";
				}
				cout << endl;
			}
		}
		T& get(int i, int j) {
			return base[i * n + j];
		}
		void set(int i, int j, T value) {
			base[i * n + j] = value;
		}
		bool duplicate() {
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < n; j++) {
					for (int k = 0; k < i; k++) {
						for (int l = 0; l < j; l++) {
							if (base[i * n + j] == base[k * n + l])
								return true;
						}
					}
				}
			}
			return false;
		}
};
int main() {
//	system("chcp 65001>nul");
	Array<int> a(3, 3);
	a.set(0, 0, 1);
	a.set(0, 1, 2);
	a.set(0, 2, 2);
	a.set(1, 0, 4);
	cout << "a[1][0]:" << a.get(1, 0) << endl;
	a.traverse();
	if (a.duplicate()) {
		cout << "有重复元素" << endl;
	} else {
		cout << "无重复元素" << endl;
	}
	return 0;
}
