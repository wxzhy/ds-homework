//
// Created by HuJW on 2023/11/2.
//

#ifndef Q2_SPARSE_MATRIX_ORTHOGONALLIST_H
#define Q2_SPARSE_MATRIX_ORTHOGONALLIST_H
#include "SparseMatrix.h"
#include "iNode.h"

class OrthogonalList {
    /*
     * 十字矩阵，可用于储存稀疏矩阵
     */
private:
    int Rows, Cols;         // 矩阵的总行数、总列数
    iNode **pRows, **pCols; // 分别储存多个指向该行、该列下的首个节点的指针
public:
    OrthogonalList(SparseMatrix &sparsematrix){
        /*
         * 从稀疏矩阵SparseMatrix构造十字矩阵OrthogonalList
         */
        Rows = sparsematrix.GetRows();
        Cols = sparsematrix.GetCols();
        pRows = new iNode*[Rows];
        pCols = new iNode*[Cols];
        // 先将存放指针的二级指针pRows和pCols都初始化为nullptr
        for(int i=0;i<=Rows-1;i+=1)
        {
            pRows[i] = nullptr;
        }
        for(int i=0;i<=Cols-1;i+=1)
        {
            pCols[i] = nullptr;
        }
        std::vector<iNode*> prev_row(Cols,nullptr); // 表示某一列上的上一个节点是什么（prev_row[idx]对应第(idx+1)列）
        iNode *prev_col = nullptr;                           // 指向当前行上的上一个节点
        int row = 0;
        // 遍历稀疏矩阵，逐个加入至十字矩阵中
        // 行，以及每行以内的列，都必定是递增的
        for(int idx=0;idx<=sparsematrix.GetElementsNum()-1;idx+=1)
        {
            std::vector<int> temp = sparsematrix.GetElement(idx);
            iNode *pNode = new iNode(temp[0],temp[1],temp[2]);
            if(temp[0]!=row)
            {
                row = temp[0];
                pRows[row-1] = pNode;
                prev_col = pNode;
            }
            else
            {
                prev_col->SetNext_Row(pNode);
                prev_col = pNode;
            }
            if(prev_row[temp[1]-1] == nullptr)
            {
                pCols[temp[1]-1] = pNode;
                prev_row[temp[1]-1] = pNode;
            }
            else
            {
                prev_row[temp[1]-1]->SetNext_Col(pNode);
                prev_row[temp[1]-1] = pNode;
            }
        }
    }
    ~OrthogonalList(){
        /*
         * 释放十字矩阵所占用的空间
         */
        for(int col=1;col<=Cols;col+=1)
        {
            iNode *pPrev = nullptr;
            iNode *pNext = pCols[col-1];
            while(pNext!= nullptr)
            {
                pPrev = pNext;
                pNext = pNext->GetNext_Col();
                delete pPrev;
            }
        }
        delete pRows;
        delete pCols;
    }
    void ExportToFile(const char *file_path){
        /*
         * 将十字矩阵以完整的矩阵的形式输出至file_path路径下的文件中
         */
        std::fstream fp;
        fp.open(file_path, std::ios::ate|std::ios::out);
        if(!fp.is_open())
        {
            std::cout<<"File open error"<<std::endl;
            std::exit(-1);
        }
        for(int row=1;row<=Rows;row+=1)
        {
            iNode *pPrev = nullptr;
            iNode *pNext = pRows[row-1];
            int prev_col = 0;
            while(pNext!= nullptr)
            {
                pPrev = pNext;
                pNext = pNext->GetNext_Row();
                int col = pPrev->GetCol();
                // 在同一行中的先后两个非零元素之间补齐零元素'0'
                for(int i=prev_col+1;i<col;i+=1)
                {
                    fp<<"0 ";
                }
                prev_col = col;
                fp<<pPrev->GetValue()<<" ";
            }
            // 在每一行的末尾补齐剩余的零元素'0'
            if(prev_col!=Cols)
            {
                for(int i=prev_col+1;i<=Cols;i+=1)
                {
                    fp<<"0 ";
                }
            }
            fp<<std::endl;
        }
        fp.close();
    }
};


#endif //Q2_SPARSE_MATRIX_ORTHOGONALLIST_H
