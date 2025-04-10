#include "SparseMatrix.h"
#include "OrthogonalList.h"

int main() {
	/*
	 * ��datamatrix.txt�ж�ȡ��������ϡ�����
	 */
	SparseMatrix Matrix("datamatrix.txt");
	/*
	 * ��ϡ����������matrix1.txt��
	 */
	Matrix.ExportToFile("matrix1.txt");
	/*
	 * �ֱ������ַ���ת�þ��󣬽�ת�ú�ľ���ֱ������matrix-a.txt��matrix-b.txt��
	 */
	Matrix.Transpose_1();   // �õ�1�ַ���ת��
	Matrix.ExportToFile("matrix-a.txt");
	Matrix.Transpose_1();   // ת�û�ȥ
	Matrix.Transpose_2();   // �õ�2�ַ�������ת��
	Matrix.ExportToFile("matrix-b.txt");
	Matrix.Transpose_2();   // ��ת�û�ȥ
	/*
	 * ��ϡ���������ʮ�������������matrix-c.txt
	 */
	OrthogonalList OrthoList(Matrix);
	OrthoList.ExportToFile("matrix-c.txt");

	return 0;
}
