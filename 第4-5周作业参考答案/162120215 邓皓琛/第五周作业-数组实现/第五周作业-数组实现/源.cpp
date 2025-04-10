//===========================================================================
//		学号：162120215
//		姓名：邓皓琛
//		数据结构-第5周作业-数组实现
//		时间：2022/9/28
//============================================================================

/*
	注意：本程序为便于测试，将data与data2合并后的数据输出至文件“data_output.txt”
	中，请注意查看
*/

#include<iostream>
#include<fstream>
#include<stdlib.h>

using namespace std;

int* InitArray(int);						//初始化数组
int getlen();								//获取data中数据的个数
int* InsArray(int*,int&);					//在数组的第二个位置插入3456
void Print(int*,int);						//输出数组
int getlen_2();								//获取data2中数据的个数
int* InitArray_2(int);						//初始化数组data2
int* ArrayCat(int*,int*,int,int);			//链接两个数组
int* DelElem(int*,int&);					//删除数组中的重复元素
void Output(int*, int);						//将数组中的元素输出至文件

int main() {
	
	int cnt = getlen();
	int* pArray = InitArray(cnt);
	cout << "     data原始数据：";
	Print(pArray,cnt);

	pArray=InsArray(pArray,cnt);
	cout << " 插入3456后的data：";
	Print(pArray, cnt);

	int cnt2 = getlen_2();
	int* pArray2 = InitArray_2(cnt2);
	cout << "      data2中数据：";
	Print(pArray2, cnt2);

	int *pArray_Cat = ArrayCat(pArray, pArray2, cnt, cnt2);
	int cnt_sum = cnt + cnt2;
	cout << "           合并后：";
	Print(pArray_Cat, cnt_sum);

	int* pArray_Del = DelElem(pArray_Cat, cnt_sum);
	cout << " 合并删除重复元素：";
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
	// pArray 顺序完整数组
	for (int i = 0; i < cnt; i++) {
		InputFile >> pArray[i];
	}
	InputFile.close();
	return pArray;
}

int getlen() {
	/*打开data.txt文件*/
	ifstream InputFile;
	InputFile.open("data.txt", ios::in);
	if (!InputFile) {
		cout << "Error!" << endl;
		exit(0);
	}

	int cnt = 0;		//存储数组长度
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
	/*打开data.txt文件*/
	ifstream InputFile;
	InputFile.open("data2.txt", ios::in);
	if (!InputFile) {
		cout << "Error!" << endl;
		exit(0);
	}

	int cnt = 0;		//存储数组长度
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
	// pArray 顺序完整数组
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
	/*计算删除重复元素后数组的长度*/
	int* pArray_tmp = new int[cnt];
	int cnt_Del = 0;	//删除重复元素后的数组长度
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


	/*获得删除相同元素后的数组*/
	int* pArray_Del = new int[cnt_Del];
	for (int i = 0; i < cnt_Del; i++) {
		pArray_Del[i] = pArray_tmp[i];
	}
	cnt = cnt_Del;
	delete[]pArray_tmp;		//释放临时数组
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

	cout << endl << "写入文件成功！" << endl;

	OutputFile.close();
}