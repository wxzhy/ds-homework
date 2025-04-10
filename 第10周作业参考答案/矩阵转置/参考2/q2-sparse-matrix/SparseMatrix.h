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
     * 用于std::sort()中，作为参数
     * 按照SparseMatrix::Sparse内行、列的字典序，符合顺序的return true，不符合的return false
     */
    return left[0]<right[0] || (left[0] == right[0] && left[1] <= right[1]);
}

class SparseMatrix {
    /*
     * 稀疏矩阵，用vector<vector<int>>三元元组数组来储存非零元素
     */
private:
    int Rows, Cols, Elements_Num;           // 分别表示矩阵的总行数、总列数、非零元素的个数
    std::vector<std::vector<int>> Sparse;   // 储存非零元素的三元元组数组，每个元组为(Row, Col, Value)
public:
    SparseMatrix(const char *file_path){
        /*
         * 读取file_path路径下的文件，构造稀疏矩阵
         */
        std::fstream fp;
        fp.open(file_path, std::ios::in);
        if(!fp.is_open())
        {
            // 读取文件出错，终止运行
            std::cout<<"File open error"<<std::endl;
            std::exit(-1);
        }
        Rows = 1;
        Cols = Elements_Num = 0;
        int col = 0;
        while(!fp.eof())
        {
            int buffer;
            fp>>buffer; // 从文件中读取的数
            col += 1;
            if(buffer!=0)
            {
                Sparse.emplace_back(std::vector<int>{Rows,col,buffer});
                Elements_Num += 1;
            }
            // 每读取一个数，读取其下一个字符（为' '则该行尚未结束；为'\n'则该行结束）
            char key;
            fp.get(key);
            if(key=='\n')
            {
                // 在读完第一行时，记录下矩阵的总列数
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
         * 使用：[1]先对每个非零元素行列交换，[2]再按照Sparse内行、列的字典序进行排序 的方式进行矩阵转置
         */
        int temp = Rows;
        Rows = Cols;
        Cols = temp;
        if(Elements_Num<1)
        {
            // 若矩阵内没有非零元素，则无需对稀疏矩阵Sparse进行调整
            return -1;
        }
        auto iterator = Sparse.begin();
        while(iterator!=Sparse.end())
        {
            // 将Sparse内每一个元素的行、列交换
            int row = (*iterator)[0];
            int col = (*iterator)[1];
            (*iterator)[1] = row;
            (*iterator)[0] = col;
            iterator += 1;
        }
        // 按照Sparse内行、列的字典序进行排序
        // 排序规则使用封装好的Compare()函数
        sort(Sparse.begin(),Sparse.end(), Compare);
        return 1;
    }
    int Transpose_2(){
        /*
         * 使用：[1]先对原矩阵每列里的非零元素进行计数，[2]再遍历稀疏矩阵Sparse，根据计数结果调整每个元素在Sparse中的位置，并行列交换 的方式进行矩阵转置
         */
        int temp = Rows;
        Rows = Cols;
        Cols = temp;
        if(Elements_Num<1)
        {
            // 若矩阵内没有非零元素，则无需对稀疏矩阵Sparse进行调整
            return -1;
        }
        std::vector<int> Count(Cols+1,0);   // 记录原矩阵每列里的非零元素的个数（Count[idx]对应第idx列，Count[0]==0）
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
        // 深拷贝一份Sparse至Copy，一边遍历Copy，一边原地修改Sparse
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
         * 根据行、列位置获取该位置的矩阵元素值
         */
        // 确保输入参数合法（在矩阵范围内）
        if(row<=0 || row>Rows || col<=0 || col>Cols)
        {
            std::cout<<"Index Overflow"<<std::endl;
            std::exit(-1);
        }
        // 若矩阵为零矩阵，则直接返回0，节约性能
        if(Elements_Num<1)
        {
            return 0;
        }
        auto iterator = Sparse.begin();
        // 遍历稀疏矩阵Sparse，直到找到查找的元素并return元素值（若找不到，则说明该位置的元素为0）
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
        // 在稀疏矩阵中找不到查找位置的元素，说明该位置的元素为0，return 0
        return 0;
    }
    std::vector<int> GetElement(int idx){
        /*
         * 根据稀疏矩阵中的下标数返回非零元素的行、列、值
         */
        // 确保输入参数合法（在稀疏矩阵范围内）
        if(idx<0 || idx>=Elements_Num)
        {
            std::cout<<"Index Overflow"<<std::endl;
            std::exit(-1);
        }
        return Sparse[idx];
    }
    int GetRows(){
        /*
         * 获取矩阵总行数
         */
        return Rows;
    }
    int GetCols(){
        /*
         * 获取矩阵总列数
         */
        return Cols;
    }
    int GetElementsNum(){
        /*
         * 获取矩阵非零元素总数
         */
        return Elements_Num;
    }
    int ExportToFile(const char *file_path){
        /*
         * 以稀疏矩阵的形式将矩阵输出至file_path路径下的文件中
         */
        std::fstream fp;
        fp.open(file_path, std::ios::ate|std::ios::out);
        if(!fp.is_open())
        {
            std::cout<<"File open error"<<std::endl;
            std::exit(-1);
        }
        // 若矩阵为零矩阵，则直接返回-1，节约性能
        if(Elements_Num<1)
        {
            return -1;
        }
        fp<<"Row\tCol\tValue"<<std::endl;
        // 遍历稀疏矩阵Sparse，并逐个写入至文件fp中
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
