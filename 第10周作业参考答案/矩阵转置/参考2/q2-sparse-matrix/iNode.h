//
// Created by HuJW on 2023/11/2.
//

#ifndef Q2_SPARSE_MATRIX_INODE_H
#define Q2_SPARSE_MATRIX_INODE_H


class iNode {
    /*
     * ʮ�־���OrthogonalList�еķ���Ԫ�ؽڵ�
     */
private:
    int Row, Col;               // Ԫ�ص��С���λ��
    int Value;                  // Ԫ�ص�ֵ
    iNode *Next_Row, *Next_Col; // �ֱ�Ϊ��ͬһ���µ���һ���ڵ㡢ͬһ���µ���һ���ڵ�
public:
    iNode(int row, int col, int value=0, iNode* next_row=nullptr, iNode *next_col= nullptr){
        Row = row;
        Col = col;
        Value = value;
        Next_Row = next_row;
        Next_Col = next_col;
    }
    int GetRow(){
        return Row;
    }
    int GetCol(){
        return Col;
    }
    int GetValue(){
        return Value;
    }
    void SetNext_Row(iNode *next){
        Next_Row = next;
    }
    void SetNext_Col(iNode *next){
        Next_Col = next;
    }
    iNode *GetNext_Row(){
        return Next_Row;
    }
    iNode *GetNext_Col(){
        return Next_Col;
    }
};


#endif //Q2_SPARSE_MATRIX_INODE_H
