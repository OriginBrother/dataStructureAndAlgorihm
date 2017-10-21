#include<stdio.h>
#include<malloc.h>
#define LH  1
#define EH  0
#define RH -1

typedef struct BSTNode{
	int data;
	int bf;  // 平衡因子
	struct BSTNode * lchild, *rchild;
}BSTree;


void R_Rotate(BSTree **T)
{
	BSTree *lc = (*T)->lchild;
	(*T)->lchild = lc->rchild;
	lc->rchild = *T;
	*T = lc;
}

void L_Rotate(BSTree **T)
{
	BSTree *rc = (*T)->rchild;
	(*T)->rchild = rc->lchild;
	rc ->lchild = *T;
	*T = rc;
}
	



void LeftBalance(BSTree **T)
{
	BSTree *lc = (*T)->lchild;
	BSTree *rd;
	switch(lc->bf)
	{
			case LH:
					(*T)->bf = lc->bf = EH;
					R_Rotate(T);
					break;
			case RH:
					rd = lc->rchild;
					switch(rd->bf)
					{
							case LH:
									(*T)->bf = RH;
									lc->bf = EH;
									break;
							case EH:
									(*T)->bf = lc ->bf = EH;
									break;
							case RH:
									(*T)->bf = EH; lc->bf = LH;
									break;
					}

					rd->bf = EH;
					R_Rotate(T);
	}


}

void RightBalance(BSTree **T)
{
		BSTree *rc = (*T)->rchild;
		BSTree *ld;
		switch(rc->bf)
		{
				case RH:
						(*T)->bf = rc->bf = EH;
						L_Rotate(T);
						break;
				case LH:
						ld = rc->lchild;
						switch(ld->bf)
						{
								case RH:
										(*T)->bf = LH;
										rc->bf = EH;
										break;
								case EH:
										(*T)->bf = rc->bf = EH;
										break;
								case LH:
										(*T)->bf = EH;rc->bf = RH;
										break;
						
						}
						ld->bf = EH;
						L_Rotate(T);

		}
}

int InsertAVL(BSTree **T,int e,int *taller )
{
	if(!*T)
	{
		*T = (BSTree*)malloc(sizeof(BSTree));
		(*T)->data = e;
		(*T)->lchild = (*T)->rchild = NULL;
		(*T)->bf = EH; *taller = 1;
	}
	else{
		if(e == (*T)->data)
		{
			*taller = 0;
			printf("已存在该节点，无须插入：\n");
			return 0;
		}
		if(e < (*T)->data)
		{
			if(!InsertAVL(&((*T)->lchild),e,taller)) return 0; 
			if(*taller)
			{
					switch((*T)->bf)
					{
							case LH:
									LeftBalance(T);
									*taller = 0;
									break;
							case EH:
									(*T)->bf = LH; *taller = 1;
									break;
							case RH:
									(*T)->bf = EH; *taller = 0;
									break;
				 	}
			}
		}
		if(e > (*T)->data)
		{
			if(!InsertAVL(&((*T)->rchild),e,taller)) return 0;
			if(*taller)
			{
					switch((*T)->bf){
							case LH:
									(*T)->bf = EH; *taller = 0;
									break;
							case EH:
									(*T)->bf = RH; *taller = 1;
									break;
							case RH:
									RightBalance(T);
									*taller = 0;
									break;
					}
			}
		}
	}

	return 1;
}

void PrePrintTree(BSTree *tree) //先序打印出树
{
	if(!tree)
			return;
	if(tree)
		printf(" %d",tree->data);
	if(tree->lchild)
		PrePrintTree(tree->lchild);
	if(tree->rchild)
		PrePrintTree(tree->rchild);
}

void InPrintTree(BSTree *tree)
{
	if(!tree)
			return;
	if(tree->lchild)
			InPrintTree(tree->lchild);

	printf(" %d",tree->data);

	if(tree->rchild)
			InPrintTree(tree->rchild);
}


void findAVL(BSTree *tree,int data)
{
	if(!tree)
	{
			printf("树中不存在这个数！\n");
			return ;
	}
	else if(data > tree->data)
	{
			findAVL(tree->rchild,data);
	}
	else if(data < tree->data)
	{
			findAVL(tree->lchild,data);
	}
	else 
	{
			printf("这个节点存在，地址为:%p",tree);
	}
}

void deleteNode(BSTree **T);

int deleteAVL(BSTree **T,int e,int *shorter)
{
	if(!(*T))
	{
			printf("该节点不存在，删除失败！\n");
			return 0;
	}
	else if(e < (*T)->data)  //在左子树中查找
	{
			if(!deleteAVL(&((*T)->lchild),e,shorter))
			{
					return 0;
			}
			if(*shorter) //平衡处理：
			{
				switch((*T)->bf)
				{
						case LH:
								(*T)->bf = EH;
								*shorter = 1;
								break;
						case EH:
								(*T)->bf = RH;
								*shorter = 0;
								break;
						case RH:
								if((*T)->rchild->bf ==EH)	*shorter = 0;
								else *shorter = 1;
								RightBalance(T);
								break;
				}
			}


	}
	else if(e > (*T)->data)  //在右子树中查找 ,同上
	{
			if(!deleteAVL(&((*T)->rchild),e,shorter))
			{
					if(*shorter)
					{
							switch((*T)->bf)
							{
									case LH:
											if((*T)->lchild->bf==EH) *shorter = 0;
											else *shorter =1;
											LeftBalance(T);
											break;
									case EH:
											(*T)->bf = LH;
											*shorter = 0;
											break;
									case RH:
											(*T)->bf = EH;
											*shorter = 1;
											break;
							}
					}

			}
	}
	else if(e== (*T)->data)   //找到删除节点，进行删除操作
	{  //分为三种情况：1.左子树为空;2.右子树为空;3.左右子数都存在
			BSTree *tree=NULL; //暂时保存被删除节点指针，交换后释放空间;

			if((*T)->lchild==NULL) 
			{	
					tree = *T;
					*T = (*T)->rchild;
					free(tree);
					*shorter = 1;  //该节点为跟的树高度降低，整个树并不一定;
			}else if((*T)->rchild==NULL)
			{
					tree = *T;
					*T = (*T)->lchild;
					free(tree);
					*shorter = 1;
			}
			else {
					tree = (*T)->lchild;
					while(tree->rchild)
					{//找到T的左子树的最右子树
							tree = tree->rchild;
					}
					(*T)->data = tree->data;
					
					deleteAVL(&((*T)->lchild),tree->data,shorter); //删除tree->data 节点
			}
	}
	
	return 1;

}




int main()
{
	int n;
	int input;

	BSTree *tree=NULL;
	int *taller;
	*taller = 0;
	for(;;)
	{
		printf("插入节点:	..............		1\n");
		printf("遍历树	:	..............		2\n");
		printf("查找节点:	..............		3\n");
		printf("删除节点:	..............		4\n");
		printf("退出	:	..............		0\n");
		printf("Please Enter the correct key to continue:\n");
		scanf("%d",&n);
		switch(n)
		{
			case 1:
				printf("请输入插入节点的数据:	");
				scanf("%d",&input);
				InsertAVL(&tree,input,taller); //0 表示初始时未增长
				break;
			case 2:
				printf("先序遍历:	");
				PrePrintTree(tree);
				printf("\n中序遍历：	");
				InPrintTree(tree);
				printf("\n");
				
				break;
			case 3:
				printf("请输入要查找的数:");
				scanf("%d",&input);
				findAVL(tree,input);
				break;
			case 4:
				printf("请输入要删除的节点:");
				scanf("%d",&input);
				deleteAVL(&tree,input,taller);
				break;
			case 0:
				return 0;
		}

		printf("\n");

	}
}
