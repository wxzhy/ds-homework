//
// Created by HuJW on 2023/11/2.
//

#ifndef Q2_SPARSE_MATRIX_ORTHOGONALLIST_H
#define Q2_SPARSE_MATRIX_ORTHOGONALLIST_H
#include "SparseMatrix.h"
#include "iNode.h"

class OrthogonalList {
    /*
     * ʮ�־��󣬿����ڴ���ϡ�����
     */
private:
    int Rows, Cols;         // �������������������
    iNode **pRows, **pCols; // �ֱ𴢴���ָ����С������µ��׸��ڵ��ָ��
public:
    OrthogonalList(SparseMatrix &sparsematrix){
        /*
         * ��ϡ�����SparseMatrix����ʮ�־���OrthogonalList
         */
        Rows = sparsematrix.GetRows();
        Cols = sparsematrix.GetCols();
        pRows = new iNode*[Rows];
        pCols = new iNode*[Cols];
        // �Ƚ����ָ��Ķ���ָ��pRows��pCols����ʼ��Ϊnullptr
        for(int i=0;i<=Rows-1;i+=1)
        {
            pRows[i] = nullptr;
        }
        for(int i=0;i<=Cols-1;i+=1)
        {
            pCols[i] = nullptr;
        }
        std::vector<iNode*> prev_row(Cols,nullptr); // ��ʾĳһ���ϵ���һ���ڵ���ʲô��prev_row[idx]��Ӧ��(idx+1)�У�
        iNode *prev_col = nullptr;                           // ָ��ǰ���ϵ���һ���ڵ�
        int row = 0;
        // ����ϡ��������������ʮ�־�����
        // �У��Լ�ÿ�����ڵ��У����ض��ǵ�����
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
         * �ͷ�ʮ�־�����ռ�õĿռ�
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
         * ��ʮ�־����������ľ������ʽ�����file_path·���µ��ļ���
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
                // ��ͬһ���е��Ⱥ���������Ԫ��֮�䲹����Ԫ��'0'
                for(int i=prev_col+1;i<col;i+=1)
                {
                    fp<<"0 ";
                }
                prev_col = col;
                fp<<pPrev->GetValue()<<" ";
            }
            // ��ÿһ�е�ĩβ����ʣ�����Ԫ��'0'
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
