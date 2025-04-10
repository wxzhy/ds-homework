//
// Created by HuJW on 2023/11/2.
//

#ifndef Q2_SPARSE_MATRIX_SPARSEMATRIX_H
#define Q2_SPARSE_MATRIX_SPARSEMATRIX_H
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>


bool Compare(const std::vector<int> &left, const std::vector<int> &right)
{
    /*
     * ����std::sort()�У���Ϊ����
     * ����SparseMatrix::Sparse���С��е��ֵ��򣬷���˳���return true�������ϵ�return false
     */
    return left[0]<right[0] || (left[0] == right[0] && left[1] <= right[1]);
}

class SparseMatrix {
    /*
     * ϡ�������vector<vector<int>>��ԪԪ���������������Ԫ��
     */
private:
    int Rows, Cols, Elements_Num;           // �ֱ��ʾ�������������������������Ԫ�صĸ���
    std::vector<std::vector<int>> Sparse;   // �������Ԫ�ص���ԪԪ�����飬ÿ��Ԫ��Ϊ(Row, Col, Value)
public:
    SparseMatrix(const char *file_path){
        /*
         * ��ȡfile_path·���µ��ļ�������ϡ�����
         */
        std::fstream fp;
        fp.open(file_path, std::ios::in);
        if(!fp.is_open())
        {
            // ��ȡ�ļ�������ֹ����
            std::cout<<"File open error"<<std::endl;
            std::exit(-1);
        }
        Rows = 1;
        Cols = Elements_Num = 0;
        int col = 0;
        while(!fp.eof())
        {
            int buffer;
            fp>>buffer; // ���ļ��ж�ȡ����
            col += 1;
            if(buffer!=0)
            {
                Sparse.emplace_back(std::vector<int>{Rows,col,buffer});
                Elements_Num += 1;
            }
            // ÿ��ȡһ��������ȡ����һ���ַ���Ϊ' '�������δ������Ϊ'\n'����н�����
            char key;
            fp.get(key);
            if(key=='\n')
            {
                // �ڶ����һ��ʱ����¼�¾����������
                if(Rows==1)
                {
                    Cols = col;
                }
                col = 0;
                Rows += 1;
            }
        }
        fp.close();
    }
    int Transpose_1(){
        /*
         * ʹ�ã�[1]�ȶ�ÿ������Ԫ�����н�����[2]�ٰ���Sparse���С��е��ֵ���������� �ķ�ʽ���о���ת��
         */
        int temp = Rows;
        Rows = Cols;
        Cols = temp;
        if(Elements_Num<1)
        {
            // ��������û�з���Ԫ�أ��������ϡ�����Sparse���е���
            return -1;
        }
        auto iterator = Sparse.begin();
        while(iterator!=Sparse.end())
        {
            // ��Sparse��ÿһ��Ԫ�ص��С��н���
            int row = (*iterator)[0];
            int col = (*iterator)[1];
            (*iterator)[1] = row;
            (*iterator)[0] = col;
            iterator += 1;
        }
        // ����Sparse���С��е��ֵ����������
        // �������ʹ�÷�װ�õ�Compare()����
        sort(Sparse.begin(),Sparse.end(), Compare);
        return 1;
    }
    int Transpose_2(){
        /*
         * ʹ�ã�[1]�ȶ�ԭ����ÿ����ķ���Ԫ�ؽ��м�����[2]�ٱ���ϡ�����Sparse�����ݼ����������ÿ��Ԫ����Sparse�е�λ�ã������н��� �ķ�ʽ���о���ת��
         */
        int temp = Rows;
        Rows = Cols;
        Cols = temp;
        if(Elements_Num<1)
        {
            // ��������û�з���Ԫ�أ��������ϡ�����Sparse���е���
            return -1;
        }
        std::vector<int> Count(Cols+1,0);   // ��¼ԭ����ÿ����ķ���Ԫ�صĸ�����Count[idx]��Ӧ��idx�У�Count[0]==0��
        auto iterator = Sparse.begin();
        while(iterator!=Sparse.end())
        {
            Count[(*iterator)[1]] += 1;
            iterator += 1;
        }
        for(int i=1;i<=Cols-1;i+=1)
        {
            Count[i] = Count[i-1]+Count[i];
        }
        // ���һ��Sparse��Copy��һ�߱���Copy��һ��ԭ���޸�Sparse
        std::vector<std::vector<int>> Copy = Sparse;
        auto it_Copy = Copy.begin();
        while(it_Copy!=Copy.end())
        {
            Sparse[Count[(*it_Copy)[1]-1]++] = {(*it_Copy)[1],(*it_Copy)[0],(*it_Copy)[2]};
            it_Copy += 1;
        }
        return 1;
    }
    int GetElement(int row, int col){
        /*
         * �����С���λ�û�ȡ��λ�õľ���Ԫ��ֵ
         */
        // ȷ����������Ϸ����ھ���Χ�ڣ�
        if(row<=0 || row>Rows || col<=0 || col>Cols)
        {
            std::cout<<"Index Overflow"<<std::endl;
            std::exit(-1);
        }
        // ������Ϊ�������ֱ�ӷ���0����Լ����
        if(Elements_Num<1)
        {
            return 0;
        }
        auto iterator = Sparse.begin();
        // ����ϡ�����Sparse��ֱ���ҵ����ҵ�Ԫ�ز�returnԪ��ֵ�����Ҳ�������˵����λ�õ�Ԫ��Ϊ0��
        while(iterator->front()<row || (*iterator)[1]<col)
        {
            if(iterator->front()>row)
            {
                break;
            }
            iterator += 1;
        }
        if(iterator->front()==row || (*iterator)[1]==col)
        {
            return (*iterator)[2];
        }
        // ��ϡ��������Ҳ�������λ�õ�Ԫ�أ�˵����λ�õ�Ԫ��Ϊ0��return 0
        return 0;
    }
    std::vector<int> GetElement(int idx){
        /*
         * ����ϡ������е��±������ط���Ԫ�ص��С��С�ֵ
         */
        // ȷ����������Ϸ�����ϡ�����Χ�ڣ�
        if(idx<0 || idx>=Elements_Num)
        {
            std::cout<<"Index Overflow"<<std::endl;
            std::exit(-1);
        }
        return Sparse[idx];
    }
    int GetRows(){
        /*
         * ��ȡ����������
         */
        return Rows;
    }
    int GetCols(){
        /*
         * ��ȡ����������
         */
        return Cols;
    }
    int GetElementsNum(){
        /*
         * ��ȡ�������Ԫ������
         */
        return Elements_Num;
    }
    int ExportToFile(const char *file_path){
        /*
         * ��ϡ��������ʽ�����������file_path·���µ��ļ���
         */
        std::fstream fp;
        fp.open(file_path, std::ios::ate|std::ios::out);
        if(!fp.is_open())
        {
            std::cout<<"File open error"<<std::endl;
            std::exit(-1);
        }
        // ������Ϊ�������ֱ�ӷ���-1����Լ����
        if(Elements_Num<1)
        {
            return -1;
        }
        fp<<"Row\tCol\tValue"<<std::endl;
        // ����ϡ�����Sparse�������д�����ļ�fp��
        auto iterator = Sparse.begin();
        while(iterator!=Sparse.end())
        {
            fp<<(*iterator)[0]<<"\t"<<(*iterator)[1]<<"\t"<<(*iterator)[2]<<std::endl;
            iterator += 1;
        }
        fp.close();
        return 1;
    }
};


#endif //Q2_SPARSE_MATRIX_SPARSEMATRIX_H
