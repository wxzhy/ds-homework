#include <iostream>
#include <cstring>

#define MAX 100
using namespace std;

template<class T> // 模板类
class Stack { // 栈类
	private:
		T *pBase;// 栈的数据域
		T *pTop;// 栈顶指针
		int maxSize;// 栈的最大容量
	public:
		Stack(int size) {
			pBase = new T[size];// 动态分配内存
			pTop = pBase;// 初始化栈顶指针
			maxSize = size;// 初始化栈的最大容量
		}

		Stack() {
			delete[]pBase;
		}

		bool empty() {
			return pTop == pBase;
		}

		bool full() {
			return pTop - pBase == maxSize - 1;
		}

		void push(T x) {
			if (full())
				return;
			*pTop++ = x;
		}

		T pop() {
			if (empty())
				return 0;
			return *--pTop;
		}

		T top() {
			if (empty())
				return 0;
			return *(pTop - 1);
		}
};

int priority(char op) {
	if (op == '+' || op == '-') // 优先级最低
		return 1;
	if (op == '*' || op == '/' || op == '%') // 优先级较高
		return 2;
	return 0;
}

double calculate(double val1, char op, double val2) {
	switch (op) {// 计算对应表达式
		case '+':
			return val1 + val2;
		case '-':
			return val1 - val2;
		case '*':
			return val1 * val2;
		case '/':
			return val1 / val2;
		case '%':
			return ((int) val1) % ((int) val2);
		default:
			return 0;
	}
}

double eval(char *s) {
	Stack<double> opnd(MAX / 2); // 操作数栈
	Stack<char> optr(MAX / 2); // 操作符栈
	int len = strlen(s);
	for (int i = 0; i < len; ++i) {
		if (isspace(s[i]))
			continue;
		if (isdigit(s[i])) {
			double val = 0;// 记录操作数
			while (isdigit(s[i])) {// 处理多位数，转换为double类型
				val = val * 10 + (s[i] - '0');
				i++;
			}
			opnd.push(val);// 将操作数压入栈中
			i--;
		} else if (s[i] == '(')
			optr.push(s[i]);// 将左括号压入栈中
		else if (s[i] == ')') {
			while (!optr.empty() && optr.top() != '(') {
				double val2 = opnd.pop();// 取出操作数栈中的两个操作数
				double val1 = opnd.pop();
				char op = optr.pop();
				opnd.push(calculate(val1, op, val2));// 计算并将结果压入操作数栈中
			}
			if (!optr.empty())
				optr.pop(); // 将左括号弹出
		} else {
			while (!optr.empty() && priority(optr.top()) >= priority(s[i])) { // 当前操作符优先级小于等于栈顶操作符优先级
				double val2 = opnd.pop();
				double val1 = opnd.pop();
				char op = optr.pop();
				opnd.push(calculate(val1, op, val2)); // 计算并将结果压入操作数栈中
			}
			optr.push(s[i]);// 将当前操作符压入栈中
		}
	}
	while (!optr.empty()) { // 处理剩余操作符
		double val2 = opnd.pop();// 取出操作数栈中的两个操作数
		double val1 = opnd.pop();
		char op = optr.pop();
		opnd.push(calculate(val1, op, val2));// 计算并将结果压入操作数栈中
	}
	return opnd.top();// 返回操作数栈中的结果
}

int main() {
//	system("chcp 65001>nul");// 设置编码格式为UTF-8
	char s[MAX];
	cout << "请输入表达式：";
	cin.get(s, MAX);// 输入表达式
	cout << "结果为：" << eval(s);
	return 0;
}
