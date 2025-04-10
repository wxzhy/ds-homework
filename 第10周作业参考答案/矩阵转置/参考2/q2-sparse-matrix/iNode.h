//
// Created by HuJW on 2023/11/2.
//

#ifndef Q2_SPARSE_MATRIX_INODE_H
#define Q2_SPARSE_MATRIX_INODE_H


class iNode {
    /*
     * 十字矩阵OrthogonalList中的非零元素节点
     */
private:
    int Row, Col;               // 元素的行、列位置
    int Value;                  // 元素的值
    iNode *Next_Row, *Next_Col; // 分别为：同一行下的下一个节点、同一列下的下一个节点
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
