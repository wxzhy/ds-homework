#include "SparseMatrix.h"
#include "OrthogonalList.h"

int main() {
	/*
	 * 从datamatrix.txt中读取矩阵，生成稀疏矩阵
	 */
	SparseMatrix Matrix("datamatrix.txt");
	/*
	 * 将稀疏矩阵输出至matrix1.txt中
	 */
	Matrix.ExportToFile("matrix1.txt");
	/*
	 * 分别用两种方法转置矩阵，将转置后的矩阵分别输出至matrix-a.txt和matrix-b.txt中
	 */
	Matrix.Transpose_1();   // 用第1种方法转置
	Matrix.ExportToFile("matrix-a.txt");
	Matrix.Transpose_1();   // 转置回去
	Matrix.Transpose_2();   // 用第2种方法重新转置
	Matrix.ExportToFile("matrix-b.txt");
	Matrix.Transpose_2();   // 再转置回去
	/*
	 * 从稀疏矩阵生成十字链表，并输出至matrix-c.txt
	 */
	OrthogonalList OrthoList(Matrix);
	OrthoList.ExportToFile("matrix-c.txt");

	return 0;
}
