#include <stdio.h>
#include <malloc.h>
#define NDEBUG   //此语句禁用assert调用
#include <assert.h>
#include <stdlib.h>
#include "main.h"
#define N 8

const int stackMaxSize = 50;

//初始化栈 
void initStack(Stack *S)
{
    assert(S != NULL);
    S->base = (ElemType *)malloc(sizeof(ElemType)*stackMaxSize);
    if (NULL == S->base)
    {
        exit(0);
    }
    S->top = S->base;
    S->stacksize = 0;
}


int isEmpty(Stack *S)
{
    assert(S != NULL);
    return !S->stacksize;
}

ElemType* getTop(Stack *S)
{
    ElemType* e;
    assert(S != NULL);
    assert (!isEmpty(S));
    e = S->top-1;
    return e;
}

void push(Stack *S,ElemType e)
{
    assert(S != NULL);
    assert(S->stacksize != stackMaxSize);
    *(S->top) = e;
    S->stacksize++;
    S->top++;
}
void pop(Stack *S)
{
    assert(S != NULL);
    assert (!isEmpty(S));

    S->stacksize--;
    S->top = &S->base[S->stacksize];
}

//递归方法测试二叉树是否正确
void printTree(BiTree *T)
{
    //后序递归遍历（测试）
    if(T->lchild) printTree(T->lchild);
    if(T->rchild) printTree(T->rchild);
    printf("%c ",T->data);
    return;
}


int main(void)
{
    char fir[N],mid[N];
    getData(fir,mid);
    BiTree* tree = createBinaryTree(fir,mid,N-1);
    preOrderTraverse(tree);
    InOrderTraverse(tree);
    postOrderTraverse(tree);
    return 0;
}

void postOrderTraverse(BiTree* root)
{
    printf("后序遍历：");
    if (root == NULL)
        return;
    Stack s;
    initStack(&s);

    BiTree* pCur, *pLastVisit;
    pCur = root;
    pLastVisit = NULL;
    //先把pCur移动到左子树最下边
    while (pCur)
    {
        push(&s,*pCur);
        pCur = pCur->lchild;
    }
    while (!isEmpty(&s))
    {
        pCur = getTop(&s);
        pop(&s);
        //一个根节点被访问的前提是：无右子树或右子树已被访问过
        if (pCur->rchild == NULL || (pCur->rchild->lchild)== pLastVisit->lchild)
            // 由于取出的栈中数据不是放入时候的原地址，因此用二次引用匹配
            //pCur->rchild == pLastVisit 永远都不会相等的
        {
            printf("%c ",pCur->data);
            pLastVisit = pCur;
        }
        else
        {
            push(&s,*pCur);
            //进入右子树，且可肯定右子树一定不为空
            pCur = pCur->rchild;
            while (pCur)
            {
                push(&s,*pCur);
                pCur = pCur->lchild;
            }
        }
    }
    printf("\n");
}

void preOrderTraverse(BiTree* root)
{
    printf("前序遍历：");
    if (root == NULL)
        return;
    BiTree* p = root;
    Stack s;
    initStack(&s);
    while (!isEmpty(&s) || p)
    {
        if (p)
        {
            printf("%c ",p->data);
            push(&s,*p);
            p = p->lchild;
        }
        else
        {
            p = getTop(&s);
            pop(&s);
            p = p->rchild;
        }
    }
    printf("\n");
}


void InOrderTraverse(BiTree* root)
{
    printf("中序遍历：");
    if (root == NULL)
        return;
    BiTree* p = root;
    Stack s;
    initStack(&s);
    while (!isEmpty(&s) || p)
    {
        if (p)
        {
            push(&s,*p);
            p = p->lchild;
        }
        else
        {
            p=getTop(&s);
            pop(&s);
            printf("%c ",p->data);
            p = p->rchild;
        }
    }
    printf("\n");
}

//从文件中获取数据写入数组;
void getData(char *fir,char *in)
{
    FILE *fp;
    int i;
    fp = fopen("Array.txt","r+");
    assert(fp);
    for(i=0;i<N;i++)
    {
        fscanf(fp,"%c",fir+i);
    }
    for(i=0;i<N;i++)
    {
       fscanf(fp,"%c",in+i);
    }
    fclose(fp);
}


//根据前中序序列得到二叉树
BiTree* createBinaryTree(char* fir,char *in,int n)
{
	BiTree* T;	char *p; 	int k;
	if(n<=0) return NULL;
	T = (BiTree*)malloc(sizeof(BiTree));
	T->data = *fir;
	for(p=in;p<in+n;p++){
		if(*p == *fir)  break;
	}
	k=p-in;
	T->lchild = createBinaryTree(fir+1,in,k);
	T->rchild = createBinaryTree(fir+k+1,in+k+1,n-k-1);
	return T;
}

