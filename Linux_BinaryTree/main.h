#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

typedef struct BiTNode{
    char data;
    struct BiTNode *lchild;
    struct BiTNode *rchild;
}BiTree;
typedef struct SeqStack
{
    BiTree *top;
    BiTree *base;
    int stacksize;
}Stack;
typedef BiTree ElemType;

void push(Stack *S,ElemType e);


void getData(char *fir,char *in);
BiTree* createBinaryTree(char* fir,char *in,int n);
void preOrderTraverse(BiTree* root);
void InOrderTraverse(BiTree* root);
void postOrderTraverse(BiTree* root);

#endif // MAIN_H_INCLUDED
